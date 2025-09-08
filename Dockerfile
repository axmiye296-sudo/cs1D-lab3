# Dockerfile
FROM ubuntu:22.04

# Install build tools and PostgreSQL development libraries
RUN apt-get update && apt-get install -y \
    build-essential \
    g++ \
    make \
    libpqxx-dev \
    libpq-dev \
    file \
    && rm -rf /var/lib/apt/lists/*

# Set working directory
WORKDIR /app

# Copy source code
COPY . .

# Build the application
RUN make clean && make all

# Debug: Check binary architecture
RUN echo "System architecture:"
RUN uname -m
RUN echo "Binary architecture:"
RUN file ./build/main

# Default command
CMD ["./build/main"]