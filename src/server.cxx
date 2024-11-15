#include <string>
#include <iostream>
#include <asio.hpp>

constexpr int port = 8888; 

using asio::ip::udp;

int main()
{
    asio::io_context io_context;
    udp::socket socket(io_context, udp::endpoint(udp::v6(), port));

    char buffer[1024]{};
    udp::endpoint sender_endpoint;

    std::string message;
    while (message != "exit")
    {
        std::size_t bytes_received = socket.receive_from(asio::buffer(buffer), sender_endpoint);
        message = std::string(buffer, bytes_received);
        std::cout << "Received: " << message << std::endl;
        socket.send_to(asio::buffer(buffer, bytes_received), sender_endpoint);
    }

    return 0;
}