cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(qsnake)

macro(addunit FILENAME)
set(SOURCE
${SOURCE}
source/${FILENAME}
)
endmacro()

addunit(main.cpp)

add_executable(qsnake ${SOURCE})

target_precompile_headers(qsnake PRIVATE "source/pch.h")

