FROM ubuntu:latest
RUN apt update && DEBIAN_FRONTEND="noninteractive" apt install -y git build-essential libsdl2-dev python3
RUN git clone https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
RUN ./emsdk install latest && ./emsdk activate latest
WORKDIR /
COPY . /poker
RUN cd /emsdk && \
    . ./emsdk_env.sh && \
    cd /poker && \
    make all
WORKDIR /poker
EXPOSE 5000
CMD cd /emsdk && \
    . ./emsdk_env.sh && \
    cd /poker && \
    make serve
