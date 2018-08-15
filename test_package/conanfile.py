#!/usr/bin/env python

from os import getenv, path
from conans import ConanFile, CMake


class BitStlConanTest(ConanFile):
    generators = "cmake"
    settings = "os", "compiler", "arch", "build_type"
    username = getenv("CONAN_USERNAME", "bitwizeshift")
    channel = getenv("CONAN_CHANNEL", "experimental")

    requires = "BitStl/2.0.0@{}/{}".format(username, channel)

    def build(self):
        cmake = CMake(self)
        cmake.configure(build_dir="./")
        cmake.build()
        return

    def test(self):
        return
