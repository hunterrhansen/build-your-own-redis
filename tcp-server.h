#pragma once

#include <string>
class TCPServer {
    public:
        TCPServer(std::string fd, std::string address);
    private:
        std::string fd;
        std::string address;
};