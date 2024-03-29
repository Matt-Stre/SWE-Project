cmake_minimum_required(VERSION 3.26)
project(SWE_Project)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/backend)

add_executable(SWE_Project
        src/backend/main.cpp
        src/backend/Server.cpp
        src/backend/httplib/httplib.h
        src/backend/Opportunity.cpp
        src/backend/Opportunity.h
        src/backend/Database.cpp
        src/backend/Database.h
)
