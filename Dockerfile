FROM ubuntu:20.04
WORKDIR /app
RUN apt-get update && DEBIAN_FRONTEND="noninteractive" TZ="America/New_York" \
apt-get -y install tzdata git wget unzip cmake libboost-all-dev build-essential \ 
libjsoncpp-dev uuid-dev protobuf-compiler libprotobuf-dev
ENV LD_LIBRARY_PATH=/app/libtorch/lib

COPY ./configs /app/configs
COPY ./models /app/models
COPY newsbot /app
COPY entrypoint.sh /app
COPY download_models.sh /app
RUN chmod +rx download_models.sh
RUN ./download_models.sh
RUN chmod +rx entrypoint.sh
RUN wget https://download.pytorch.org/libtorch/cpu/libtorch-cxx11-abi-shared-with-deps-1.5.0%2Bcpu.zip -P /app
RUN unzip libtorch-cxx11-abi-shared-with-deps-1.5.0+cpu.zip
ENTRYPOINT ["./entrypoint.sh"]






































