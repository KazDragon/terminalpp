A program that showcases some basic functionality of Terminal++

To build: you will need the Conan remotes that are registered with the following commands:

```
conan remote add conan-center https://conan.bintray.com
conan remote add bincrafters https://api.bintray.com/conan/bincrafters/public-conan
conan remote add kazdragon-conan https://api.bintray.com/conan/kazdragon/conan-public
```

Conan packages are then installed as following (assuming you are in the examples/tprint folder):

```
conan install -s compiler.libcxx=libstdc++11 -s cppstd=14 --build=missing .
```

You can then build with:

```
cmake .
make -j
```

    ./positioned smiley

will print a smiley character to the top left corner of the terminal.