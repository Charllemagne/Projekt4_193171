cmake_minimum_required(VERSION 3.10)
project(Projekt2_wojna)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(Projekt4_193171 src/main.cpp src/funkcje.cpp src/generacje_blokow.cpp)

if (WIN32)
    target_link_libraries(Projekt4_193171 PRIVATE gdiplus)
endif()