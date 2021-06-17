cmake_minimum_required(VERSION 3.19 FATAL_ERROR)

#Устанавливаем стандарт по умолчанию C++14
set (CMAKE_CXX_STANDARD 14)

#Название проекта
project(LittelWorld)

#Подключаем cmake файлы библиотеки sfml 
set(SFML_DIR ${CMAKE_CURRENT_SOURCE_DIR}/SFML-2.5.1/lib/cmake/SFML/)
find_package(SFML COMPONENTS audio graphics window system REQUIRED)

#Путь к заголовочным файлам Lua
set(LUA_HEADERS 
    ${CMAKE_SOURCE_DIR}/Lua/Lua/include/
)

#Путь к заголовочным файлам LuaBridge
set (LUABRIDGE_HEADERS
    ${CMAKE_SOURCE_DIR}/Lua/LuaBridge/
)

#Путь ко всем остальным исходникам
file(GLOB_RECURSE SOURCES RELATIVE 
    ${CMAKE_SOURCE_DIR} "Scr/*.cpp" 
    ${CMAKE_SOURCE_DIR} "/Scr/*.hpp"
    ${CMAKE_SOURCE_DIR} "/Scr/*.h"
)

add_executable(${PROJECT_NAME} ${SOURCES})

#Подключаем lib sfml к нашему проекту
target_link_libraries(${PROJECT_NAME} sfml-audio sfml-graphics sfml-window sfml-system)

#Теперь подключаем lib интерпритатора Lua к нашему проекту
target_link_libraries(${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/Lua/Lua/lua54.lib)

#Указываем внешнюю директорию заголовочных вайлов
target_include_directories( ${PROJECT_NAME} PRIVATE 	
    ${LUABRIDGE_HEADERS}
    ${LUA_HEADERS}
)