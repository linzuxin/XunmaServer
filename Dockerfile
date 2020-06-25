FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive
RUN apt-get update \
&& apt-get install -y cmake build-essential autoconf libtool pkg-config git \
&& git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc \
&& mkdir -p ~/.local /grpc/cmake/build /grpc/examples/cpp/helloworld/cmake/build \
&& cd /grpc/cmake/build \
&& cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=~/.local ../.. \
&& make -j && make install \
&& cd /grpc/examples/cpp/helloworld/cmake/build \
&& cmake -DCMAKE_PREFIX_PATH=~/.local ../.. \
&& make -j \