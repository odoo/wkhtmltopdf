#!/bin/bash
set -e
cd packaging
./build compile-docker bionic-amd64 ../. ../build
