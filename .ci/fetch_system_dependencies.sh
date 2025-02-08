#!/bin/bash
if [ -z ${EXTERNAL_ROOT+x} ]; then echo EXTERNAL_ROOT not set; exit 1; fi

export EXTERNAL_BUILD_ROOT=$HOME/external_build

mkdir "$EXTERNAL_BUILD_ROOT" || true

# libfmt and Boost dependencies installed via apt in build.yml

# Install googletest dependency
if [ ! -f "$EXTERNAL_ROOT/include/gtest/gtest.h" ]; then
    cd "$EXTERNAL_BUILD_ROOT";
    wget https://github.com/google/googletest/archive/release-1.11.0.tar.gz;
    tar -xzf release-1.11.0.tar.gz;
    cd googletest-release-1.11.0;
    cmake -DCMAKE_INSTALL_PREFIX="$EXTERNAL_ROOT" .;
    make -j2 && make install;
fi
