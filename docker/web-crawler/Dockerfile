From ubuntu:plucky

MAINTAINER jamesg

WORKDIR /app

RUN mkdir -p /app/data

RUN apt-get update -y && apt-get install -y curl

COPY docker/crawler-deps/* /lib64
     
COPY docker/crawler-deps/jam-web-crawler config/config.toml .

EXPOSE 80


CMD ["/app/jam-web-crawler", "/app/config.toml"]