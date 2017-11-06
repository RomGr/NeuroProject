cmake_minimum_required (VERSION 2.6)
project(NeuroProject)

set(CMAKE_CXX_FLAGS "-W -Wall -pedantic -std=c++11")

add_subdirectory(googletest)
enable_testing()
include_directories(${gtest_SOURCE_DIR}/include ${guest_SOURCE_DIR})

add_executable (
	Neuro 
	Src/main.cpp
	Src/neurone.hpp 
	Src/neurone.cpp
	Src/network.hpp 
	Src/network.cpp
	Src/ringbuffer.hpp
	Src/ringbuffer.cpp
	)

add_executable (
	UnitTest
	Src/neurone.hpp 
	Src/neurone.cpp
	Src/network.hpp 
	Src/network.cpp
	Src/ringbuffer.hpp
	Src/ringbuffer.cpp
	Test/UnitTest.cpp
	)

target_link_libraries (UnitTest gtest gtest_main)
add_test (UnitTest UnitTest)


###### Doxygen generation ######

# We first check if Doxygen is present.
find_package(Doxygen)
if(DOXYGEN_FOUND)

    # We then check if the Doxygen.in configuration file exists
    IF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
        message(FATAL_ERROR "Doxygen configuration file is needed to build the documentation:
         - ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in not found.
         - Generate one in the project folder with doxygen -g Doxyfile.in")
    ENDIF(NOT EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)

    # We configure the doxyfile for make.
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile @ONLY)
    add_custom_target(doc
        ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    )
ELSE(DOXYGEN_FOUND)
    message(FATAL_ERROR "Doxygen is needed to build the documentation.")
ENDIF(DOXYGEN_FOUND)

