cmake_minimum_required(VERSION 3.18.0)
project(ChessKit
    DESCRIPTION "Toolkit for playing chess"
    VERSION 0.1
    LANGUAGES CXX
)


list(PREPEND CMAKE_MODULE_PATH ${PROJECT_BINARY_DIR})
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)


if (CMAKE_BUILD_TYPE STREQUAL "")
    set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()


add_library(ChessKit)
target_include_directories(ChessKit PUBLIC include)
target_sources(ChessKit PRIVATE src/Chess.cpp)


find_package(Catch2)
if (Catch2_FOUND)
    add_library(Catch2_Main OBJECT src/Main.Test.cpp)
    target_link_libraries(Catch2_Main PUBLIC Catch2::Catch2)

    add_executable(ChessKit.UT EXCLUDE_FROM_ALL)
    target_sources(ChessKit.UT PRIVATE src/Chess.Test.cpp)
    target_link_libraries(ChessKit.UT PRIVATE ChessKit Catch2_Main)

    add_custom_target(check-unit
        COMMAND ChessKit.UT
        DEPENDS ChessKit.UT
        COMMENT "Running unit tests"
    )
else()
    message(WARNING "Could not find Catch2 dependency, skipping unit tests")
endif()