#include <iostream>
#include "tcp-server.h"

int main() {
    std::cout << "Hello, redis!" << std::endl;
    
    TCPServer server("fd", "address");

    return 0;
}