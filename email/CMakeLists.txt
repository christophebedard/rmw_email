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

include(cmake/add_example.cmake)

find_package(ament_cmake_ros REQUIRED)
find_package(rcpputils REQUIRED)
find_package(spdlog_vendor REQUIRED)
find_package(spdlog REQUIRED)

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

# Lib
set(SOURCES
  src/context.cpp
  src/curl/context.cpp
  src/curl/executor.cpp
  src/email/payload_utils.cpp
  src/email/polling_manager.cpp
  src/email/receiver.cpp
  src/email/response_utils.cpp
  src/email/sender.cpp
  src/init.cpp
  src/log.cpp
  src/options.cpp
  src/pub_sub.cpp
  src/publisher.cpp
  src/service.cpp
  src/service_client.cpp
  src/service_handler.cpp
  src/service_server.cpp
  src/subscriber.cpp
  src/subscription_handler.cpp
  src/utils.cpp
)

add_library(${PROJECT_NAME} SHARED ${SOURCES})
if(CURL_USE_VENDOR)
  ament_target_dependencies(${PROJECT_NAME} libcurl_vendor)
else()
  target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARIES})
endif()
ament_target_dependencies(${PROJECT_NAME} rcpputils spdlog)
if(WIN32)
  # Causes the visibility macros to use dllexport rather than dllimport
  # which is appropriate when building the dll but not consuming it.
  target_compile_definitions(${PROJECT_NAME} PRIVATE "EMAIL_BUILDING_DLL")
endif()
target_link_libraries(${PROJECT_NAME} spdlog::spdlog)
target_include_directories(${PROJECT_NAME} PUBLIC
  "$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>"
  "$<INSTALL_INTERFACE:include>"
)
ament_export_include_directories(include)
ament_export_dependencies(ament_cmake_ros rcpputils spdlog_vendor spdlog)
ament_export_targets(${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_libraries(${PROJECT_NAME})
if(CURL_USE_VENDOR)
  ament_export_dependencies(libcurl_vendor)
else()
  ament_export_libraries(${CURL_LIBRARIES})
endif()

install(
  DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/
  DESTINATION include
)
install(
  TARGETS ${PROJECT_NAME}
  EXPORT ${PROJECT_NAME}
  LIBRARY DESTINATION lib
  ARCHIVE DESTINATION lib
  RUNTIME DESTINATION bin
  INCLUDES DESTINATION include
)

# Examples & executables for testing the lib
add_example(send)
add_example(receive)
add_example(pub)
add_example(sub)
add_example(service_client)
add_example(service_server)

if(BUILD_TESTING)
  #set(ament_cmake_cppcheck_ADDITIONAL_INCLUDE_DIRS ${CURL_INCLUDE_DIRS})
  find_package(ament_lint_auto REQUIRED)
  ament_lint_auto_find_test_dependencies()

  find_package(ament_cmake_gtest REQUIRED)
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
endif()

ament_package()
