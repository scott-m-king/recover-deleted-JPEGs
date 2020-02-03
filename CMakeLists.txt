cmake_minimum_required(VERSION 3.15)
project(recover)

set(CMAKE_CXX_STANDARD 14)

add_executable(recover
        card.raw
        recover
        recover.c)
