#!/usr/bin/env bash

set -e

if [ -z "$CUTEKIT" ]; then
    export CUTEKIT="./bootstrap.sh"
fi

# for each target build the project
DISTROS="\
    alpine-3.18 \
    arch \
    debian-bookworm \
    fedora-39 \
    ubuntu-jammy"

for DISTRO in $DISTROS; do
    echo "Building for $DISTRO"
    BUILDER=$DISTRO-builder
    $CUTEKIT pod create --name=$BUILDER --image=$DISTRO || true
    $CUTEKIT --pod=$BUILDER wk dist --distro=$DISTRO $@
done

$CUTEKIT pod kill --all
docker system prune -fa
