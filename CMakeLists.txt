CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

PROJECT("OCTOPUS_ENGINE") #TODO: version?!

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

FILE(GLOB HEADERS LIST_DIRECTORIES false "include/*.hpp")
FILE(GLOB SOURCES LIST_DIRECTORIES false "src/*.cpp")


#dependencies we expect the user takes care of
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(Freetype REQUIRED)
FIND_PACKAGE(Harfbuzz REQUIRED)
FIND_PACKAGE(DevIL REQUIRED)
FIND_PACKAGE(Lua REQUIRED)
FIND_PACKAGE(Glfw REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)

#dependencies we build ourselves
ExternalProject_Add(xd
  GIT_REPOSITORY "https://github.com/cupu/xd.git"
  GIT_TAG "cmake_build"
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/xd
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

INCLUDE_DIRECTORIES("include/")
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/src/xd/include") # this is a hack because I don't know how to install xd includes yet
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/src/xd-build/LuaBind/include/") # hack because we know xd depends on LuaBind, the dependency should probably be build here and used by xd then

ADD_EXECUTABLE(octopus ${SOURCES})
ADD_DEPENDENCIES(octopus xd)
