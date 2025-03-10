# Use Ubuntu as the base image
FROM ubuntu:22.04

# Install essential build tools and debugging utilities
RUN apt-get update && apt-get install -y \
    build-essential \
    cmake \
    gdb \
    g++ \
    netcat \
    strace \
    net-tools \
    tcpdump \
    valgrind \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy your source code
COPY . .

# Example build command (adjust based on your build system)
# RUN g++ -o redis-server main.cpp

# Expose the default Redis port (or whatever port you're using)
EXPOSE 6379

# Command to run your server (adjust based on your executable name)
# CMD ["./redis-server"]