FROM ubuntu:latest
RUN apt-get update
RUN apt-get install -y cmake
RUN echo cmake --version
RUN apt-get install -y build-essential autoconf libtool pkg-config
RUN apt-get install -y git
RUN git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc
RUN mkdir -p ~/.local
RUN mkdir -p ~/grpc/cmake/build
RUN cd ~/grpc/cmake/build
RUN cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=~/.local ../..
RUN make -j
RUN make install
RUN cd ~/grpc/examples/cpp/helloworld
RUN mkdir -p cmake/build
RUN pushd cmake/build
RUN cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
RUN make -j