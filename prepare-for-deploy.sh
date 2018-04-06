#!/bin/sh

#Run as: ./prepare-for-deploy.sh isWindowsBuild platformName versionNumber

if [ "$1" = true ]
then
	mv src/*.exe .
	tar -czf "actumcrypto-multichain-$2-$3.tar.gz" *.exe
else
	cd src
	find . -maxdepth 1 -perm -111 -type f -print0 | xargs -0 tar -czf "../actumcrypto-multichain-$2-$3.tar.gz"
fi
