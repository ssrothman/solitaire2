#include <pybind11/pybind11.h>

#include <solitaire2/version.hpp>

namespace py = pybind11;

PYBIND11_MODULE(_core, module) {
    module.doc() = "Python bindings for the solitaire2 backend scaffold.";
    module.attr("__version__") = solitaire2::version;
}
