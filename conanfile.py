from conans import ConanFile, CMake, tools


class TerminalppConan(ConanFile):
    name = "terminalpp"
    version = "1.3.4"
    license = "MIT"
    author = "KazDragon"
    url = "https://github.com/KazDragon/terminalpp"
    description = "A C++ library for interacting with ANSI terminal windows"
    topics = ("terminal-emulators", "ansi-escape-codes")
    settings = "os", "compiler", "build_type", "arch"
    exports = "*.hpp", "*.in", "*.cpp", "CMakeLists.txt", "*.md", "LICENSE"
    options = {"shared": [True, False]}
    default_options = {"shared": False}
    requires = ("fmt/[>=5.3]@bincrafters/stable",
                "boost_optional/[>=1.69]@bincrafters/stable",
                "boost_range/[>=1.69]@bincrafters/stable",
                "boost_variant/[>=1.69]@bincrafters/stable")
    build_requires = ("gtest/[>=1.8.1]@bincrafters/stable")
    generators = "cmake"

    def build(self):
        cmake = CMake(self)
        cmake.definitions["BUILD_SHARED_LIBS"] = self.options.shared
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("*.hpp", dst="include", src="include")
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.so.*", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["terminalpp"]

