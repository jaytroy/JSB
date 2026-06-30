FROM ubuntu:24.04 AS build

RUN apt-get update && apt-get install -y  \
    cmake \
    build-essential \
    pkg-config \
    libncurses-dev

COPY /libraries/JSBSim_*.deb /libraries/JSBSim-devel_*.deb /tmp/
RUN apt-get install -y /tmp/JSBSim_*.deb /tmp/JSBSim-devel_*.deb \
    && rm /tmp/*.deb

WORKDIR /app

COPY CMakeLists.txt .
COPY ./src ./src/

ENV JSBGITDIR=/app/jsbsim/

RUN rm -rf build
RUN cmake -B build
RUN cmake --build build

RUN ls

CMD ["./build/JSB"]
