A program that showcases the Canvas and Screen functionality of Terminal++

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

    ./shocking_pink

Assuming your terminal is in the usual 80x24 configuration, this will fill the console
with white x characters on a shocking pink background, with a single y character on a
light blue background at position (10, 15).  Your command prompt will likely continue 
from that location since that is where the cursor last rested.