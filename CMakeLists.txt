CMAKE_MINIMUM_REQUIRED(VERSION 3.8)

PROJECT("OCTOPUS_ENGINE") #TODO: version?!

SET(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")
include(${CMAKE_ROOT}/Modules/ExternalProject.cmake)

FILE(GLOB HEADERS LIST_DIRECTORIES false "include/*.hpp")
FILE(GLOB EXTRA_HEADERS LIST_DIRECTORIES false "include/commands/*.hpp")
FILE(GLOB SOURCES LIST_DIRECTORIES false "src/*.cpp")
FILE(GLOB EXTRA_SOURCES LIST_DIRECTORIES false "src/commands/*.cpp")


#dependencies we expect the user takes care of
FIND_PACKAGE(Boost REQUIRED)
FIND_PACKAGE(GLUT REQUIRED)
FIND_PACKAGE(Freetype REQUIRED)
FIND_PACKAGE(Harfbuzz REQUIRED)
FIND_PACKAGE(DevIL REQUIRED)
FIND_PACKAGE(Lua REQUIRED)
FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Glfw REQUIRED)
FIND_PACKAGE(GLEW REQUIRED)
FIND_PACKAGE(ZLIB REQUIRED)

#dependencies we build ourselves
ExternalProject_Add(xd-lib
  GIT_REPOSITORY "https://github.com/cupu/xd.git"
  GIT_TAG "cmake_build"
  PREFIX ${CMAKE_CURRENT_BINARY_DIR}/xd
  CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
)

INCLUDE_DIRECTORIES("include/")
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/src/xd-lib/include/") # this is a hack because I don't know how to install xd includes yet
INCLUDE_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/src/xd-lib-build/LuaBind/include/") # hack because we know xd depends on LuaBind, the dependency should probably be built here and used by xd

LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/lib")
LINK_DIRECTORIES("${CMAKE_BINARY_DIR}/xd/src/xd-lib-build/LuaBind/lib")

ADD_EXECUTABLE(octopus ${SOURCES} ${EXTRA_SOURCES})
ADD_DEPENDENCIES(octopus xd-lib)
TARGET_LINK_LIBRARIES(octopus xd ${OPENGL_LIBRARIES} ${GLEW_LIBRARIES} 
				 ${GLUT_LIBRARIES} ${FREETYPE_LIBRARIES} 
				 ${HARFBUZZ_LIBRARIES} ${IL_LIBRARIES} ${LUA_LIBRARIES}
				 ${GLFW_LIBRARIES} ${GLEW_LIBRARIES} ${ZLIB_LIBRARIES}
				 ${Boost_LIBRARIES}
				 boost_unit_test_framework fmod luabind09)
