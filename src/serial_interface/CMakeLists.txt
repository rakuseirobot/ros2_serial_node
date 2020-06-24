cmake_minimum_required(VERSION 3.5)
project(serial_interface)

set(CMAKE_CXX_FLAGS " -O2 -Wall -Wextra")

find_package(ament_cmake REQUIRED)
add_executable(tests src/main.cpp test/test.cpp)
target_include_directories(tests PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/test)

install(TARGETS tests DESTINATION lib/${PROJECT_NAME})
ament_package()
