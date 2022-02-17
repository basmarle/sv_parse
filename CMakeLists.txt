cmake_minimum_required(VERSION 3.21)
project(sv_parse)

set(CMAKE_CXX_STANDARD 17)

include_directories(/usr/local/bin/include/)

add_executable(sv_parse main.cpp Module.cpp Module.h)

target_link_libraries(sv_parse /usr/local/bin/lib/libslangcompiler.a)
target_link_libraries(sv_parse /usr/local/bin/lib/libslangparser.a)
target_link_libraries(sv_parse /usr/local/bin/lib/libslangcore.a)

#target_link_libraries(sv_parse /usr/local/bin/lib/libslangruntime.a)


