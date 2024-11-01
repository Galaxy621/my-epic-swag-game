cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

# Set the project name
project(MyEpicSwagGame)

# glob all the source files
file(GLOB_RECURSE CPP_SOURCES "src/*.cpp")
file(GLOB_RECURSE C_SOURCES "src/*.c")

# Add the executable
add_executable(MyEpicSwagGame ${CPP_SOURCES} ${C_SOURCES}) 

# Include directories
include_directories(${PROJECT_SOURCE_DIR}/include)
include_directories(${PROJECT_SOURCE_DIR}/lib)

# Link libraries
target_link_libraries(MyEpicSwagGame ${CMAKE_THREAD_LIBS_INIT} opengl32 gdi32)

# Copy assets to build directory
# Check if it exists first though, destroy it if needs be
file(REMOVE_RECURSE ${PROJECT_BINARY_DIR}/assets)
file(COPY ${PROJECT_SOURCE_DIR}/assets DESTINATION ${PROJECT_BINARY_DIR})
