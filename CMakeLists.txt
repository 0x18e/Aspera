cmake_minimum_required(VERSION 3.20)

project(Aspera)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "${PROJECT_SOURCE_DIR}/src/*.cpp" "${PROJECT_SOURCE_DIR}/src/*.h" "${PROJECT_SOURCE_DIR}/src/*.c")


find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
add_executable(Aspera ${SOURCES})
target_include_directories(Aspera PUBLIC "${PROJECT_SOURCE_DIR}/include/")
target_link_directories(Aspera PRIVATE
    "${CMAKE_SOURCE_DIR}/lib/"
)

target_link_libraries(Aspera PRIVATE ${OPENGL_LIBRARIES})
target_link_libraries(Aspera PRIVATE OpenGL::GL glfw)
