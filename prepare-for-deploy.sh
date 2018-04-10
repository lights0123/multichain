#!/bin/sh

#Run as: ./prepare-for-deploy.sh platformName versionNumber

tar -czf "actumcrypto-multichain-$2-$3.tar.gz" actumcrypto/*
