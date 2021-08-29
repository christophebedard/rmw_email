cmake_minimum_required(VERSION 3.5)
project(email_examples)

# Default to C++17 for std::optional
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

include(cmake/add_example.cmake)

find_package(ament_cmake_ros REQUIRED)
find_package(email REQUIRED)

# Examples & executables for testing the lib
add_example(intra_pub_sub_wait_message_info)
add_example(intra_service_client_server_wait_service_info)
add_example(send)
add_example(receive)
add_example(pub)
add_example(sub)
add_example(sub_wait)
add_example(sub_wait_message_info)
add_example(sub_wait_set)
add_example(service_client)
add_example(service_client_wait)
add_example(service_client_wait_service_info)
add_example(service_server)
add_example(service_server_wait)
add_example(service_server_wait_service_info)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
