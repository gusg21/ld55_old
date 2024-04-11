cmake_minimum_required(VERSION 3.21)
project(ld55_engine VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(SDL_STATIC OFF)
set(SDL_SHARED ON)
set(SDL_INSTALL_TESTS OFF)
set(SDL_DISABLE_INSTALL_DOCS OFF)
set(SDL_DISABLE_INSTALL OFF)
set(SDL_TESTS OFF)
set(SDL_TEST_LIBRARY OFF)

#add_subdirectory(external/assimp)
add_subdirectory(external/glad)
add_subdirectory(external/glm)
add_subdirectory(external/SDL)
#add_subdirectory(external/stb_image)

file(GLOB ${PROJECT_NAME}_SRC src/*.cpp src/*/*.cpp)
add_library(${PROJECT_NAME} ${${PROJECT_NAME}_SRC})

target_include_directories(${PROJECT_NAME} 
    PUBLIC
        $<INSTALL_INTERFACE:include>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    PRIVATE
)

target_link_libraries(${PROJECT_NAME} 
    PUBLIC
        glm
        SDL3::SDL3
        glad
)