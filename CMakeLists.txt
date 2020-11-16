cmake_minimum_required(VERSION 3.5)

project(Freedom LANGUAGES CXX)

find_package(Qt5Core REQUIRED)
FIND_PACKAGE(Boost REQUIRED)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SOURCE_DIR "${PROJECT_SOURCE_DIR}/src")

include_directories(${Boost_INCLUDE_DIR})
include_directories(${SOURCE_DIR})
add_subdirectory(tests)

file(GLOB SOURCE_FILES
    "${SOURCE_DIR}/*.cpp"
    "${SOURCE_DIR}/*.hpp"
)


add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt5::Core PUBLIC ${Boost_LIBRARIES} )

target_compile_definitions(${PROJECT_NAME} PRIVATE EDOM_LIBRARY)
