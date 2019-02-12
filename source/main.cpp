#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include <sys/mman.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "parser.h"
#include "integrationTest.hpp"

constexpr sa_family_t IPv4 = AF_INET;
constexpr sa_family_t IPv6 = AF_INET6;

constexpr sa_family_t TCP = SOCK_STREAM;
constexpr sa_family_t UDP = SOCK_DGRAM;


// Converts an IP-address and port to a socket address.
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

// Sends a message over the socket.
void Send(int socket, std::string message)
{
    ssize_t bytes_written = write(socket, message.c_str(), message.size());
    if (bytes_written == -1)
        throw std::runtime_error("Couldn't write to socket.");
}

// Retrieves a message over the socket.
// The function will halt and wait until a message becomes available.
// The function will only fetch a maximum of 'max_size_to_receive' characters.
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


// Establishes a connection on the socket pointed at by address an port.
// Will only allow 'max_number_of_clients' clients to connect to the socket.
int ConnectServer(const std::string& address, int port, int max_number_of_clients)
{
    // The steps involved in establishing a socket on the server side are as follows:
    //
    //     1. Create a socket with the socket() system call.
    //     2. Bind the socket to an address using the bind() system call. For a server socket on the Internet,
    //        an address consists of a port number on the host machine.
    //     3. Listen for connections with the listen() system call.

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

void sendMail(std::string target, std::string attachment)
{
    std::string smtp = "smtps://smtp.gmail.com:465";
    std::string from = "ciserver21@gmail.com";
    std::string cmd = "curl --url \'" + smtp + "\' --ssl-reqd " +
      "--mail-from \'" + from +"\' --mail-rcpt \'" + target +"\' "+
      "--upload-file " + attachment + " --user 'ciserver21@gmail.com:4Urth2NN' --insecure";

    system(cmd.c_str());
}

int main(int argc, char* argv[])
{
    std::string address = "0.0.0.0";
    int port = 8080;
    int maximum_clients = 1;
    size_t max_size_to_receive = 100000;

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


        std::string received_message = Receive(client_socket, max_size_to_receive);
        std::cout << "---- Receiving ----\n" <<  received_message << std::endl;

        if (received_message.find("X-GitHub-Event: pull_request") == std::string::npos)
            continue;

        unsigned i = 0;
        for (; i < received_message.size(); ++i)
            if (received_message[i] == '{')
                break;

        try
        {
            std::cout << "JSON:\n" << received_message.substr(i, received_message.size()) << std::endl;
            Parser parser(received_message.substr(i, received_message.size()));


            // POST /repos/:owner/:repo/statuses/:sha
            std::string body = "{\n"
                               "\"state\": \"pending\",\n"
                               "\"target_url\": \"" + parser.GetPrURL() + "\",\n"
                               "\"description\": \"The build has started!\",\n"
                               "\"context\": \"default\"\n"
                               "};\n";
            std::string message =
                    "HTTP/1.1 200 OK\n"
                    "Content-Length: " + std::to_string(body.size()) + "\n"
                    "Connection: close\n"
                    "Content-Type: text/html\n"
                    "\n" + body;

            std::cout << "---- Sending ----\n" << message << std::endl;
            Send(client_socket, message);

            std::cout << parser.GetCloneURL() << std::endl;
            std::cout << parser.GetAction()   << std::endl;
            std::cout << parser.GetPrTime()   << std::endl;
            std::cout << parser.GetPrTitle()  << std::endl;
            std::cout << parser.GetPrUser()   << std::endl;
            std::cout << parser.GetPrBody()   << std::endl;
            std::cout << parser.GetPrURL()    << std::endl;

            report information = IntegrationTest(parser.GetPrSha(), parser.GetCloneURL(), "origin/master");

            if (information.errorcode == 0)
            {
                // Send a mail telling the person that the build pased
                sendMail("fpih@kth.se", "./resources/mail_resp_passed.txt");

                std::string body = "{\n"
                                   "\"state\": \"passed\",\n"
                                   "\"target_url\": \"" + parser.GetPrURL() + "\",\n"
                                   "\"description\": \"The build was successful!\",\n"
                                   "\"context\": \"default\"\n"
                                   "};\n";
                std::string message =
                        "HTTP/1.1 200 OK\n"
                        "Content-Length: " + std::to_string(body.size()) + "\n"
                        "Connection: close\n"
                        "Content-Type: text/html\n"
                        "\n" + body;

                std::cout << "---- Sending ----\n" << message << std::endl;
                Send(client_socket, message);
            }
            else
            {
                // Send a mail telling the person that the build failed
                sendMail("fpih@kth.se", "./resources/mail_resp_failed.txt");

                std::string body = "{\n"
                                   "\"state\": \"failed\",\n"
                                   "\"target_url\": \"" + parser.GetPrURL() + "\",\n"
                                   "\"description\": \"The build has failed!\",\n"
                                   "\"context\": \"default\"\n"
                                   "};\n";
                std::string message =
                        "HTTP/1.1 200 OK\n"
                        "Content-Length: " + std::to_string(body.size()) + "\n"
                        "Connection: close\n"
                        "Content-Type: text/html\n"
                        "\n" + body;
                std::cout << "---- Sending ----\n" << message << std::endl;
                Send(client_socket, message);
            }

        }
        catch (const nlohmann::detail::parse_error& error)
        {
            std::cerr << "Couldn't read event." << std::endl;
            std::string body = "{\n"
                               "\"state\": \"error\",\n"
                               "\"target_url\": \"\",\n"
                               "\"description\": \"The build has failed!\",\n"
                               "\"context\": \"default\"\n"
                               "};\n";
            std::string message =
                    "HTTP/1.1 200 OK\n"
                    "Content-Length: " + std::to_string(body.size()) + "\n"
                    "Connection: close\n"
                    "Content-Type: text/html\n"
                    "\n" + body;
            std::cout << "---- Sending ----\n" << message << std::endl;
            Send(client_socket, message);
        }
    }

    close(listen_socket);
}









