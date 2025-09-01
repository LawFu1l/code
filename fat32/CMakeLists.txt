cmake_minimum_required(VERSION 3.30)

project(fat32)

set (CMAKE_CXX_STANDARD 26)
set (HOME $ENV{HOME})
set(CMAKE_BUILD_TYPE Debug)  # ✅ Debug 모드
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")  # ✅ 최적화 off + 디버그 정보 on

set (SOURCES
        ${HOME}/develop/src/byte_buffer.cpp
        main.cpp
        bootrecord.cpp
        fatarea.cpp
        fatarea.h
        dataarea.cpp
        DirEntry.cpp
        DirEntry.h
        stream.cpp
        stream.h
        extent.cpp
        extent.h
        node.cpp
        node.h
        fat32.cpp
        fat32.h
        Lfnentry.cpp
        Lfnentry.h
        string_util.cpp
        string_util.h
        Filesystem.cpp
        Filesystem.h
        fat32_common.h
)

include_directories (
        ${HOME}/develop/include
        /usr/local/include
        /opt/homebrew/include
        ${CMAKE_CURRENT_SOURCE_DIR}
)

add_executable(fat32
        ${SOURCES}
)

