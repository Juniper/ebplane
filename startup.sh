#!/bin/bash

if [ -f /etc/redhat-release ] || [ -f /etc/centos-release ]; then
    yum update
    yum install elfutils-libelf
fi

if [ -f /etc/lsb-release ] && egrep -q 'DISTRIB_ID.*Ubuntu' /etc/lsb-release; then
    apt-get update
    apt-get install libelf-dev
fi
