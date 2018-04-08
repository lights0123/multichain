#!/bin/sh

#Run as: ./prepare-for-deploy.sh isWindowsBuild platformName versionNumber

if [ "$1" = true ]
then
	mkdir actumcrypto
	mv src/*.exe actumcrypto/
	rename s/multichain/actumcrypto/ actumcrypto/*.exe
	tar -czf "actumcrypto-multichain-$2-$3.tar.gz" actumcrypto/*.exe
else
	mkdir actumcrypto
	find src -maxdepth 1 -perm -111 -type f | xargs mv -t actumcrypto/
	rename s/multichain/actumcrypto/ actumcrypto/*
	tar -czf "actumcrypto-multichain-$2-$3.tar.gz" actumcrypto/*
fi
