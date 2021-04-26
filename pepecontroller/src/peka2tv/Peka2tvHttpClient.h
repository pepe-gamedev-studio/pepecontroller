#pragma once
#include <nlohmann/json.hpp>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/network/uri/uri.hpp>
#include <boost/beast/version.hpp>
#include <boost/asio/strand.hpp>
#include <memory>
#include <string>
#include <string>
#include <optional>
#include <type_traits>

namespace peka2tv
{

namespace beast = boost::beast;         // from <boost/beast.hpp>
namespace http = beast::http;           // from <boost/beast/http.hpp>
namespace net = boost::asio;            // from <boost/asio.hpp>
namespace ssl = boost::asio::ssl;       // from <boost/asio/ssl.hpp>
using tcp = boost::asio::ip::tcp;       // from <boost/asio/ip/tcp.hpp>
	
template<typename T, typename U> constexpr size_t offsetOf(U T::*member)
{
	return (char*)&((T*)nullptr->*member) - (char*)nullptr;
}

template<typename T>
struct MemberType {};

template<typename T, typename M>
struct MemberType<T M::*> { using type = T; };

	
class session : public std::enable_shared_from_this<session>
{
	tcp::resolver resolver_;
	beast::ssl_stream<beast::tcp_stream> stream_;
	beast::flat_buffer buffer_; // (Must persist between reads)
	http::request<http::string_body> req_;
	http::response<http::string_body> res_;
public:
	explicit session(net::any_io_executor ex, ssl::context& ctx)
      : resolver_(ex), stream_(ex, ctx)
	{}
	void fail(beast::error_code ec, std::string what);
	void run(std::string host, std::string port, std::string target,
	         std::string data, int version);
	void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

	void on_connect(beast::error_code ec,
	                tcp::resolver::results_type::endpoint_type);
	void on_handshake(beast::error_code ec);
	void on_write(beast::error_code ec, std::size_t bytes_transferred);
	void on_read(beast::error_code ec, std::size_t bytes_transferred);
	void on_shutdown(beast::error_code ec);
    std::function<void(nlohmann::basic_json<>)> on_result;
};
	
	
class Peka2tvHttpClient
{

public:
	struct UserInfo
	{
		int64_t id;
		std::string name;
		std::string slug;
	};
public:
        Peka2tvHttpClient(boost::asio::io_context *ioc,
                          std::string entry = "https://sc2tv.ru");

	template<typename UserInfoMember, typename T>
        void
        FetchUserInfo(UserInfoMember m, T val,
                      std::function<void(std::optional<UserInfo>)> callback)
	{
		static_assert(std::is_convertible_v<T, MemberType<UserInfoMember>::type>, "Type mismatch between property and provided value");

		const std::string resource = "/api/user";
		const int version = 11;
		
		auto Session = std::make_shared<session>(make_strand(*ioc), ctx);
		Session->on_result = [&](nlohmann::json j)
		{
			if (j.find("id") == j.end())
				callback({});
			else
			{
				callback(JsonToUserInfo(j));
			}
		};
		nlohmann::json q;
		if (offsetOf(m) == offsetOf(&UserInfo::id))
			q["id"] = val;
		else if (offsetOf(m) == offsetOf(&UserInfo::name))
			q["name"] = val;
		else if (offsetOf(m) == offsetOf(&UserInfo::slug))
			q["slug"] = val;
		else
			throw std::runtime_error("Invalid query");
		
		Session->run(host, port, resource, q.dump(), version);
	}

      protected:
        std::string Call(std::string method, std::string data,
                         std::function<void(nlohmann::json)> callback);
        UserInfo JsonToUserInfo(const nlohmann::json& j);


private:
	std::string host;
	std::string port;
    boost::asio::io_context* ioc;
    ssl::context ctx{ssl::context::sslv23_client};
	//tcp::resolver resolver_;
	//beast::ssl_stream<beast::tcp_stream> stream_;
	//beast::flat_buffer buffer_; // (Must persist between reads)
	//http::request<http::empty_body> req_;
	//http::response<http::string_body> res_;
	//ssl::context ctx{ssl::context::tlsv12_client};
};

}
