cmake_minimum_required(VERSION 3.26)
project(SWE_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/backend)
include_directories(${CMAKE_SOURCE_DIR}/src/backend/httplib)
include_directories(${CMAKE_SOURCE_DIR}/src/backend/nlohmann)

add_executable(SWE_Project
        src/backend/main.cpp
        src/backend/Server.cpp
        src/backend/CSV.cpp
        src/backend/CSV.h
        src/backend/httplib/httplib.h
)
