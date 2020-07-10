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
find_package(rcpputils REQUIRED)

set(CURL_USE_VENDOR FALSE)
find_package(CURL)
if(NOT CURL_FOUND)
  message(STATUS "libcurl not found; using libcurl_vendor")
  find_package(libcurl_vendor REQUIRED)
  set(CURL_USE_VENDOR TRUE)
endif()
# message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
# message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
# message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")

# Lib
set(SOURCES
  src/context.cpp
  src/curl/context.cpp
  src/curl/executor.cpp
  src/email/payload_utils.cpp
  src/email/receiver.cpp
  src/email/response_utils.cpp
  src/email/sender.cpp
  src/init.cpp
  src/options.cpp
  src/pub_sub.cpp
  src/publisher.cpp
  src/subscriber.cpp
  src/utils.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
if(CURL_USE_VENDOR)
  ament_target_dependencies(${PROJECT_NAME} libcurl_vendor)
else()
  target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()
ament_target_dependencies(${PROJECT_NAME} rcpputils)
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_targets(${PROJECT_NAME}_export HAS_LIBRARY_TARGET)
if(CURL_USE_VENDOR)
  ament_export_dependencies(libcurl_vendor)
else()
  ament_export_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()

# Examples & executables for testing the lib
add_executable(send
  src/example/send.cpp
)
target_link_libraries(send
  ${PROJECT_NAME}
)
install(TARGETS
  send
  DESTINATION lib/${PROJECT_NAME}
)
add_executable(receive
  src/example/receive.cpp
)
target_link_libraries(receive
  ${PROJECT_NAME}
)
install(TARGETS
  receive
  DESTINATION lib/${PROJECT_NAME}
)
add_executable(pub
  src/example/pub.cpp
)
target_link_libraries(pub
  ${PROJECT_NAME}
)
install(TARGETS
  pub
  DESTINATION lib/${PROJECT_NAME}
)
add_executable(sub
  src/example/sub.cpp
)
target_link_libraries(sub
  ${PROJECT_NAME}
)
install(TARGETS
  sub
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

  find_package(ament_cmake_gtest REQUIRED)
  ament_add_gtest(test_utils
    test/test_utils.cpp
  )
  target_link_libraries(test_utils ${PROJECT_NAME})
endif()

ament_package()
