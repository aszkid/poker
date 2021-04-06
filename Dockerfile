FROM ubuntu:latest
RUN apt update && DEBIAN_FRONTEND="noninteractive" apt install -y git build-essential libsdl2-dev python3 curl
ENV NVM_DIR /usr/local/nvm
RUN mkdir -p /usr/local/nvm && \
    curl -o- https://raw.githubusercontent.com/nvm-sh/nvm/v0.38.0/install.sh | bash && \
    . $NVM_DIR/nvm.sh && \
    nvm install node
RUN git clone https://github.com/emscripten-core/emsdk.git
WORKDIR /emsdk
RUN ./emsdk install latest && ./emsdk activate latest
WORKDIR /
COPY . /poker
WORKDIR /poker
EXPOSE 5000
CMD . $NVM_DIR/nvm.sh && \
    npm i -g nodemon serve && \
    cd /emsdk && \
    . ./emsdk_env.sh && \
    cd /poker && \
    npx nodemon -w src -w dist/index.html --ext c,h,html --exec "make all && npx serve dist || exit 1"
