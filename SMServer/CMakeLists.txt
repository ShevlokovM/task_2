cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(StaffManagementServer)

find_package(SQLite3 REQUIRED)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(StaffManagementServer
	 main.cpp
	MessageHandler.cpp
	MessageHandler.h
	DBHandler.cpp
	DBHandler.h)

target_link_libraries(StaffManagementServer PRIVATE nlohmann_json::nlohmann_json SQLite::SQLite3)

