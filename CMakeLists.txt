cmake_minimum_required(VERSION 3.4)

project(NetworkDesigner)

include_directories(${PROJECT_SOURCE_DIR}/include ${PROJECT_SOURCE_DIR}/src)


add_executable(NetworkDesigner 
    src/main.cpp
    src/IPAddress.hpp
    src/IPAddress.cpp
    src/Designer.cpp
    src/Designer.hpp)
target_link_libraries(NetworkDesigner user32.lib ws2_32.lib iphlpapi.lib)