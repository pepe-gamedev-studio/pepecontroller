#include <boost/beast/version.hpp>
#include "Peka2tvHttpClient.h"

namespace peka2tv
{
	namespace beast = boost::beast; // from <boost/beast.hpp>
	namespace http = beast::http; // from <boost/beast/http.hpp>
	namespace net = boost::asio; // from <boost/asio.hpp>
	namespace ssl = boost::asio::ssl; // from <boost/asio/ssl.hpp>
	using tcp = boost::asio::ip::tcp;

	Peka2tvHttpClient::Peka2tvHttpClient(
            boost::asio::io_context *ioc, std::string entry)
	{
		boost::network::uri::uri uri(entry);
		host = uri.host();
		port = uri.port().empty()
			       ? (uri.scheme() == std::string_view("http") ? "80" : "443")
			       : uri.port();
		this->ioc = ioc;
                this->ctx.set_verify_mode(ssl::verify_none);
	}

	std::string Peka2tvHttpClient::Call(std::string method, std::string data,
                                std::function<void(nlohmann::json)>)
	{
		using tcp = boost::asio::ip::tcp;
		namespace ssl = boost::asio::ssl;
		namespace http = beast::http;
		int version = 11;

		boost::asio::io_context ioc;


		ctx.set_verify_mode(ssl::verify_peer);

		tcp::resolver resolver{ioc};
		ssl::stream<tcp::socket> stream{ioc, ctx};
		stream.set_verify_mode(ssl::verify_none);

		if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
		{
			boost::system::error_code ec{
				static_cast<int>(ERR_get_error()),
				boost::asio::error::get_ssl_category()
			};
			throw boost::system::system_error{ec};
		}

		const auto results = resolver.resolve(host.c_str(), port);

		boost::asio::connect(stream.next_layer(), results.begin(),
		                     results.end());

		stream.handshake(ssl::stream_base::client);

		http::request<http::string_body> req{
			http::verb::post, method,
			version
		};
		req.set(http::field::host, host);
		req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
		req.set(http::field::content_type, "application/json");
		req.body() = data;
		req.prepare_payload();

		http::write(stream, req);

		beast::flat_buffer buffer;
		http::response<http::string_body> res;

		http::read(stream, buffer, res);

		return res.body();
	}

	Peka2tvHttpClient::UserInfo Peka2tvHttpClient::JsonToUserInfo(const nlohmann::json& j)
	{
		return UserInfo{
			j["id"].get<int64_t>(), j["name"].get<std::string>(),
			j["slug"].get<std::string>()
		};
	}

}

namespace peka2tv
{
	void session::fail(beast::error_code ec, std::string what)
	{
		std::cerr << what << ": " << ec.message() << "\n";
	}

	void session::run(std::string host, std::string port,
	                  std::string target, std::string data,
	                  int version)
	{
        
		
		if (!SSL_set_tlsext_host_name(stream_.native_handle(), host.c_str()))
		{
			beast::error_code ec{
				static_cast<int>(ERR_get_error()),
				net::error::get_ssl_category()
			};
            throw boost::system::system_error{ec};
		}

		// Set up an HTTP POST request message
		req_.version(version);
		req_.method(http::verb::post);
		req_.target(target);
		req_.set(http::field::host, host);
		req_.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
		req_.set(http::field::content_type, "application/json");
		req_.body() = data;
		req_.prepare_payload();

		// Look up the domain name
		resolver_.async_resolve(
			host, port,
			beast::bind_front_handler(&session::on_resolve, shared_from_this()));
	}

	void session::on_resolve(beast::error_code ec,
	                         tcp::resolver::results_type results)
	{
		if (ec)
			return fail(ec, "resolve");

		// Set a timeout on the operation
		get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

		// Make the connection on the IP address we get from a lookup
		get_lowest_layer(stream_).async_connect(
			results,
			beast::bind_front_handler(&session::on_connect, shared_from_this()));
	}

	void session::on_connect(beast::error_code ec,
	                         tcp::resolver::results_type::endpoint_type)
	{
		if (ec)
			return fail(ec, "connect");

		// Perform the SSL handshake
		stream_.async_handshake(
			ssl::stream_base::client,
			beast::bind_front_handler(&session::on_handshake, shared_from_this()));
	}

	void session::on_handshake(beast::error_code ec)
	{
		if (ec)
			return fail(ec, "handshake");

		// Set a timeout on the operation
		get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

		// Send the HTTP request to the remote host
		http::async_write(
			stream_, req_,
			beast::bind_front_handler(&session::on_write, shared_from_this()));
	}

	void session::on_write(beast::error_code ec, std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "write");

		// Receive the HTTP response
		http::async_read(
			stream_, buffer_, res_,
			beast::bind_front_handler(&session::on_read, shared_from_this()));
	}

	void session::on_read(beast::error_code ec, std::size_t bytes_transferred)
	{
		boost::ignore_unused(bytes_transferred);

		if (ec)
			return fail(ec, "read");

		// Write the message to standard out
		//std::cout << res_ << std::endl;
        on_result(nlohmann::json::parse(res_.body()));
		// Set a timeout on the operation
		get_lowest_layer(stream_).expires_after(std::chrono::seconds(30));

		// Gracefully close the stream
		stream_.async_shutdown(
			beast::bind_front_handler(&session::on_shutdown, shared_from_this()));
	}

	void session::on_shutdown(beast::error_code ec)
	{
		if (ec == net::error::eof)
		{
			// Rationale:
			// http://stackoverflow.com/questions/25587403/boost-asio-ssl-async-shutdown-always-finishes-with-an-error
			ec = {};
		}
		if (ec)
			return fail(ec, "shutdown");

		// If we get here then the connection is closed gracefully
	}
}
