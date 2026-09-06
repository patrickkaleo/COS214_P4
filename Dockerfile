FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && apt-get install -y --no-install-recommends \
        g++ \
        make \
        gdb \
        valgrind \
    && rm -rf /var/lib/apt/lists/*

WORKDIR /app

COPY makefile .
COPY include/ include/
COPY src/ src/

RUN make

CMD ["./taskforge"]
