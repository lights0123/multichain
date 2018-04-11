#!/bin/sh

#Run as: ./prepare-for-deploy.sh isWindowsBuild

if [ "$1" = true ]
then
	mkdir actumcrypto
	mv src/*.exe actumcrypto/
	rename s/multichain/actumcrypto/ actumcrypto/*.exe
else
	mkdir actumcrypto
	find src -maxdepth 1 -perm -111 -type f | xargs -I {} mv {} actumcrypto/
	rename s/multichain/actumcrypto/ actumcrypto/*
fi
