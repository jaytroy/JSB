FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y  \
    cmake \
    build-essential \
    pkg-config \
    libncurses-dev


WORKDIR /app

COPY CMakeLists.txt .
COPY src .

RUN rm -rf build
RUN cmake -B build
RUN cmake --build build

CMD ["../build/JSB"]

