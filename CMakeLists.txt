cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 17)

project(KnucklesEditor)

file(GLOB SOURCES src/*.cpp)

add_executable(${PROJECT_NAME} ${SOURCES})

add_compile_definitions(
KE_EDITOR
)

add_subdirectory(vendor/Knuckles )

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory 
  "${CMAKE_CURRENT_SOURCE_DIR}/vendor/Knuckles/build/Assets"
  "${CMAKE_CURRENT_SOURCE_DIR}/build/Assets" 
    COMMENT "Copying assets to output directory")

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD 
  COMMAND "${CMAKE_COMMAND}" -E copy_directory 
  "${CMAKE_CURRENT_SOURCE_DIR}/vendor/Knuckles/build/Shaders"
  "${CMAKE_CURRENT_SOURCE_DIR}/build/Shaders" 
    COMMENT "Copying Shader to output directory")

target_include_directories(${PROJECT_NAME}
	PUBLIC include
	PUBLIC vendor/Knuckles/include
	)

target_link_directories(${PROJECT_NAME}
	PUBLIC src
	)

target_link_libraries(${PROJECT_NAME}
	${SDL2_LIBRARIES}
	Knuckles
	)
