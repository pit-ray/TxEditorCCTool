cmake_minimum_required(VERSION 3.0.0)
project(tecc VERSION 0.1.0)
set(CMAKE_CXX_FLAGS "-std=c++1z -Wall")
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(EXEC_NAME ${PROJECT_NAME})

set(SOURCE_FILE
    ${CMAKE_SOURCE_DIR}/lib/tinyxml2.cpp
    ${CMAKE_SOURCE_DIR}/cc_src/ccx_parser.cpp
    ${CMAKE_SOURCE_DIR}/cc_src/Color.cpp
    ${CMAKE_SOURCE_DIR}/cc_src/TextEditor.cpp
    ${CMAKE_SOURCE_DIR}/cc_src/TeraPad.cpp
    ${CMAKE_SOURCE_DIR}/cc_src/Sakura.cpp
    ${CMAKE_SOURCE_DIR}/src/main.cpp
)

set(INCLUDE_DIR
    C:/boost_1_68_0
    ${CMAKE_SOURCE_DIR}/lib
    ${CMAKE_SOURCE_DIR}/cc_include
    ${CMAKE_BINARY_DIR}
)

set(LINK_DIR
    C:/boost_1_68_0/stage/lib
)
set(gflags_DIR
    C:/gflags
)

find_package(gflags REQUIRED)

link_directories(${LINK_DIR})
include_directories(${INCLUDE_DIR} ${gflags_INCLUDE_DIR})

add_executable(${EXEC_NAME} ${SOURCE_FILE})
target_link_libraries(${EXEC_NAME} gflags)