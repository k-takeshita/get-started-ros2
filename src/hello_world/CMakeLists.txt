cmake_minimum_required(VERSION 3.12)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

# アルファベット順にしたい感じ
find_package(ament_cmake REQUIRED)
find_package(hello_world_msgs REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker hello_world_msgs rclcpp)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener hello_world_msgs rclcpp)

# add_libraryは必要なはず
add_library(talker_component SHARED src/talker_component.cpp)
ament_target_dependencies(talker_component hello_world_msgs rclcpp rclcpp_components)
# EXECUTABLEは別名の必要あり，rclcpp_components_register_nodeの中でadd_executableが呼ばれているので
rclcpp_components_register_node(talker_component PLUGIN hello_world::TalkerComponent EXECUTABLE talker_component_node)

add_library(listener_component SHARED src/listener_component.cpp)
ament_target_dependencies(listener_component hello_world_msgs rclcpp rclcpp_components)
rclcpp_components_register_node(listener_component PLUGIN hello_world::ListenerComponent EXECUTABLE listener_component_node)

# インストールはまとめる
install(TARGETS talker listener
        DESTINATION lib/${PROJECT_NAME})

install(TARGETS talker_component listener_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

ament_package()
