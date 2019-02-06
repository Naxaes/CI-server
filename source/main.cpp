#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <sys/mman.h>
#include <arpa/inet.h>
#include <unistd.h>


constexpr sa_family_t IPv4 = AF_INET;
constexpr sa_family_t IPv6 = AF_INET6;

constexpr sa_family_t TCP = SOCK_STREAM;
constexpr sa_family_t UDP = SOCK_DGRAM;


sockaddr_in Address(const std::string& address, int port)
{
    // http://man7.org/linux/man-pages/man7/ip.7.html
    // struct sockaddr_in {
    //     sa_family_t    sin_family; /* address family: AF_INET */
    //     in_port_t      sin_port;   /* port in network byte order */
    //     struct in_addr sin_addr;   /* internet address */
    // };
    // sin_family is always set to AF_INET.
    sockaddr_in socket_address{};
    socket_address.sin_family = IPv4;
    socket_address.sin_port = htons(port);  // htons - Host to Network Short. Flip endianness to match machine.
    int success = inet_pton(IPv4, address.c_str(), &socket_address.sin_addr);  // Pointer (to String) to Number.
    if (success <= 0)
        throw std::runtime_error("Invalid address: " + address);

    return socket_address;
}


void Send(int socket, std::string message)
{
    ssize_t bytes_written = write(socket, message.c_str(), message.size());
    if (bytes_written == -1)
        throw std::runtime_error("Couldn't write to socket.");
}


std::string Receive(int socket, size_t max_size_to_receive)
{
    char* message = new char[max_size_to_receive];

    // Wait for message
    // http://man7.org/linux/man-pages/man2/recvmsg.2.html
    //     recv(socket, buffer, size, flags)
    //          socket: any socket.
    //          buffer: array to fill with the message.
    //          size: the size of the buffer.
    //          flags: options.
    ssize_t bytes_received = recv(socket, message, max_size_to_receive, 0);
    if (bytes_received == -1)
        throw std::runtime_error("Issue with connection.");
    // else if (bytes_received == 0)
    //     throw std::runtime_error("The client disconnected.");
    return message;
}



int ConnectServer(const std::string& address, int port, int max_number_of_clients)
{
    // The steps involved in establishing a socket on the server side are as follows:
    //
    //     1. Create a socket with the socket() system call.
    //     2. Bind the socket to an address using the bind() system call. For a server socket on the Internet,
    //        an address consists of a port number on the host machine.
    //     3. Listen for connections with the listen() system call.
    //     4. Accept a connection with the accept() system call. This call typically blocks until a client connects
    //        with the server.
    //     5. Send and receive data.

    int success;

    // http://man7.org/linux/man-pages/man2/socket.2.html
    //     socket(domain, type, protocol) creates an endpoint for communication and returns a file descriptor that
    //     refers to that endpoint
    //         domain: most commonly AF_INET (IPv4) or AF_INET6 (IPv6)
    //         type: most commonly SOCK_STREAM or SOCK_DGRAM
    //         protocol: 0 unless more protocols in the protocol family exist.
    int listen_socket = socket(IPv4, TCP, 0);
    if (listen_socket == -1)
        throw std::runtime_error("Couldn't create socket.");


    // http://man7.org/linux/man-pages/man2/bind.2.html
    //     bind(socket, address, size) assigns/binds the address to the socket.
    //
    sockaddr_in server_address = Address(address, port);
    success = bind(listen_socket, (sockaddr*)&server_address, sizeof(server_address));
    if (success == -1)
        throw std::runtime_error("Couldn't bind socket. Errno: " + std::to_string(errno) + ".");


    // http://man7.org/linux/man-pages/man2/listen.2.html
    //     listen(socket, backlog) marks the socket as a passive socket that will be used to accept incoming connection.
    //        socket: socket of type SOCK_STREAM or SOCK_SEQPACKET.
    //        backlog: the maximum length to which the queue of pending connections for socket may grow.
    success = listen(listen_socket, max_number_of_clients);
    if (success == -1)
        throw std::runtime_error("Can't listen to socket. Errno: " + std::to_string(errno) + ".");

    return listen_socket;
}



int main(int argc, char* argv[])
{
    std::string address = "0.0.0.0";
    int port = 8080;
    int maximum_clients = 1;
    size_t max_size_to_receive = 1024;

    int listen_socket = ConnectServer(address, port, maximum_clients);

    std::cout << "Server connected. Waiting for clients." << std::endl;

    bool connected = true;
    while (connected)
    {
        // http://man7.org/linux/man-pages/man2/accept.2.html
        //     accept(socket, address, size, flags)
        //         socket: socket of type SOCK_STREAM or SOCK_SEQPACKET.
        sockaddr_in client_address{};
        socklen_t client_address_size = sizeof(client_address);
        int client_socket = accept(listen_socket, (sockaddr*)&client_address, &client_address_size);
        if (client_socket == -1)
            throw std::runtime_error("Couldn't accept request from client. Errno: " + std::to_string(errno) + ".");


        std::cout << Receive(client_socket, max_size_to_receive) << std::endl;
    }


    close(listen_socket);


}









