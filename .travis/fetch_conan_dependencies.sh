#!/bin/bash

# Install Conan for package dependencies
pip3 install --user --upgrade setuptools
pip3 install --user conan

# Important: Conan Center can be rather slow when fetching Boost,
# and will fail a decent portion of the time unless it is given
# a generous timeout.
conan config set general.request_timeout=120

# Install dependencies for our build using Conan.
mkdir build || true
cd build
conan install .. -s compiler.libcxx=libstdc++11 -s cppstd=14 --build=missing
cd -
