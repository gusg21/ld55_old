cmake_minimum_required(VERSION 3.5)
project(ld55 VERSION 0.0.1 LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 20)
if (MSVC)
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/$<CONFIG>)
else()
  set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
endif()

add_executable(${PROJECT_NAME} src/main.cpp)

add_subdirectory(external/engine)

target_link_libraries(${PROJECT_NAME} PUBLIC ld55_engine)

# Python stuff
find_package(Python)

set(can_file_name ld55.can)
set(py_cmd ${CMAKE_SOURCE_DIR}/scripts/canner.py ${CMAKE_SOURCE_DIR}/assets ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ld55.can)
add_custom_command(
    TARGET ${PROJECT_NAME}
    PRE_BUILD # Call this command pre-build
    COMMAND ${PYTHON_EXECUTABLE} ${py_cmd}
    COMMENT "=> Canning the assets..."
)    

add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:${PROJECT_NAME}> $<TARGET_FILE_DIR:${PROJECT_NAME}>
  COMMAND_EXPAND_LISTS
  )