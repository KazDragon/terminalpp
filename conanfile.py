from conan import ConanFile
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps


class TerminalppConan(ConanFile):
    name = "terminalpp"
    license = "MIT"
    author = "KazDragon"
    url = "https://github.com/KazDragon/terminalpp"
    description = "A C++ library for interacting with ANSI terminal windows"
    topics = ("terminal-emulators", "ansi-escape-codes")
    settings = "os", "compiler", "build_type", "arch"
    exports = "*.hpp", "*.in", "*.cpp", "CMakeLists.txt", "*.md", "LICENSE", "*.cmake"
    options = {
        "shared": [True, False],
        "coverage": [True, False],
        "sanitize": ["off", "address"],
    }
    default_options = {"shared": False, "coverage": False, "sanitize": "off"}
    requires = ("fmt/[>=5.3]", "boost/[>=1.69]", "gsl-lite/[=0.38]")
    generators = "CMakeDeps"

    def configure(self):
        self.options["boost"].without_test = True

    def generate(self):
        toolchain = CMakeToolchain(self)
        toolchain.variables["BUILD_SHARED_LIBS"] = self.options.shared
        toolchain.cache_variables["TERMINALPP_COVERAGE"] = self.options.coverage
        toolchain.cache_variables["TERMINALPP_SANITIZE"] = self.options.sanitize
        toolchain.cache_variables["TERMINALPP_VERSION"] = self.version
        toolchain.cache_variables["TERMINALPP_WITH_TESTS"] = "OFF"
        toolchain.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        cmake = CMake(self)
        cmake.install()
        # self.copy("*.hpp", dst="include", src="include")
        # self.copy("*.dll", dst="bin", keep_path=False)
        # self.copy("*.so", dst="lib", keep_path=False)
        # self.copy("*.so.*", dst="lib", keep_path=False)
        # self.copy("*.dylib", dst="lib", keep_path=False)
        # self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        if self.settings.build_type == "Debug":
            self.cpp_info.libs = ["terminalppd"]
        else:
            self.cpp_info.libs = ["terminalpp"]
