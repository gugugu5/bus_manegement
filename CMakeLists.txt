cmake_minimum_required(VERSION 3.25)
project(YuntuTrafficReservation LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_MFC_FLAG 2)

add_executable(YuntuTraffic WIN32
    src/main.cpp
    src/database.cpp
    third_party/sqlite/sqlite3.cpp
)
set_source_files_properties(third_party/sqlite/sqlite3.cpp PROPERTIES LANGUAGE C)

target_include_directories(YuntuTraffic PRIVATE src third_party/sqlite)
target_compile_definitions(YuntuTraffic PRIVATE UNICODE _UNICODE NOMINMAX)

if (MSVC)
    target_compile_options(YuntuTraffic PRIVATE /W4 /utf-8)
endif()

