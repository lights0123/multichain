#!/bin/sh

#Run as: ./prepare-for-deploy.sh platformName versionNumber

tar -czf "actumcrypto-multichain-$1-$2.tar.gz" actumcrypto/*
