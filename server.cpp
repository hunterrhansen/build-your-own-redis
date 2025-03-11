#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <stdexcept>
#include <cstdio>
#include <cstring>
#include <iostream>


static void do_something(int connfd) {
    char rbuf[64] = {};
    ssize_t n = ::read(connfd, rbuf, sizeof(rbuf) - 1);
    if (n < 0) {
        perror("read error");
        close(connfd);
        return;
    }
    printf("client says: %s\n", rbuf);

    char wbuf[] = "world";
    ssize_t w = write(connfd, wbuf, strlen(wbuf));
    if (w < 0) {
        perror("write error");
        return;
    }
}

int main() {
    // 1. create socket
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        perror("Failed to create socket");
        return 1;
    }

    // 2. set socket options
    int val = 1;
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &val, sizeof(val)) < 0) {
        perror("Failed to set socket options");
        close(fd);
        return 1;
    }

    // 3. bind to an address
    struct sockaddr_in addr = {};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);        // port
    addr.sin_addr.s_addr = htonl(0);    // wildcard IP 0.0.0.0
    int rv = bind(fd, (const struct sockaddr *)&addr, sizeof(addr));
    if (rv) { 
        perror("Failed to bind socket");
        close(fd);
        return 1;
    }

    // 4. listen
    rv = listen(fd, SOMAXCONN);
    if (rv) { 
        perror("Failed to listen on socket");
        close(fd);
        return 1;
    }

    // 5. accept connections
    while (true) {
        struct sockaddr_in client_addr = {};
        socklen_t addrlen = sizeof(client_addr);
        int connfd = accept(fd, (struct sockaddr *)&client_addr, &addrlen);
        if (connfd < 0) {
            continue;   // error
        }

        do_something(connfd);

        close(connfd);
    }
}