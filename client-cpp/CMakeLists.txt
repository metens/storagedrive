cmake_minimum_required(VERSION 3.22)

project(storagedrive_client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(cpr REQUIRED)
add_executable(storagedrive_client src/main.cpp)
target_link_libraries(storagedrive_client PRIVATE cpr::cpr)
