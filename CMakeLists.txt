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
addunit(GraphicsManager.cpp)
addunit(GameObjectManager.cpp)
addunit(Level.h)
addunit(Level.cpp)

#game files
addunit(game/SnakeGameMode.cpp)

add_executable(qsnake ${SOURCE})

target_precompile_headers(qsnake PRIVATE "source/pch.h")

target_include_directories(qsnake 
  PRIVATE lib/includes/
  PRIVATE source/)

target_link_options(qsnake PRIVATE /ignore:4098)

target_link_libraries(qsnake
  PRIVATE opengl32.lib
  PRIVATE ${PROJECT_SOURCE_DIR}/lib/libraries/glew32.lib
  PRIVATE ${PROJECT_SOURCE_DIR}/lib/libraries/glfw3.lib)

target_compile_definitions(qsnake PRIVATE DATA_DIR="${PROJECT_SOURCE_DIR}/data/")

add_custom_command(TARGET qsnake POST_BUILD 
  COMMAND ${CMAKE_COMMAND} -E copy_if_different
  "${PROJECT_SOURCE_DIR}/lib/libraries/glew32.dll"
  ${CMAKE_BINARY_DIR})

