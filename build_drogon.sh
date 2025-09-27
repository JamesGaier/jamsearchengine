#!/bin/bash

cd subprojects/drogon
sudo ./build.sh
sudo chown -R $USER:$USER .