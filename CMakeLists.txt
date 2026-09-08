cmake_minimum_required(VERSION 3.23)

project(solitaire2 VERSION 0.1.0 LANGUAGES CXX)

option(SOLITAIRE2_BUILD_PYTHON "Build the pybind11 Python extension" ON)
option(SOLITAIRE2_BUILD_TESTS "Build C++ tests" ON)

include(GNUInstallDirs)
include(CMakePackageConfigHelpers)
include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/Dependencies.cmake)

add_library(solitaire2_backend STATIC
	src/version.cpp
    src/gamestate/gamedeck.cpp
    src/gamestate/foundation.cpp
)
add_library(solitaire2::backend ALIAS solitaire2_backend)

target_include_directories(solitaire2_backend
	PUBLIC
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
		$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set_target_properties(solitaire2_backend PROPERTIES
	EXPORT_NAME backend
	POSITION_INDEPENDENT_CODE ON
)

add_executable(solitaire2_cli apps/solitaire2_cli.cpp)
target_link_libraries(solitaire2_cli PRIVATE solitaire2::backend)

add_executable(solitaire2_perf perf/solitaire2_perf.cpp)
target_link_libraries(solitaire2_perf PRIVATE solitaire2::backend)

add_executable(solitaire2_profile perf/solitaire2_profile.cpp)
target_link_libraries(solitaire2_profile PRIVATE solitaire2::backend)

if(SOLITAIRE2_BUILD_TESTS)
	add_executable(test_version tests/cpp/test_version.cpp)
    add_executable(test_cards tests/cpp/test_cards.cpp)
    add_executable(test_gamedeck tests/cpp/test_gamedeck.cpp)
    add_executable(test_foundation tests/cpp/test_foundation.cpp)

	target_link_libraries(test_version PRIVATE solitaire2::backend Catch2::Catch2WithMain)
	target_link_libraries(test_cards PRIVATE solitaire2::backend Catch2::Catch2WithMain)
	target_link_libraries(test_gamedeck PRIVATE solitaire2::backend Catch2::Catch2WithMain)
	target_link_libraries(test_foundation PRIVATE solitaire2::backend Catch2::Catch2WithMain)

	include(Catch)

	catch_discover_tests(test_version)
	catch_discover_tests(test_cards)
	catch_discover_tests(test_gamedeck)
	catch_discover_tests(test_foundation)
endif()

if(SOLITAIRE2_BUILD_PYTHON)
	find_package(Python COMPONENTS Interpreter Development.Module REQUIRED)
	pybind11_add_module(solitaire2_python MODULE bindings/module.cpp)
	target_link_libraries(solitaire2_python PRIVATE solitaire2::backend)
	set_target_properties(solitaire2_python PROPERTIES OUTPUT_NAME _core)
endif()

install(TARGETS solitaire2_backend solitaire2_cli solitaire2_perf solitaire2_profile
	EXPORT solitaire2Targets
	ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
	RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(DIRECTORY python/solitaire2/ DESTINATION solitaire2)

if(SOLITAIRE2_BUILD_PYTHON)
	install(TARGETS solitaire2_python
		EXPORT solitaire2Targets
		LIBRARY DESTINATION solitaire2
		RUNTIME DESTINATION solitaire2
	)
endif()

install(EXPORT solitaire2Targets
	FILE solitaire2Targets.cmake
	NAMESPACE solitaire2::
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/solitaire2
)

configure_package_config_file(
	cmake/solitaire2Config.cmake.in
	${CMAKE_CURRENT_BINARY_DIR}/solitaire2Config.cmake
	INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/solitaire2
)
write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/solitaire2ConfigVersion.cmake
	COMPATIBILITY SameMajorVersion
)

install(FILES
	${CMAKE_CURRENT_BINARY_DIR}/solitaire2Config.cmake
	${CMAKE_CURRENT_BINARY_DIR}/solitaire2ConfigVersion.cmake
	DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/solitaire2
)
