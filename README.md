# solitaire2

A scaffold for a C++20 backend, Python bindings, Python tooling, unit tests, and performance/profiling entry points.

This repository intentionally contains no solitaire rules or production algorithms yet. It establishes the build, packaging, testing, performance, and profiling surfaces for later implementation.

## Requirements

- CMake 3.23 or newer
- A C++20 compiler
- Unix Makefiles or another supported CMake generator
- Python 3.10 or newer
- pip

During configuration, CMake first searches for installed Catch2 `>= 3.8.1` and pybind11 `>= 2.13.6` packages. If a suitable local package is unavailable, it downloads the pinned versions with `FetchContent`.

To point CMake at packages installed in a custom prefix, set `CMAKE_PREFIX_PATH`:

```sh
cmake --preset debug -DCMAKE_PREFIX_PATH=/path/to/packages
```

## Project Structure

```text
.
|-- CMakeLists.txt              # Main CMake targets, options, and install rules
|-- CMakePresets.json           # Debug/release configure, build, and test presets
|-- pyproject.toml              # pip/PEP 517 metadata and scikit-build-core setup
|-- cmake/
|   `-- Dependencies.cmake      # Installed-package lookup and FetchContent fallback
|-- include/solitaire2/         # Public C++ headers
|-- src/                        # C++ backend implementation
|-- bindings/                   # pybind11 extension module definitions
|-- apps/                       # Native application entry points
|-- perf/                       # Performance and profiling executable entry points
|-- python/solitaire2/          # Python package and CLI dispatcher
|-- tests/cpp/                  # Catch2 unit tests
|-- tests/python/               # pytest tests for Python bindings and tools
`-- README.md
```

The generated `build/` directory is intentionally excluded from version control.

## CMake Build

The supplied presets use the Unix Makefiles generator in this environment. The `debug` preset enables warnings-as-errors and Python bindings; the `release` preset enables release optimization and Python bindings.

### Debug build

```sh
cmake --preset debug
cmake --build --preset debug
ctest --preset debug
```

### Release build

```sh
cmake --preset release
cmake --build --preset release
```

### Install

Install the C++ library, headers, native executables, CMake package files, Python package, and built Python extension into a local prefix:

```sh
cmake --install build/debug --prefix build/install
```

The installed Python package can be checked with:

```sh
PYTHONPATH="$PWD/build/install" python -c 'import solitaire2; print(solitaire2.__version__)'
```

### CMake options

Options can be supplied after a preset or directly with `cmake -S . -B ...`:

| Option | Default | Description |
| --- | --- | --- |
| `SOLITAIRE2_BUILD_PYTHON` | `ON` | Build and install the pybind11 Python extension |
| `SOLITAIRE2_BUILD_TESTS` | `ON` | Build and register the Catch2 C++ tests |
| `CMAKE_BUILD_TYPE` | Preset-specific | Select `Debug` or `Release` for single-configuration generators |
| `CMAKE_COMPILE_WARNING_AS_ERROR` | Preset-specific | Treat compiler warnings as errors in the debug preset |
| `CMAKE_PREFIX_PATH` | Empty | Additional prefixes to search for installed dependencies |

For example, configure a build without tests and Python bindings:

```sh
cmake -S . -B build/minimal \
	-G "Unix Makefiles" \
	-DCMAKE_BUILD_TYPE=Release \
	-DSOLITAIRE2_BUILD_PYTHON=OFF \
	-DSOLITAIRE2_BUILD_TESTS=OFF
cmake --build build/minimal
```

## Python Build and Installation

The Python package uses `scikit-build-core`, which delegates the extension build to the same top-level CMake project.

Build and install a wheel:

```sh
python -m pip install build
python -m build --wheel
python -m pip install dist/*.whl
```

For an editable development installation with test dependencies:

```sh
python -m pip install -e '.[test]'
pytest
```

The Python CLI dispatches on its first argument:

```sh
solitaire2 scaffold
```

## Where Behavior Goes

Keep implementation organized by ownership:

- Add public backend types and functions to `include/solitaire2/`.
- Implement those C++ APIs in matching files under `src/`. Add new source files to the `solitaire2_backend` target in `CMakeLists.txt`.
- Expose intentionally supported backend APIs to Python in `bindings/module.cpp`; keep Python-facing conversion and convenience logic in the Python package where appropriate.
- Add Python tools and first-argument dispatch entries under `python/solitaire2/`.
- Put native command-line behavior in `apps/`, and keep performance or profiler drivers in `perf/`. These executables should call the backend rather than duplicate its logic.
- Add C++ behavior tests under `tests/cpp/` and Python binding/CLI tests under `tests/python/`. New C++ test source files must be added to the `solitaire2_cpp_tests` target.

The existing version surface is only build and packaging validation. The performance and profiling executables are entry-point scaffolds, not meaningful benchmarks yet.
