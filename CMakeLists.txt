cmake_minimum_required(VERSION 3.13)
project(jtkDB VERSION 0.1)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(INCLUDES_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")

add_executable(jtkDB ${SRC_DIR}/jtkDB.cpp)

add_subdirectory(${SRC_DIR}/jtkDatabase)
add_subdirectory(${SRC_DIR}/jtkTable)
add_subdirectory(${SRC_DIR}/dbTerminal)
add_subdirectory(${SRC_DIR}/tableTerminal)
add_subdirectory(${SRC_DIR}/utils)

target_include_directories(jtkDB PRIVATE
                           "${INCLUDES_DIR}"
                           "${INCLUDES_DIR}/jtkDatabase"
                           "${INCLUDES_DIR}/jtkTable"
                           "${INCLUDES_DIR}/dbTerminal"
                           "${INCLUDES_DIR}/tableTerminal"
                           "${INLUCDES_DIR}/utils"
                          )