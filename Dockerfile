FROM ubuntu:20.04

# prepare env
RUN apt-get update && apt-get install -y --no-install-recommends \
        curl \
        apt-utils \
        openssl \
        ca-certificates

# install deps
RUN apt-get update && apt-get install -y --no-install-recommends \
        git \
        g++ \
        make \
        libssl-dev \
        libgflags-dev \
        libprotobuf-dev \
        libprotoc-dev \
        protobuf-compiler \
        libleveldb-dev \
        libcpprest-dev \
        libspdlog-dev \
        libyaml-cpp0.6 \
        libyaml-cpp-dev \
        libsnappy-dev && \
        apt-get clean -y
