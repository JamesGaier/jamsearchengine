#!/bin/bash

# gets a newer version of cmake than default version available
sudo pip3 install cmake
sudo dnf install boost, boost-devel, uuid-devel, doxygen, jsoncpp-devel, yaml-cpp-devl, yaml-cpp, python3-flask-cors
meson builddir
ninja-build -C builddir install

# only rebuild drogon if you say to
# compelation takes a really long time and this should only be done if
# drogon is updated
if [ "$1" = "--build-drogon" ]; then
    echo "Building Drogon"
    ./build_drogon.sh
fi

# puts web-crawler binary in crawler-deps folder
if [ "$2" = "--build-web-crawler" ]; then
    echo "Building Web Crawler"
    ./docker/docker.sh
fi

# build drogon webserver stuff
cd web/WebCrawlerBackend/build
cmake ..
make
cd -
