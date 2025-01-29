# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-src")
  file(MAKE_DIRECTORY "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-src")
endif()
file(MAKE_DIRECTORY
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-build"
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix"
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/tmp"
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/src"
  "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp"
)

set(configSubDirs )
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/greenbox/projects/Prosaic-at-best/build/_deps/ogg-subbuild/ogg-populate-prefix/src/ogg-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
