#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <string>

namespace Freedom
{
    class Client
    {
    public:
        Client() = default;
        ~Client() = default;

        int sock;
        struct sockaddr_in client;
        int PORT = 80;

        int get();
    };
} // namespace Freedom

#endif // CLIENT_HPP
