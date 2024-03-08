cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)

project(KnucklesEditor)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_subdirectory(vendor/Knuckles )

target_include_directories(${PROJECT_NAME}
				PUBLIC include
				PUBLIC vendor/Knuckles/include
				)

target_link_directories(${PROJECT_NAME}
				PUBLIC src
				)

target_link_libraries(${PROJECT_NAME}
				Knuckles
				)
