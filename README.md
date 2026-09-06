# solitaire2

A scaffold for a C++20 backend, Python bindings, and Python tooling.

This repository intentionally contains no solitaire rules or production algorithms yet. It establishes the build, packaging, testing, performance, and profiling entry points for later implementation.

## Requirements

- CMake 3.23 or newer
- A C++20 compiler
- Ninja (for the provided presets)
- Python 3.10 or newer
- pip

During configuration, CMake first searches for installed Catch2 `>= 3.8.1` and pybind11 `>= 2.13.6` packages. If a suitable local package is unavailable, it downloads the pinned versions with `FetchContent`.

To point CMake at packages installed in a custom prefix, set `CMAKE_PREFIX_PATH`, for example:

```sh
cmake --preset debug -DCMAKE_PREFIX_PATH=/path/to/packages
```

## CMake workflow

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
cmake --install build/debug --prefix build/install
```

The build produces the `solitaire2` library, native CLI, performance and profiling executables, C++ tests, and Python extension module.

## Python workflow

Build and install the wheel into an environment with:

```sh
python -m pip install build
python -m build
python -m pip install dist/*.whl
```

Install test dependencies and run Python tests from a development environment after building the extension:

```sh
python -m pip install -e '.[test]'
pytest
```

The Python CLI dispatches on its first argument:

```sh
solitaire2 scaffold
```

## Scope

The performance and profiling executables are entry-point scaffolds only. Profiling instrumentation, benchmark methodology, backend APIs, and additional Python tools will be added with the implementation work.
