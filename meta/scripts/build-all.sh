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
    ck pod create --name=$BUILDER --image=$DISTRO || true
    ck --pod=$BUILDER wk dist --distro=$DISTRO $@
done

ck pod kill --all
docker system prune -fa
