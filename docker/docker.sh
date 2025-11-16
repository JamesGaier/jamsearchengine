#!/bin/bash

# NOTE: THIS SCRIPT IS MEANT TO BE RUN FROM THE ROOT OF THE PROJECT BY build.sh
# RUNNING THIS SCRIPT FROM ANYWHERE ELSE WILL NOT WORK BECAUSE OF RELATIVE PATHS

# remove old containers
podman rmi --force $(podman images -aq)

# get dependencies
mkdir -p docker/crawler-deps
mkdir -p docker/web-server-deps
mkdir -p docker/images
cp \
    builddir/libjam-web-crawler-lib.so \
    builddir/subprojects/tomlplusplus-3.4.0/src/libtomlplusplus.so.3 \
    builddir/jam-web-crawler \
    /lib64/libstdc++.so.6 \
    /lib64/libgcc_s.so.1 \
    /lib64/libc.so.6 \
    /usr/local/lib64/libcurl.so.4 \
    /usr/local/lib64/libgumbo.so.2 \
    /usr/local/lib64/libsqlitecpp.so.0 \
    /lib64/libm.so.6 \
    /lib64/libsqlite3.so.0 \
    /lib64/ld-linux-x86-64.so.2 \
    /lib64/libssl.so.3 \
    /lib64/libcrypto.so.3 \
    /lib64/libz.so.1 \
    /lib64/libzstd.so.1 \
    docker/crawler-deps/ 


cp \
    web/WebCrawlerBackend/build/WebCrawlerBackend \
    web/WebCrawlerBackend/config.yaml \
    builddir/subprojects/tomlplusplus-3.4.0/src/libtomlplusplus.so.3 \
    /lib64/libssl.so.3 \
    /lib64/libcrypto.so.3 \
    /usr/local/lib64/libjsoncpp.so.26 \
    /lib64/libyaml-cpp.so.0.8 \
    /lib64/libossp-uuid.so.16 \
    /lib64/libsqlite3.so.0 \
    /lib64/libz.so.1 \
    /lib64/libstdc++.so.6 \
    /lib64/libm.so.6 \
    /lib64/libgcc_s.so.1 \
    /lib64/libc.so.6 \
    /lib64/ld-linux-x86-64.so.2 \
    docker/web-server-deps

# build docker image
IMAGE_NAME_CRAWLER="jam/webcrawler:v0.1"
podman build -t  $IMAGE_NAME_CRAWLER -f $(pwd)/docker/web-crawler/Dockerfile .

IMAGE_NAME_WEB_SERVER="jam/webserver:v0.1"
podman build -t $IMAGE_NAME_WEB_SERVER -f $(pwd)/docker/backend-server/Dockerfile .

# export docker image as tarball file
podman save $IMAGE_NAME_CRAWLER | gzip > docker/images/web-crawler-v0.1.tar.gz
podman save $IMAGE_NAME_WEB_SERVER | gzip > docker/images/web-server-v0.1.tar.gz

# clean up deps
rm -rf docker/crawler-deps
rm -rf docker/web-server-deps