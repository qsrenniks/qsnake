cmake_minimum_required(VERSION 3.16 FATAL_ERROR)

project(qsnake)

macro(addunit FILENAME)
set(SOURCE
${SOURCE}
source/${FILENAME}
)
endmacro()

addunit(main.cpp)

addunit(Engine.cpp)
addunit(Window.cpp)

add_executable(qsnake ${SOURCE})

target_precompile_headers(qsnake PRIVATE "source/pch.h")

target_include_directories(qsnake 
  PRIVATE lib/includes/)

