#pragma once
#include <nlohmann/json.hpp>

#include <string>
#include <exception>
#include <optional>
#include <type_traits>
#include <boost/beast/core.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <boost/beast/version.hpp>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <string>
#include <boost/network/uri/uri.hpp>

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
	http::request<http::empty_body> req_;
	http::response<http::string_body> res_;
public:
	explicit session(net::any_io_executor& ex, ssl::context& ctx)
		: resolver_(ex), stream_(ex, ctx)
	{}
	void fail(beast::error_code ec, char const *what);
	void run(const char* host, const char* port, const char* target,
	         int version);
	void on_resolve(beast::error_code ec, tcp::resolver::results_type results);

	void on_connect(beast::error_code ec,
	                tcp::resolver::results_type::endpoint_type);
	void on_handshake(beast::error_code ec);
	void on_write(beast::error_code ec, std::size_t bytes_transferred);
	void on_read(beast::error_code ec, std::size_t bytes_transferred);
	void on_shutdown(beast::error_code ec);
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
        Peka2tvHttpClient(net::any_io_executor &ex,
                          std::string entry = "https://sc2tv.ru");

	template<typename UserInfoMember, typename T>
	std::optional<UserInfo> FetchUserInfo(UserInfoMember m, T val)
	{
		static_assert(std::is_convertible_v<T, MemberType<UserInfoMember>::type>, "Type mismatch between property and provided value");

		const std::string resource = "/api/user";
		nlohmann::json q;
          switch (offsetOf(m))
          {
          case offsetOf(&UserInfo::id):
	          q["id"] = val;
	          break;
          case offsetOf(&UserInfo::name):
	          q["name"] = val;
	          break;
          case offsetOf(&UserInfo::slug):
	          q["slug"] = val;
	          break;
          default:
	          throw std::runtime_error("Invalid query");
          }

		auto r = nlohmann::json::parse(Call(resource, q.dump()));

		if (r.find("id") == r.end())
			return {};

		return UserInfo{ r["id"].get<int64_t>(), r["name"].get<std::string>(), r["slug"].get<std::string>() };
	}

      protected:
	std::string Call(std::string method, std::string data);


private:
	std::string host;
	std::string port;
	//tcp::resolver resolver_;
	//beast::ssl_stream<beast::tcp_stream> stream_;
	//beast::flat_buffer buffer_; // (Must persist between reads)
	//http::request<http::empty_body> req_;
	//http::response<http::string_body> res_;
	//ssl::context ctx{ssl::context::tlsv12_client};
};

}
