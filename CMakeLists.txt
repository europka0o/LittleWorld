cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

project(LittelWorld)

set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML/)

find_package(SFML COMPONENTS audio graphics window system REQUIRED)

set(LUA_HEADERS 
    ${CMAKE_SOURCE_DIR}/Lua/Lua/include/
)

set (LUABRIDGE_HEADERS
    ${CMAKE_SOURCE_DIR}/Lua/LuaBridge/
)

file(GLOB_RECURSE SOURCES RELATIVE 
    ${CMAKE_SOURCE_DIR} "Scr/*.cpp" 
    ${CMAKE_SOURCE_DIR} "/Scr/*.hpp"
    ${CMAKE_SOURCE_DIR} "/Scr/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)

target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Lua/Lua/lua54.lib)

target_include_directories( ${PROJECT_NAME} PRIVATE 	
    ${LUABRIDGE_HEADERS}
    ${LUA_HEADERS}
)