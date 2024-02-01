#!/usr/bin/env bash

set -e

# for each target build the project
DISTROS="\
    alpine \
    arch \
    debian \
    fedora \
    ubuntu"

for DISTRO in $DISTROS; do
    echo "Building for $DISTRO"
    BUILDER=$DISTRO-builder
    ./bootstrap.sh pod create --name=$BUILDER --image=$DISTRO || true
    ./bootstrap.sh --pod=$BUILDER wk dist --distro=$DISTRO $@
done

./bootstrap.sh ck pod kill --all
docker system prune -fa
