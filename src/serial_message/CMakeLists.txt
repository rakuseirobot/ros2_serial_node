cmake_minimum_required(VERSION 3.5)
project(serial_message)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

#generate msga files
find_package(rosidl_default_generators REQUIRED)
rosidl_generate_interfaces(${PROJECT_NAME} "msg/Serial.msg" "msg/SerialArray.msg")

set(CMAKE_CXX_FLAGS "-O2 -Wall -Wextra -Wpedantic")

find_package(ament_cmake REQUIRED)

ament_package()
