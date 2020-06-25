FROM ubuntu:latest
RUN sudo apt install -y cmake
RUN echo cmake --version
RUN sudo apt install -y build-essential autoconf libtool pkg-config
RUN git clone --recurse-submodules -b v1.30.0 https://github.com/grpc/grpc
RUN cd grpc
RUN mdkir -p .local
RUN mkdir -p cmake/build
RUN pushd cmake/build
RUN cmake -DgRPC_INSTALL=ON \
      -DgRPC_BUILD_TESTS=OFF \
      -DCMAKE_INSTALL_PREFIX=~/.local \
      ../..
RUN make -j
RUN make install
RUN popd
RUN cd examples/cpp/helloworld
RUN mkdir -p cmake/build
RUN pushd cmake/build
RUN cmake -DCMAKE_PREFIX_PATH=$MY_INSTALL_DIR ../..
RUN make -j