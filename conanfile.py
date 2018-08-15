#!/usr/bin/env python3

from conans import ConanFile, CMake, tools

def extract_cmake_version():
    import re

    try:
        content = tools.load("CMakeLists.txt")
        major   = re.search(".*BIT_STL_VERSION_MAJOR ([0-9]+) .*", content).group(1)
        minor   = re.search(".*BIT_STL_VERSION_MINOR ([0-9]+) .*", content).group(1)
        patch   = re.search(".*BIT_STL_VERSION_PATCH ([0-9]+) .*", content).group(1)

        return "{}.{}.{}".format(major,minor,patch)
    except Exception:
        return None

class BitStlConan(ConanFile):
    name = "BitStl"
    version = extract_cmake_version()
    description = "A header-only standard template library"
    author = "bitwizeshift"
    generators = "cmake"
    exports_sources = ("CMakeLists.txt",
                       "CMake/Templates/*.in",
                       "CMake/Modules/*.cmake",
                       "include/*",
                       "LICENSE.md",
                       "docs/CMakeLists.txt",
                       "docs/Doxyfile.in")
    url = "https://github.com/bitwizeshift/bit-stl"
    license = "MIT License"
    options = {"install_docs" : [True,False]}
    default_options = "install_docs=False"

    def source(self):
        pass

    def build(self):
        pass

    def test(self):
        pass

    def package(self):
        cmake = CMake(self)
        cmake.definitions["BIT_STL_COMPILE_HEADER_SELF_CONTAINMENT_TESTS"] = "OFF"
        cmake.definitions["BIT_STL_COMPILE_UNIT_TESTS"] = "OFF"
        cmake.definitions["BIT_STL_GENERATE_DOCS"] = "ON" if self.options.install_docs else "OFF"
        cmake.definitions["BIT_STL_INSTALL_DOCS"]  = "ON" if self.options.install_docs else "OFF"
        cmake.configure()
        # If we have specified to build install_docs, install them
        if self.options.install_docs:
            cmake.build(target="stl_docs")
        cmake.install()

        self.copy(pattern="LICENSE.md", dst="licenses")
        return

    def package_id(self):
        self.info.header_only()
        return
