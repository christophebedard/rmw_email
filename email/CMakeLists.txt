cmake_minimum_required(VERSION 3.5)
project(email)

# Default to C++17 for std::optional
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
  add_compile_options(/W4)
endif()

find_package(ament_cmake_ros REQUIRED)
find_package(rcpputils REQUIRED)
find_package(rcutils REQUIRED)
find_package(spdlog_vendor REQUIRED)
find_package(spdlog REQUIRED)
find_package(yaml_cpp_vendor REQUIRED)

set(CURL_USE_VENDOR TRUE)
# TODO(christophebedard) switch to using system curl when possible,
# but for now using the vendor package makes it easier for Windows
#find_package(CURL)
if(CURL_USE_VENDOR OR NOT CURL_FOUND)
  message(STATUS "using libcurl_vendor")
  find_package(libcurl_vendor REQUIRED)
  set(CURL_USE_VENDOR TRUE)
endif()
message(STATUS "Found CURL version: ${CURL_VERSION_STRING}")
message(STATUS "Using CURL include dir(s): ${CURL_INCLUDE_DIRS}")
message(STATUS "Using CURL lib(s): ${CURL_LIBRARIES}")

option(EMAIL_ENABLE_TRACING "Enable building with static tracepoints using LTTng" ON)
if(EMAIL_ENABLE_TRACING)
  find_package(PkgConfig)
  if(PkgConfig_FOUND)
    pkg_check_modules(LTTNG lttng-ust)
    if(LTTNG_FOUND)
      message(STATUS "Building with LTTng instrumentation support")
      set(EMAIL_HAS_LTTNG_TRACING "1")
    else()
      message("Not building with LTTng since lttng-ust was not found")
    endif()
  endif()
endif()
configure_file(include/${PROJECT_NAME}/config.hpp.in include/${PROJECT_NAME}/config.hpp)

# Lib
set(SOURCES
  src/communication_info.cpp
  src/context.cpp
  src/curl/context.cpp
  src/curl/executor.cpp
  src/email/curl_receiver.cpp
  src/email/curl_sender.cpp
  src/email/handler.cpp
  src/email/intra_receiver.cpp
  src/email/intra_sender.cpp
  src/email/payload_utils.cpp
  src/email/polling_manager.cpp
  src/email/receiver.cpp
  src/email/response_utils.cpp
  src/email/sender.cpp
  src/gid.cpp
  src/gid_object.cpp
  src/guard_condition.cpp
  src/init.cpp
  src/log.cpp
  src/message_info.cpp
  src/named_object.cpp
  src/options.cpp
  src/pub_sub.cpp
  src/publisher.cpp
  src/service.cpp
  src/service_client.cpp
  src/service_handler.cpp
  src/service_info.cpp
  src/service_server.cpp
  src/subscription.cpp
  src/subscription_handler.cpp
  src/timestamp.cpp
  src/utils.cpp
  src/wait.cpp
  src/wait_set.cpp
)

if(EMAIL_HAS_LTTNG_TRACING)
  list(APPEND SOURCES src/lttng.cpp)
endif()

add_library(${PROJECT_NAME} SHARED ${SOURCES})
if(CURL_USE_VENDOR)
  ament_target_dependencies(${PROJECT_NAME} libcurl_vendor)
else()
  target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()
ament_target_dependencies(${PROJECT_NAME}
  rcpputils
  rcutils
  spdlog
  yaml_cpp_vendor
)
if(WIN32)
  # Causes the visibility macros to use dllexport rather than dllimport
  # which is appropriate when building the dll but not consuming it.
  target_compile_definitions(${PROJECT_NAME} PRIVATE "EMAIL_BUILDING_DLL")
endif()
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
if(EMAIL_HAS_LTTNG_TRACING)
  target_link_libraries(${PROJECT_NAME} ${LTTNG_LIBRARIES})
endif()
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_dependencies(
  ament_cmake_ros
  rcpputils
  rcutils
  spdlog_vendor
  spdlog
  yaml_cpp_vendor
)
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_libraries(${PROJECT_NAME})
if(CURL_USE_VENDOR)
  ament_export_dependencies(libcurl_vendor)
else()
  ament_export_libraries(${CURL_LIBRARIES})
endif()

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ ${CMAKE_CURRENT_BINARY_DIR}/include/
  DESTINATION include
  PATTERN "*.in" EXCLUDE
)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
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
  ament_add_gtest(test_cli
    test/test_cli.cpp
  )
  target_link_libraries(test_cli ${PROJECT_NAME})
  ament_add_gtest(test_communication_info
    test/test_communication_info.cpp
  )
  target_link_libraries(test_communication_info ${PROJECT_NAME})
  ament_add_gtest(test_containers
    test/test_containers.cpp
  )
  target_link_libraries(test_containers ${PROJECT_NAME})
  ament_add_gtest(test_context
    test/test_context.cpp
  )
  target_link_libraries(test_context ${PROJECT_NAME})
  ament_add_gtest(test_end_to_end
    test/test_end_to_end.cpp
  )
  target_link_libraries(test_end_to_end ${PROJECT_NAME})
  ament_add_gtest(test_gid
    test/test_gid.cpp
  )
  target_link_libraries(test_gid ${PROJECT_NAME})
  ament_add_gtest(test_handlers
    test/test_handlers.cpp
  )
  target_link_libraries(test_handlers ${PROJECT_NAME})
  ament_add_gtest(test_log
    test/test_log.cpp
  )
  target_link_libraries(test_log ${PROJECT_NAME})
  ament_add_gtest(test_options
    test/test_options.cpp
  )
  target_link_libraries(test_options ${PROJECT_NAME})
  ament_add_gtest(test_utils
    test/test_utils.cpp
    ENV EMAIL_TEST_UTILS_TEST_ENV_VAR=value42 EMAIL_TEST_UTILS_FILE=${CMAKE_CURRENT_SOURCE_DIR}/test/test_utils.cpp
  )
  target_link_libraries(test_utils ${PROJECT_NAME})
  ament_add_gtest(test_utils_payload
    test/test_utils_payload.cpp
  )
  target_link_libraries(test_utils_payload ${PROJECT_NAME})
  ament_add_gtest(test_utils_response
    test/test_utils_response.cpp
  )
  target_link_libraries(test_utils_response ${PROJECT_NAME})
  ament_add_gtest(test_pub_sub
    test/test_pub_sub.cpp
  )
  target_link_libraries(test_pub_sub ${PROJECT_NAME})
  ament_add_gtest(test_service
    test/test_service.cpp
  )
  target_link_libraries(test_service ${PROJECT_NAME})
  ament_add_gtest(test_timestamp
    test/test_timestamp.cpp
  )
  target_link_libraries(test_timestamp ${PROJECT_NAME})
  ament_add_gtest(test_wait_set
    test/test_wait_set.cpp
  )
  target_link_libraries(test_wait_set ${PROJECT_NAME})
endif()

ament_package()
