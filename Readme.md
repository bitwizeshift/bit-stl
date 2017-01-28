# `bit::stl` Standard library

[![Build Status](https://travis-ci.org/bitwizeshift/bit-stl.svg?branch=master)](https://travis-ci.org/bitwizeshift/bit-stl)
[![Build status](https://ci.appveyor.com/api/projects/status/50vmwi1src4ihwmk/branch/master?svg=true)](https://ci.appveyor.com/project/bitwizeshift/bit-stl/branch/master)
[![Github Issues](https://img.shields.io/github/issues/bitwizeshift/bit-stl.svg)](http://github.com/bitwizeshift/bit-stl/issues)
[![Tested Compilers](https://img.shields.io/badge/compilers-clang-blue.svg)](#tested-compilers)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://bitwizeshift.github.io/bit-stl)
[![GitHub License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bitwizeshift/bit-stl/master/LICENSE.md)
[![Github Releases](https://img.shields.io/github/release/bitwizeshift/bit-stl.svg)](https://github.com/bitwizeshift/bit-stl/releases)

## What is `bit::stl`?

This is the standsard template library for various personal projects of mine.
It is both an extension to the standard library, along with a custom implementation
of future-proof components (such as c++17 features like std::string_view that is not
available to a c++14 compiler).

All functions and types are written to replicate the standard namespace's naming
conventions for easy use and upgradeability to new c++ library features at is released.

All definitions reside within `namespace bit`, short for `bitwize`/`bitwize_shift` (my common username).
