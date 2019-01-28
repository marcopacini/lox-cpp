cmake_minimum_required(VERSION 3.2)
add_custom_target(lox-cpp COMMAND make run bin ${CMAKE_CURRENT_SOURCE_DIR}/src)