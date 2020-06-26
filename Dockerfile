FROM ubuntu:latest
ENV DEBIAN_FRONTEND=noninteractive
ENV WORK="$HOME/grpc"
ENV LOCAL="$HOME/.local"
ENV PATH="$PATH:$LOCAL/bin"
WORKDIR $HOME
RUN apt-get update \
    && apt-get install -y cmake build-essential autoconf libtool pkg-config git \
    && git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc \
    && mkdir -p "$LOCAL" \
    && mkdir -p "$WORK/cmake/build"\
    && cd "$WORK/cmake/build" \
    && cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$LOCAL ../.. \
    && make -j && make install \
    && mkdir -p "$WORK/examples/cpp/helloworld/cmake/build" \
    && cd "$WORK/examples/cpp/helloworld/cmake/build" \
    && cmake -DCMAKE_PREFIX_PATH=$LOCAL ../.. \
    && make -j