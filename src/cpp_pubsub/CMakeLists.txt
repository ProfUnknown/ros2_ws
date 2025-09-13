cmake_minimum_required(VERSION 3.8)
project(cpp_pubsub)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(std_msgs REQUIRED) #Sebelum pake interface
find_package(tutorial_interfaces REQUIRED)

add_executable(talker src/publisher_member_function.cpp)
add_executable(receiver src/subscriber_member_function.cpp)
ament_target_dependencies(talker rclcpp tutorial_interfaces)
ament_target_dependencies(receiver rclcpp tutorial_interfaces)

install(TARGETS
  talker
  receiver
  DESTINATION lib/${PROJECT_NAME})


if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_copyright_FOUND TRUE)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
