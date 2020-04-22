A program that showcases the encoded-text functionality of Terminal++

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

See [https://github.com/KazDragon/terminalpp/wiki/String-To-Elements-Protocol](Terminal++'s encoding protocol) for information 
about how to encode text to be displayed on the terminal.  As a start, running the program:

    ./tprint "\U262F" 

will display a yin-yang symbol.