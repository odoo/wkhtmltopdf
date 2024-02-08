#!/usr/bin/env bash

set -e

if [ -z "$CUTEKIT" ]; then
    export CUTEKIT="./bootstrap.sh"
fi

DISTRO=$1
shift

echo "Building for $DISTRO"
BUILDER=$DISTRO-builder
$CUTEKIT pod create --name=$BUILDER --image=$DISTRO || true
$CUTEKIT --pod=$BUILDER wk dist --distro=$DISTRO $@
$CUTEKIT pod kill --all
docker system prune -fa
