#!/bin/bash
set -e
cd packaging
./build compile-docker bookworm-amd64 ../. ../build
