# Copyright Abel Sinkovics (abel@sinkovics.hu)  2013.
# Distributed under the Boost Software License, Version 1.0.
#    (See accompanying file LICENSE_1_0.txt or copy at
#          http://www.boost.org/LICENSE_1_0.txt)

cmake_minimum_required(VERSION 2.6)
project(process)
set(CMAKE_PROJECT_NAME process)
set(MAJOR_VERSION 0)
set(MINOR_VERSION 1)
set(PATCH_VERSION 0)

# Boost
# Turn this on to link statically against Boost
set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS
  unit_test_framework
)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIRS})

enable_testing()

include_directories("include")

subdirs(test example)

# Warning level
if(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
  message("Setting warning level for GCC")
elseif("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Werror -pedantic")
  message("Setting warning level for Clang")
endif()

# Installation
macro(install_with_dir PREFIX_TO_CUT)
 
 string(LENGTH ${PREFIX_TO_CUT} PREFIX_LEN)

 foreach(F ${ARGN})
   string(REGEX MATCH "(.*)[/\\]" DIR ${F})
   string(LENGTH ${DIR} DIR_LEN)
   math(EXPR DIR_KEEP "${DIR_LEN} - ${PREFIX_LEN}")
   string(SUBSTRING ${DIR} ${PREFIX_LEN} ${DIR_KEEP} DIR2)
   install(FILES ${F} DESTINATION include/${DIR2})
 endforeach(F)
          
endmacro(install_with_dir)

if (CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
  set(CMAKE_INSTALL_PREFIX "/usr")
endif()

file(GLOB_RECURSE HEADER_FILES ${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp)
install_with_dir(${CMAKE_CURRENT_SOURCE_DIR}/include ${HEADER_FILES})

# Debian package
if(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")
  include(InstallRequiredSystemLibraries)
   
  set(CPACK_SET_DESTDIR "on")
  set(CPACK_PACKAGING_INSTALL_PREFIX "/tmp")
  set(CPACK_GENERATOR "DEB")
   
  set(CPACK_PACKAGE_DESCRIPTION "Process")
  set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "Library for capturing standard output and error of a process")
  set(CPACK_PACKAGE_VENDOR "Abel Sinkovics")
  set(CPACK_PACKAGE_CONTACT "abel@sinkovics.hu")
  set(CPACK_PACKAGE_VERSION_MAJOR "${MAJOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_MINOR "${MINOR_VERSION}")
  set(CPACK_PACKAGE_VERSION_PATCH "${PATCH_VERSION}")
  set(CPACK_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")
  set(CPACK_SOURCE_PACKAGE_FILE_NAME "lib${CMAKE_PROJECT_NAME}-${MAJOR_VERSION}.${MINOR_VERSION}.${CPACK_PACKAGE_VERSION_PATCH}-dev")

  set(CPACK_DEBIAN_PACKAGE_PRIORITY "optional")
  set(CPACK_DEBIAN_PACKAGE_SECTION "devel")
  set(CPACK_DEBIAN_ARCHITECTURE "all") # Header-only
   
  set(CPACK_COMPONENTS_ALL headers)
  include(CPack)
   
endif(EXISTS "${CMAKE_ROOT}/Modules/CPack.cmake")



