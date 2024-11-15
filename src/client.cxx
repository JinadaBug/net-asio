#include <string>
#include <iostream>

#define ASIO_STANDALONE
#define ASIO_HAS_CO_AWAIT
#include <asio.hpp>

constexpr char host[] = "0:0:0:0:0:0:0:1";
constexpr char port[] = "8888";

using asio::ip::udp;

std::string callback(std::string message)
{
	asio::io_context context;

	auto routine = [&](std::string new_message) -> asio::awaitable<std::string>
	{
		udp::socket socket(context);
		udp::resolver resolver(context);

		udp::resolver::query query(host, port, udp::resolver::query::numeric_host);
		udp::resolver::iterator iterator = co_await resolver.async_resolve(query, asio::use_awaitable);

		udp::endpoint receiver_endpoint = *iterator;
		udp::endpoint sender_endpoint;

		co_await socket.async_connect(receiver_endpoint, asio::use_awaitable);
		co_await socket.async_send_to(asio::buffer(new_message), receiver_endpoint, asio::use_awaitable);

		char receive_buffer[1024]{};
		auto receive_length = co_await socket.async_receive_from(asio::buffer(receive_buffer), sender_endpoint, asio::use_awaitable);

		co_return std::string(receive_buffer, receive_length);
	};

	std::future<std::string> response;
	response = asio::co_spawn(context, routine(message), asio::use_future);
	context.run();
	return response.get();
}

int main()
{
	std::string message;

	while (message != "exit")
	{	
		std::cin >> message;
		std::cout << "Received: " << callback(message) << std::endl;
	}

    return 0;
}