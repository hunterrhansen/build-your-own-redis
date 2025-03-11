#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstring>
#include <cstdio>
#include <iostream>

int main() {
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        close(fd);
        std::cerr << "Failed to connect to the socket" << std::endl;
    }

    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = ntohs(1234);
    addr.sin_addr.s_addr = ntohl(INADDR_LOOPBACK);  // 127.0.0.1
    int rv = connect(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) {
        close(fd);
        std::cerr << "failed to connect" << std::endl;
    }

    char msg[] = "hello";

    write(fd, msg, strlen(msg));

    char rbuf[64] = {};
    ssize_t n = read(fd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        close(fd);
        std::cerr << "failed to read" << std::endl;
    }
    printf("server says: %s\n", rbuf);
    close(fd);
}