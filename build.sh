#!/bin/bash
set -e
cd packaging
./build compile-docker fedora38-x86_64 ../. ../build
