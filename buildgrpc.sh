export DEBIAN_FRONTEND=noninteractive
export WORK="$HOME/grpc"
export MYLOCALBIN="$HOME/mybin"
export PATH="$PATH:$MYLOCALBIN/bin"
cd $HOME
apt-get update \
    && apt-get install -y cmake build-essential autoconf libtool pkg-config git \
    && git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc \
    && mkdir -p "$MYLOCALBIN" \
    && mkdir -p "$WORK/cmake/build"\
    && cd "$WORK/cmake/build" \
    && cmake -DgRPC_INSTALL=ON -DgRPC_BUILD_TESTS=OFF -DCMAKE_INSTALL_PREFIX=$MYLOCALBIN ../.. \
    && make -j && make install \
    && mkdir -p "$WORK/examples/cpp/helloworld/cmake/build" \
    && cd "$WORK/examples/cpp/helloworld/cmake/build" \
    && cmake -DCMAKE_PREFIX_PATH=$MYLOCALBIN ../.. \
    && make -j