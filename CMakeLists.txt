cmake_minimum_required(VERSION 3.10)

project(BookStore LANGUAGES CXX) 

set(CMAKE_CXX_STANDARD 20) 
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(MY_SOURCES
    src/main.cpp
    src/Initializer.cpp
    src/IO.cpp
    src/User.cpp
    src/Name.cpp
    src/UserManager.cpp
    src/Commander.cpp
    src/Book.cpp
    src/BookManager.cpp
)

# set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

add_executable(code ${MY_SOURCES})

target_include_directories(code PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include   
#    ${CMAKE_CURRENT_SOURCE_DIR}/src       
)