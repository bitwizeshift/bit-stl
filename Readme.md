# `bit::stl` Standard library

[![Build Status](https://travis-ci.org/bitwizeshift/bit-stl.svg?branch=master)](https://travis-ci.org/bitwizeshift/bit-stl)
[![Build status](https://ci.appveyor.com/api/projects/status/q3k3qns2amtdhliy?svg=true)](https://ci.appveyor.com/project/bitwizeshift/bit-stl)
[![Github Issues](https://img.shields.io/github/issues/bitwizeshift/bit-stl.svg)](http://github.com/bitwizeshift/bit-stl/issues)
[![Tested Compilers](https://img.shields.io/badge/compilers-gcc%20%7C%20clang%20%7C%20msvc-blue.svg)](#tested-compilers)
[![Documentation](https://img.shields.io/badge/docs-doxygen-blue.svg)](http://bitwizeshift.github.io/bit-stl)
[![GitHub License](https://img.shields.io/badge/license-MIT-blue.svg)](https://raw.githubusercontent.com/bitwizeshift/bit-stl/master/LICENSE.md)
[![Github Releases](https://img.shields.io/github/release/bitwizeshift/bit-stl.svg)](https://github.com/bitwizeshift/bit-stl/tags)

## What is `bit::stl`?

This is the standard template library for various personal projects of mine.
It is both an extension to the C++ standard library, along with a custom implementation
of future-proof components (such as c++17 features like std::string_view that is not
available to a c++14 compiler).

## What does this library offer?

This is a core-library intended as an extension to the standard C++ library.

It offers various lightweight/useful utilities that are otherwise missing from the standard library.
For example:

- Extended type traits that support plural type comparison (`are_same`, `is_derived_from_all`, etc)
- GSL suggested types (`span`,`string_span`)
- Type-erased types (`array_view`,`map_view`,`set_view`)
- EBO generic storage types (`compressed_tuple`,`compressed_pair`)
- Dynamic constant types (`dynamic_size_constant`,`dynamic_index_constant`). These allow runtime _or_ compile-time constant values
- Circular buffers (`circular_deque`,`circular_queue`,`circular_buffer`)
- Concepts! (More on this below)
- Many other useful utilities

**Note** This is _not_ intended as a replacement for the C++ standard library; just a supplement.

### Concepts

This library includes a series of type-traits that validate types for satisfying specific concepts.

This is not a true C++ Concepts Light implementation, since it is unable to provide proper diagnostics for which requirements are missed. But it does offer type validation where necessary, allowing for better SFINAE on template types.

For example, to test whether a type satisfies a `Container` concept, a trait called `is_container` can be used

### Directory Structuring

Although this library does provide C++17 utilities, this primarily acts as a core library extension, and does not follow 1-1 with
the standard. Some example differences are:

- Composite standard headers are decomposed into individual header files. For example, type trait types are all in individual header files under a `traits` subsystem (unlike the standard's `type_traits` header that contains everything)
- The various utility headers are in a `utility` subsystem; likewise, container additions (like `string_view`) are under a `container` subsystem.

### Simple Namespacing

The namespace convention is simple; all components reside within `namespace bit::stl`.

There are two common `inline namespace`s as well that can be brought in independently; `inline namespace casts` and `inline namespace literals`. The `casts` namespace can be used to bring things like `pointer_cast` or `narrow_cast` to the top-level without
requiring polluting the entire global namespace, whereas the `literals` namespace, much like the standard library, brings in
any `operator ""` literals.

## Using this library

### Building & Installing

Building `bit::stl` is simple, and only requires a CMake version greater than 3.1, and a compatible compiler.

Fist, make a directory to build the library in, then build with CMake

```bash
mkdir build
cd build

cmake . -DBIT_STL_BUILD_UNIT_TESTS=Off -DBIT_STL_BUILD_INDEPENDENCE_TESTS=Off  # ... any additional toolchain parameters ...
cmake --build .
```

Omitting the `-DBIT_STL_BUILD_UNIT_TESTS=Off` will build unit tests; likewise `DBIT_STL_BUILD_INDEPENDENCE_TESTS=Off` will
build header-independence checks (building each header independently to ensure there are no header-order based transitive dependencies).

To install, run:

```bash
cmake --build . --target install
```

To change the output directory of the installation, you can export `BIT_HOME` to install to a specific directory

```bash
export BIT_HOME=/etc/bit
cmake --build . --target install
```

will install into `/etc/bit/`.

### Through a `cmake` subdirectory

Clone/copy/subtree the contents of this repository to a subdirectory, and `add_subdirectory` the directory containing `bit::stl`.

To add a dependency to the library, just add `target_link_libraries(<your target> [PUBLIC|INTERFACE|PRIVATE] bit::stl)`

## <a name="tested-compilers"></a>Tested Compilers

The following compilers are currently being tested through continuous integration with [Travis](https://travis-ci.org/bitwizeshift/bit-stl) and [AppVeyor](https://ci.appveyor.com/project/bitwizeshift/bit-stl/)

Note that `bit-stl` only works on compiler that provide proper conformance for c++14

| Compiler              | Operating System                   |
|-----------------------|------------------------------------|
| g++ 6.3.0             | Ubuntu 14.04.3 TLS                 |
| g++ 7.2.0             | Ubuntu 14.04.3 TLS                 |
| clang++ 3.9.0         | Ubuntu 14.04.3 TLS                 |
| clang++ 4.0.1         | Ubuntu 14.04.3 TLS                 |
| clang xcode 7.3       | Darwin Kernel 15.6.0 (OSX 10.11.6) |
| clang xcode 8.0       | Darwin Kernel 15.6.0 (OSX 10.11.6) |
| clang xcode 8.1       | Darwin Kernel 16.1.0 (OSX 10.12.1) |
| clang xcode 8.2       | Darwin Kernel 16.1.0 (OSX 10.12.1) |
| clang xcode 8.3       | Darwin Kernel 16.6.0 (OSX 10.12.5) |
| clang xcode 9.0       | Darwin Kernel 16.7.0 (OSX 10.12.6) |
| Visual Studio 2017    | Windows Server 2016 (x64)          |

## <a name="license"></a>License

<img align="right" src="http://opensource.org/trademarks/opensource/OSI-Approved-License-100x137.png">

The class is licensed under the [MIT License](http://opensource.org/licenses/MIT):

Copyright &copy; 2017 Matthew Rodusek

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
