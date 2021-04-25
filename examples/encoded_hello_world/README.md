A program that shows off some encoded-text functionality of Terminal++

To build: you will need the Conan remotes that are registered with the following commands:

```
conan remote add conan-center https://conan.bintray.com
conan remote add kazdragon https://kazdragon.jfrog.io/artifactory/api/conan/conan-public
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

    ./encoded_hello_world

will display "Hello" in red, ", World!" in green, and follow that up with a default-coloured smiley.
