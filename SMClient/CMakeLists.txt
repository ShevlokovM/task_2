cmake_minimum_required(VERSION 3.8)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(StaffManagementClient)

include(FetchContent)

FetchContent_Declare(json URL https://github.com/nlohmann/json/releases/download/v3.11.3/json.tar.xz)
FetchContent_MakeAvailable(json)

add_executable(StaffManagementClient 
	main.cpp
	MessageHandler.cpp
	MessageHandler.h
	BaseHandler.h
	AddEmploeeHandler.cpp
	AddEmploeeHandler.h
	DelEmploeeHandler.cpp
	DelEmploeeHandler.h
	EmploeeListHandler.cpp
	EmploeeListHandler.h
	GetChiefHandler.cpp
	GetChiefHandler.h
	SetChiefHandler.cpp
	SetChiefHandler.h
	SetPositionHandler.cpp
	SetPositionHandler.h)

target_link_libraries(StaffManagementClient PRIVATE nlohmann_json::nlohmann_json)


