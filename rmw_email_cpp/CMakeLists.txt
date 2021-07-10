cmake_minimum_required(VERSION 3.5)
project(rmw_email_cpp)

if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

find_package(ament_cmake_ros REQUIRED)

# Try to find 'email' and skip building this if not found
find_package(email QUIET)
if(NOT email_FOUND)
  message(WARNING "Could not find 'email' - skipping '${PROJECT_NAME}'")
  ament_package()
  return()
endif()

find_package(dynmsg REQUIRED)
find_package(rcutils REQUIRED)
find_package(rcpputils REQUIRED)
find_package(rosidl_runtime_c REQUIRED)
find_package(rosidl_typesupport_introspection_c REQUIRED)
find_package(rosidl_typesupport_introspection_cpp REQUIRED)
find_package(rmw REQUIRED)

add_library(${PROJECT_NAME}
  src/conversion.cpp
  src/gid.cpp
  src/identifier.cpp

  src/rmw_gid.cpp
  src/rmw_implementation_serialization.cpp
  src/rmw_init.cpp
  src/rmw_log.cpp
  src/rmw_node.cpp
  src/rmw_publish.cpp
  src/rmw_publisher.cpp
  src/rmw_subscription.cpp
)

ament_target_dependencies(${PROJECT_NAME}
  email
  dynmsg
  rcutils
  rcpputils
  rosidl_runtime_c
  rosidl_typesupport_introspection_c
  rosidl_typesupport_introspection_cpp
  rmw
)
target_include_directories(${PROJECT_NAME} PRIVATE
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
)

ament_export_dependencies(dynmsg)
ament_export_dependencies(rcutils)
ament_export_dependencies(rcpputils)
ament_export_dependencies(rmw)
ament_export_dependencies(rosidl_runtime_c)
ament_export_dependencies(rosidl_typesupport_introspection_c)
ament_export_dependencies(rosidl_typesupport_introspection_cpp)

configure_rmw_library(${PROJECT_NAME})
ament_export_libraries(${PROJECT_NAME})
register_rmw_implementation(
  "c:rosidl_typesupport_c:rosidl_typesupport_introspection_c"
  "cpp:rosidl_typesupport_cpp:rosidl_typesupport_introspection_cpp"
)

install(
  TARGETS ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_conversion
    test/test_conversion.cpp
  )
  target_link_libraries(test_conversion ${PROJECT_NAME})
  ament_target_dependencies(test_conversion dynmsg std_msgs)
endif()

ament_package()