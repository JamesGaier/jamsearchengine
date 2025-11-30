#!/bin/bash

# log all shell commands to terminal
set -x

# global variables
SOURCE_FILE=web.tar.gz
WEB_DIR=/var/www/jamsearchengine.com
SOURCE=/opt/web
SOURCE_PATH=/opt/web/$SOURCE_FILE
DEPLOY_DIR=web
IMAGES_DIR=images
WEB_CRAWLER_IMAGE=web-crawler-v0.1.tar.gz
WEB_SERVER_IMAGE=web-server-v0.1.tar.gz

# if the deploy source isn't in the folder exit the job
if [[ -z "$( ls -A $SOURCE )" ]]; then
    echo "deploy folder is empty, exiting..."
    exit 0
fi

echo "Deploy folder contains update.  Updating..."

# move my source code to the web directory
mv -v $SOURCE_PATH $WEB_DIR
pushd $WEB_DIR 

# extract the code
tar xvf $SOURCE_FILE

# copy the code out of the folder into the web directory and clean up junk
cp -r $DEPLOY_DIR/* .
rm -r $DEPLOY_DIR/
rm $SOURCE_FILE

# load the images
TO_DELETE="$(podman images -qa)"

if [[ ! -z "$TO_DELETE" ]]; then
    podman rmi $TO_DELETE -f
fi
cd $IMAGES_DIR
podman-compose down
podman system prune --all -f
podman load -i $WEB_CRAWLER_IMAGE
podman load -i $WEB_SERVER_IMAGE
podman-compose up -d
cd -

# stop logging all shell commands to terminal
set +x
