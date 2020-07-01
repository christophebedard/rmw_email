cmake_minimum_required(VERSION 3.5)
project(email)

# Default to C++17 for std::optional
if(NOT CMAKE_CXX_STANDARD)
  # set(CMAKE_CXX_STANDARD 14)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

find_package(ament_cmake_ros REQUIRED)

find_package(CURL REQUIRED)
# message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
# message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
# message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")

# Lib
set(SOURCES
  src/email_receiver.cpp
  src/email_sender.cpp
  src/utils.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_targets(${PROJECT_NAME}_export HAS_LIBRARY_TARGET)
ament_export_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})

# Tools for sending/receiving emails (& testing the lib)
add_executable(send
  src/send.cpp
)
target_link_libraries(send
  ${PROJECT_NAME}
)
install(TARGETS
  send
  DESTINATION lib/${PROJECT_NAME}
)
add_executable(receive
  src/receive.cpp
)
target_link_libraries(receive
  ${PROJECT_NAME}
)
install(TARGETS
  receive
  DESTINATION lib/${PROJECT_NAME}
)

install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}_export
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

if(BUILD_TESTING)
  #set(ament_cmake_cppcheck_ADDITIONAL_INCLUDE_DIRS ${CURL_INCLUDE_DIRS})
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
