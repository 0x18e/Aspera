cmake_minimum_required(VERSION 3.20)

project(Aspera)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.c")


find_package(OpenGL REQUIRED)

if (APPLE)
find_package(glfw3 REQUIRED)
message(STATUS "Compiling for mac")
endif()
add_executable(Aspera ${SOURCES})
target_include_directories(Aspera PUBLIC "${PROJECT_SOURCE_DIR}/include/") # should include assimp files as well
target_link_directories(Aspera PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/"
)

target_link_libraries(Aspera PRIVATE ${OPENGL_LIBRARIES})
if (APPLE)
target_link_libraries(Aspera PRIVATE glfw)
elseif(LINUX)
message(STATUS "Linking libassimp.so")
target_link_libraries(Aspera PRIVATE glfw libassimp.so)
else()
message(STATUS "Linking assimp-vc143")
target_link_libraries(Aspera PRIVATE glfw3 assimp-vc143-mtd)
endif()
