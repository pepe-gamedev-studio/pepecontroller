#include "Peka2tvHttpClient.h"

#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/connect.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/error.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/asio/buffer.hpp>
#include <network/uri.hpp>

#include <cstdlib>
#include <string_view>

namespace peka2tv
{

Peka2tvHttpClient::Peka2tvHttpClient(std::string entry)
{
	network::uri uri(entry);
	host = uri.host().to_string();
	port = uri.port().empty() ?
		(uri.scheme() == network::uri::string_view("http") ? "80" : "443")
		: uri.port().to_string();
}

std::string Peka2tvHttpClient::Call(std::string method, std::string data)
{
	using tcp = boost::asio::ip::tcp;
	namespace ssl = boost::asio::ssl;
	namespace http = boost::beast::http;

	int version = 11;

	boost::asio::io_context ioc;

	ssl::context ctx{ ssl::context::sslv23_client };

	ctx.set_verify_mode(ssl::verify_peer);

	tcp::resolver resolver{ ioc };
	ssl::stream<tcp::socket> stream{ ioc, ctx };
	stream.set_verify_mode(boost::asio::ssl::verify_none);

	if (!SSL_set_tlsext_host_name(stream.native_handle(), host.c_str()))
	{
		boost::system::error_code ec{ static_cast<int>(::ERR_get_error()), boost::asio::error::get_ssl_category() };
		throw boost::system::system_error{ ec };
	}

	auto const results = resolver.resolve(host.c_str(), port);

	boost::asio::connect(stream.next_layer(), results.begin(), results.end());

	stream.handshake(ssl::stream_base::client);

	http::request<http::string_body> req{ http::verb::post, method, version };
	req.set(http::field::host, host);
	req.set(http::field::user_agent, BOOST_BEAST_VERSION_STRING);
	req.set(http::field::content_type, "application/json");
	req.body() = data;
	req.prepare_payload();

	http::write(stream, req);

	boost::beast::flat_buffer buffer;
	http::response<http::string_body> res;

	http::read(stream, buffer, res);

	return res.body();
}

}
