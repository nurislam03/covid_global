FROM        ubuntu:20.04

ARG DEBIAN_FRONTEND=noninteractive
# update and install dependencies
RUN         apt-get update \
    && apt-get install -y \
    wget 
RUN  apt-get update \
    && apt-get install -y \
    make 
RUN  apt-get update \
    && apt-get install -y \
    git \
    curl 
RUN apt-get update \
    && apt-get install -y cmake 
RUN apt-get install -y \
    gcc-9 g++-9  \
    && update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-9 100 \
    && update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-9 100
RUN apt-get install -y openssl\
    libssl-dev\
    libsasl2-dev \
    pkg-config

RUN wget https://github.com/mongodb/mongo-c-driver/releases/download/1.17.6/mongo-c-driver-1.17.6.tar.gz\
    && tar xzf mongo-c-driver-1.17.6.tar.gz\
    && cd mongo-c-driver-1.17.6\
    && mkdir cmake-build\
    && cd cmake-build\
    && cmake -DENABLE_AUTOMATIC_INIT_AND_CLEANUP=OFF .. \
    && cmake --build . \
    && cmake --build . --target install

# RUN cd mongo-c-driver-1.17.6 \
#    && cd cmake-build\
#    && cmake --build . --target install

RUN curl -OL https://github.com/mongodb/mongo-cxx-driver/releases/download/r3.6.5/mongo-cxx-driver-r3.6.5.tar.gz 
    
RUN  tar -xzf mongo-cxx-driver-r3.6.5.tar.gz\
    && cd mongo-cxx-driver-r3.6.5/build\
    && cmake ..                                \
        -DCMAKE_BUILD_TYPE=Release          \
        -DCMAKE_INSTALL_PREFIX=/usr/local \
    && cmake --build . --target EP_mnmlstc_core \
    && cmake --build . \
    && cmake --build . --target install

RUN apt-get install -y unzip

RUN wget https://github.com/mariusbancila/croncpp/archive/refs/heads/master.zip \
    && unzip master.zip \
    && cd croncpp-master \
    && mkdir build \
    && cd build \
    && cmake .. \
    && cmake --build . \
    && cmake --build . --target install

COPY . /app

RUN cd app \
    && make

WORKDIR /app

ENV DB_CONNECTION_URL='mongodb+srv://cta-backend:cta-backend@mongobookshop.n7agh.mongodb.net/MongoBookShop?retryWrites=true&w=majority'
ENV DB_NAME='cta-backend'
ENV NOTIFICATION_SERVER_URL='https://ctaemailserver.herokuapp.com'
ENV NOTIFICATION_CRONTAB='0 */1 * * * ?'
ENV SERVER_PORT=4000
ENV FRONTEND_DETAILS_PAGE_URL='https://example.com'
ENV LD_LIBRARY_PATH='/usr/local/lib'

# EXPOSE ${SERVER_PORT}

CMD ["./ctaserver"]