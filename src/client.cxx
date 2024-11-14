#include <string>
#include <iostream>
#include <asio.hpp>

constexpr char host[] = "0:0:0:0:0:0:0:1";
constexpr char port[] = "8888";

using asio::ip::udp;

int main()
{
    asio::io_context context;    
    udp::resolver resolver(context);
    udp::resolver::query query(host, port, udp::resolver::query::numeric_host);
    udp::endpoint remote_endpoint = *resolver.resolve(query);
    
    udp::socket socket(context);
    socket.open(remote_endpoint.protocol());

    std::string message = "Hello from UDP IPv6 client!";
    socket.send_to(asio::buffer(message), remote_endpoint);

    char buffer[1024]{};
    asio::ip::udp::endpoint sender_endpoint;
    std::size_t bytes_received = socket.receive_from(asio::buffer(buffer), sender_endpoint);

    std::cout << "Received: " << bytes_received << " bytes from " << sender_endpoint.address().to_string() << std::endl;

    return 0;
}