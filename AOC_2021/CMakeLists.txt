cmake_minimum_required(VERSION 3.5)

project(AOC_2021 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5Core)

add_executable(AOC_2021
  main.cpp
  utils/commonStruct.h
  utils/commonFuntion.h
  Y21Day01.cpp
  Y21Day01.h
  Y21Day02.cpp
  Y21Day02.h
  Y21Day03.cpp
  Y21Day03.h
  Y21Day04.cpp
  Y21Day04.h
  Y21Day05.cpp
  Y21Day05.h
  Y21Day06.cpp
  Y21Day06.h
  Y21Day07.cpp
  Y21Day07.h
  Y21Day08.cpp
  Y21Day08.h
  Y21Day09.cpp
  Y21Day09.h
  Y21Day10.cpp
  Y21Day10.h
  Y21Day14.cpp
  Y21Day14.h
  Y21Day15.cpp
  Y21Day15.h
  Y21Day18.cpp
  Y21Day18.h
)
target_link_libraries(AOC_2021 Qt5::Core)
