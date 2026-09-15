set(SOLITAIRE2_CATCH2_MINIMUM_VERSION 3.8.1)
set(SOLITAIRE2_PYBIND11_MINIMUM_VERSION 2.13.6)
set(SOLITAIRE2_RE2_MINIMUM_VERSION 11.0.0)
#set(SOLITAIRE2_ABSL_MINIMUM_VERSION 20250512)

find_package(Catch2 ${SOLITAIRE2_CATCH2_MINIMUM_VERSION} CONFIG QUIET)
if(Catch2_FOUND)
    message(STATUS "Using installed Catch2 ${Catch2_VERSION}")
else()
    #message(STATUS "Installed Catch2 >= ${SOLITAIRE2_CATCH2_MINIMUM_VERSION} not found; fetching Catch2 v${SOLITAIRE2_CATCH2_MINIMUM_VERSION}")
    #include(FetchContent)
    #set(FETCHCONTENT_QUIET OFF)
    #FetchContent_Declare(
    #    Catch2
    #    GIT_REPOSITORY https://github.com/catchorg/Catch2.git
    #    GIT_TAG v3.8.1
    #    GIT_SHALLOW TRUE
    #)
    #FetchContent_MakeAvailable(Catch2)
    message(FATAL_ERROR "Catch2 >= ${SOLITAIRE2_CATCH2_MINIMUM_VERSION} not found")
endif()

set(PYBIND11_FINDPYTHON ON)
find_package(pybind11 ${SOLITAIRE2_PYBIND11_MINIMUM_VERSION} CONFIG QUIET)
if(pybind11_FOUND)
    message(STATUS "Using installed pybind11 ${pybind11_VERSION}")
else()
    #message(STATUS "Installed pybind11 >= ${SOLITAIRE2_PYBIND11_MINIMUM_VERSION} not found; fetching pybind11 v${SOLITAIRE2_PYBIND11_MINIMUM_VERSION}")
    #include(FetchContent)
    #set(FETCHCONTENT_QUIET OFF)
    #FetchContent_Declare(
    #    pybind11
    #    GIT_REPOSITORY https://github.com/pybind/pybind11.git
    #    GIT_TAG v2.13.6
    #    GIT_SHALLOW TRUE
    #)
    #FetchContent_MakeAvailable(pybind11)
    message(FATAL_ERROR "pybind11 >= ${SOLITAIRE2_PYBIND11_MINIMUM_VERSION} not found")
endif()

find_package(re2 ${SOLITAIRE2_RE2_MINIMUM_VERSION} CONFIG QUIET)
if(re2_FOUND)
    message(STATUS "Using installed re2 ${re2_VERSION}")
else()
    #message(STATUS "Installed re2 >= ${SOLITAIRE2_RE2_MINIMUM_VERSION} not found; fetching re2 v${SOLITAIRE2_RE2_MINIMUM_VERSION}")
    #include(FetchContent)
    #set(FETCHCONTENT_QUIET OFF)
    #FetchContent_Declare(
    #    re2
    #    GIT_REPOSITORY https://github.com/google/re2.git
    #    GIT_TAG 2025-11-05
    #    GIT_SHALLOW TRUE
    #)
    #FetchContent_MakeAvailable(re2)
    message(FATAL_ERROR "re2 >= ${SOLITAIRE2_RE2_MINIMUM_VERSION} not found")

endif()

#find_package(absl  ${SOLITAIRE2_ABSL_MINIMUM_VERSION} CONFIG QUIET)
#if (absl_FOUND)
#    message(STATUS "Using installed absl ${absl_VERSION}")
#else()
#    message(FATAL_ERROR "absl >= ${SOLITAIRE2_ABSL_MINIMUM_VERSION} not found")
#endif()