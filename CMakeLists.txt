cmake_minimum_required(VERSION 3.15)

project(libpqxx_practice)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PostgreSQL REQUIRED)
find_package(libpqxx CONFIG REQUIRED)

add_executable(libpqxx_app 
    src/Functions.cpp
    src/main.cpp
    src/menu.cpp
)

add_custom_command(TARGET libpqxx_app POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/dll"           
        $<TARGET_FILE_DIR:libpqxx_app> 
    COMMENT "Copying required DLLs to output directory"
)

target_include_directories(libpqxx_app PRIVATE include)

target_link_libraries(libpqxx_app 
    PRIVATE 
    "C:/vcpkg/installed/x64-windows/lib/pqxx.lib"
    PostgreSQL::PostgreSQL
)

message(STATUS "Project successfully configured")