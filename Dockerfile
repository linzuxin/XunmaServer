FROM ubuntu:latest
RUN ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update
RUN apt-get install -y cmake build-essential autoconf libtool pkg-config git
RUN git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc
RUN mkdir -p ~/.local /grpc/cmake/build /grpc/examples/cpp/helloworld/cmake/build
RUN cd /grpc/cmake/build
RUN cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=~/.local ../..
RUN make -j && make install
RUN cd /grpc/examples/cpp/helloworld/cmake/build
RUN cmake -DCMAKE_PREFIX_PATH=~/.local ../..
RUN make -j