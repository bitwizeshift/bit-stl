# `bit::stl` Standard library

[![Build Status](https://travis-ci.org/bitwizeshift/bit-stl.svg?branch=master)](https://travis-ci.org/bitwizeshift/bit-stl)
[![Build status](https://ci.appveyor.com/api/projects/status/q3k3qns2amtdhliy?svg=true)](https://ci.appveyor.com/project/bitwizeshift/bit-stl)
[![Github Issues](https://img.shields.io/github/issues/bitwizeshift/bit-stl.svg)](http://github.com/bitwizeshift/bit-stl/issues)
[![Tested Compilers](https://img.shields.io/badge/compilers-clang-blue.svg)](#tested-compilers)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://bitwizeshift.github.io/bit-stl)
[![GitHub License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bitwizeshift/bit-stl/master/LICENSE.md)
[![Github Releases](https://img.shields.io/github/release/bitwizeshift/bit-stl.svg)](https://github.com/bitwizeshift/bit-stl/releases)

## What is `bit::stl`?

This is the standard template library for various personal projects of mine.
It is both an extension to the C++ standard library, along with a custom implementation
of future-proof components (such as c++17 features like std::string_view that is not
available to a c++14 compiler).

All functions and types are written to replicate the standard namespace's naming
conventions for easy use and upgradeability to new c++ library features at is released.

**Pedantic Note**: The name `stl` is not meant as a mistaken reference to the c++ standard
library, which is often wrongfully referred to as `stl`. It's named this since it truly is
a `template`/`inline` library that is used in other projects.

## Namespacing

The namespace convention is simple; all components reside within `namespace bit::stl`.

There are two common `inline namespace`s as well that can be brought in independently; `inline namespace casts` and `inline namespace literals`. The `casts` namespace can be used to bring things like `pointer_cast` or `narrow_cast` to the top-level without
requiring polluting the entire global namespace, whereas the `literals` namespace, much like the standard library, brings in
any `operator ""` literals.
