#!/bin/bash

# WHAT THIS SCRIPT DOES
# The purpose of this script is to send a tarball up to a server 


# HOW THIS SCRIPT INTERACTS WITH THE SERVER
# A cron job is setup on the web-server to run every 15 minutes
# That job will do the following:
# 1. copy the tarball to /var/www/jamsearchengine.com 
# 2. untar the tarball
# 3. copy all of the source to the parent directory
# 4. clean up any junk i.e. the tarball and extra directory that was created


# GLOBAL VARIABLES
SOURCE_FILE=web.tar.gz
WEB_DIR=web
DEPLOY_DIR=/opt/web

# For security reasons I only put the hostname here
SERVER_HOSTNAME=web-crawler

# compress the web directory into a tarball file
tar -czvf $SOURCE_FILE $WEB_DIR

# push the data to the server
rsync $SOURCE_FILE $SERVER_HOSTNAME:$DEPLOY_DIR
