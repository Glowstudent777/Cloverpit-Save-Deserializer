cmake_minimum_required(VERSION 3.15)
set(name "SaveCryptoDemo")

project(${name} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(source_files
    src/main.cpp
    src/SaveCrypto.cpp
)

add_executable(${name} ${source_files})

target_include_directories(${name} PRIVATE
    src
)

set_target_properties(${name} PROPERTIES OUTPUT_NAME ${name})