#include "client.hpp"

namespace Freedom {
    int Client::get() {
        struct hostent *host = gethostbyname("https://www.google.com/");

        if (host == NULL || host->h_addr == NULL) {
            std::cout << "Error retrieving DNS information." << std::endl;
            exit(1);
        }

        bzero(&client, sizeof(client));
        client.sin_family = AF_INET;
        client.sin_port = htons(PORT);
        memcpy(&client.sin_addr, host->h_addr, host->h_length);

        sock = socket(AF_INET, SOCK_STREAM, 0);

        if (sock < 0) {
            std::cout << "Error creating socket." << std::endl;
            exit(1);
        }

        if (connect(sock, (struct sockaddr *) &client, sizeof(client)) < 0) {
            close(sock);
            std::cout << "Could not connect" << std::endl;
            exit(1);
        }

        std::stringstream ss;
        ss << "GET /3/movie/" << 550 << "?api_key=xxx HTTP/1.1\r\n"
           << "Host: api.themoviedb.org\r\n"
           << "Accept: application/Json\r\n"
           << "\r\n\r\n";
        std::string request = ss.str();

        if (send(sock, request.c_str(), request.length(), 0) != (int) request.length()) {
            std::cout << "Error sending request." << std::endl;
            exit(1);
        }

        char cur;
        while (read(sock, &cur, 1) > 0) {
            std::cout << cur;
        }

        return 0;

    }
} // namespace Freedom

