cmake_minimum_required(VERSION 3.5)
project(serial_interface)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Wpedantic")

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(serial_message REQUIRED)

add_executable(pub src/serial_publisher.cpp)
ament_target_dependencies(pub rclcpp serial_message)

install(TARGETS pub DESTINATION lib/${PROJECT_NAME})

ament_package()
