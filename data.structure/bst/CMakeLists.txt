cmake_minimum_required (VERSION 3.30)

project (bst)

set (CMAKE_CXX_STANDARD 23)
set (CMAKE_CXX_COMPILER g++)
set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

set (SOURCES
  bst.cpp
)

include_directories (
  /usr/local/include
  /opt/homebrew/include
  ${CMAKE_CURRENT_SOURCE_DIR}
)

link_directories (
  /usr/local/lib
  /opt/homebrew/lib
)

add_executable (bst
  ${SOURCES}
)