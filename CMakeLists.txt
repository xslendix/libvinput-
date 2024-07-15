cmake_minimum_required(VERSION 3.10)

project(libvinput_cpp VERSION 1.0)

option(BUILD_EXAMPLES "Build the examples" ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(PkgConfig REQUIRED)
pkg_check_modules(LIBVINPUT REQUIRED libvinput)

include_directories(${LIBVINPUT_INCLUDE_DIRS})

set(SOURCES
	src/EventEmulator.cpp
	src/EventListener.cpp
	src/Events.cpp
)
set(HEADERS
	include/libvinput++/EventEmulator.hpp
	include/libvinput++/EventListener.hpp
	include/libvinput++/Events.hpp
	include/libvinput++/VInput.hpp
)

add_library(vinput++ SHARED ${SOURCES})
target_link_libraries(vinput++ ${LIBVINPUT_LIBRARIES})
target_include_directories(vinput++ PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${LIBVINPUT_INCLUDE_DIRS})

# Installation rules
install(TARGETS vinput++
		LIBRARY DESTINATION lib
		ARCHIVE DESTINATION lib
		RUNTIME DESTINATION bin
)

install(DIRECTORY include/libvinput++
		DESTINATION include
		FILES_MATCHING PATTERN "*.hpp"
)

configure_file(libvinput++.pc.in libvinput++.pc @ONLY)
install(FILES ${CMAKE_BINARY_DIR}/libvinput++.pc DESTINATION lib/pkgconfig)

if(BUILD_EXAMPLES)
	file(GLOB EXAMPLES "examples/*.cpp")

	foreach(EXAMPLE ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME ${EXAMPLE} NAME_WE)
		add_executable(${EXAMPLE_NAME} ${EXAMPLE})
		target_link_libraries(${EXAMPLE_NAME} vinput++ ${LIBVINPUT_LIBRARIES})
		target_include_directories(${EXAMPLE_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include ${LIBVINPUT_INCLUDE_DIRS})
	endforeach()
endif()
