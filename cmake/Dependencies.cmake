set(SOLITAIRE2_CATCH2_MINIMUM_VERSION 3.8.1)
set(SOLITAIRE2_PYBIND11_MINIMUM_VERSION 2.13.6)

find_package(Catch2 ${SOLITAIRE2_CATCH2_MINIMUM_VERSION} CONFIG QUIET)
if(Catch2_FOUND)
    message(STATUS "Using installed Catch2 ${Catch2_VERSION}")
else()
    message(STATUS "Installed Catch2 >= ${SOLITAIRE2_CATCH2_MINIMUM_VERSION} not found; fetching Catch2 v${SOLITAIRE2_CATCH2_MINIMUM_VERSION}")
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG v3.8.1
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(Catch2)
endif()

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 ${SOLITAIRE2_PYBIND11_MINIMUM_VERSION} CONFIG QUIET)
if(pybind11_FOUND)
    message(STATUS "Using installed pybind11 ${pybind11_VERSION}")
else()
    message(STATUS "Installed pybind11 >= ${SOLITAIRE2_PYBIND11_MINIMUM_VERSION} not found; fetching pybind11 v${SOLITAIRE2_PYBIND11_MINIMUM_VERSION}")
    include(FetchContent)
    set(FETCHCONTENT_QUIET OFF)
    FetchContent_Declare(
        pybind11
        GIT_REPOSITORY https://github.com/pybind/pybind11.git
        GIT_TAG v2.13.6
        GIT_SHALLOW TRUE
    )
    FetchContent_MakeAvailable(pybind11)
endif()
