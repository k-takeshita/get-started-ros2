cmake_minimum_required(VERSION 3.12)
project(hello_world)

set(CMAKE_CXX_STANDARD 17)

# アルファベット順にしたい感じ
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(std_msgs REQUIRED)

add_executable(talker src/talker.cpp)
ament_target_dependencies(talker rclcpp std_msgs)

add_executable(talker_with_service_param src/talker_with_service_param.cpp)
ament_target_dependencies(talker_with_service_param rclcpp std_msgs)

add_executable(listener src/listener.cpp)
ament_target_dependencies(listener rclcpp std_msgs)

# add_libraryは必要なはず
add_library(talker_component SHARED src/talker_component.cpp)
ament_target_dependencies(talker_component rclcpp rclcpp_components std_msgs)
# EXECUTABLEは別名の必要あり，rclcpp_components_register_nodeの中でadd_executableが呼ばれているので
rclcpp_components_register_node(talker_component PLUGIN hello_world::TalkerComponent EXECUTABLE talker_component_node)

add_library(listener_component SHARED src/listener_component.cpp)
ament_target_dependencies(listener_component rclcpp rclcpp_components std_msgs)
rclcpp_components_register_node(listener_component PLUGIN hello_world::ListenerComponent EXECUTABLE listener_component_node)

# インストールはまとめる
install(TARGETS talker talker_with_service_param listener
        DESTINATION lib/${PROJECT_NAME})

install(TARGETS talker_component listener_component
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
)

install(DIRECTORY launch
  DESTINATION share/${PROJECT_NAME}
)

ament_package()
