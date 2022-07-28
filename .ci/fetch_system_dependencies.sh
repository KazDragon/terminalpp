#!/bin/bash
if [ -z ${EXTERNAL_ROOT+x} ]; then echo EXTERNAL_ROOT not set; exit 1; fi

export EXTERNAL_BUILD_ROOT=$HOME/external_build

mkdir "$EXTERNAL_BUILD_ROOT" || true

# libfmt and Boost dependencies installed via apt in build.yml

# Install gsl-lite dependency
if [ ! -f "$EXTERNAL_ROOT/include/gsl/gsl-lite.hpp" ]; then
    cd "$EXTERNAL_BUILD_ROOT";
    wget https://github.com/gsl-lite/gsl-lite/archive/v0.38.0.tar.gz;
    tar -xzf v0.38.0.tar.gz;
    cd gsl-lite-0.38.0;
    cmake -DCMAKE_INSTALL_PREFIX="$EXTERNAL_ROOT" -DGSL_LITE_OPT_BUILD_TESTS=Off .;
    make -j2 && make install;
fi

# Install googletest dependency
if [ ! -f "$EXTERNAL_ROOT/include/gtest/gtest.h" ]; then
    cd "$EXTERNAL_BUILD_ROOT";
    wget https://github.com/google/googletest/archive/release-1.10.0.tar.gz;
    tar -xzf release-1.10.0.tar.gz;
    cd googletest-release-1.10.0;
    cmake -DCMAKE_INSTALL_PREFIX="$EXTERNAL_ROOT" .;
    make -j2 && make install;
fi
