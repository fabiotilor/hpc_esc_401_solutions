# Use a recent Ubuntu base image
FROM ubuntu:24.04 

# Install dependencies (g++ and make are required to compile)
RUN apt update && \
    DEBIAN_FRONTEND=noninteractive apt install -y g++ make && \
    rm -rf /var/lib/apt/lists/*

# Set the working directory inside the container
WORKDIR /app

# Copy the source code from your local machine (MacBook) into the container's /app directory
COPY . /app

# Compile the code (runs 'make' inside the container)
RUN make

# Set the command to run when the container starts
CMD ["./main"]
