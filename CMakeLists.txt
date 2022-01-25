cmake_minimum_required(VERSION 3.8)
project(registry)

include(cmake/turn_on_warnings.cmake)

# Try to find ccache to speed up compilation
find_program(ccache_binary ccache)
if (ccache_binary)
  set_property(GLOBAL PROPERTY RULE_LAUNCH_COMPILE "${ccache_binary}")
endif()

file(
  GLOB
  HEADER_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/*.h
)

set(REGISTRY_LIBRARY registry)
set(REGISTRY_LIBRARY_NS vt::lib::registry)

add_custom_target(registry_examples)
add_subdirectory(examples)

install(FILES ${HEADER_FILES} DESTINATION include)

add_library(${REGISTRY_LIBRARY} INTERFACE)
add_library(${REGISTRY_LIBRARY_NS} ALIAS ${REGISTRY_LIBRARY})

target_compile_features(${REGISTRY_LIBRARY} INTERFACE cxx_std_14)
target_compile_features(
  ${REGISTRY_LIBRARY} INTERFACE
  cxx_variadic_templates
  cxx_auto_type
  cxx_constexpr
)

target_include_directories(
  ${REGISTRY_LIBRARY} INTERFACE
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/src>
  $<INSTALL_INTERFACE:include>
)

install(
  TARGETS                 ${REGISTRY_LIBRARY}
  EXPORT                  ${REGISTRY_LIBRARY}
  LIBRARY DESTINATION     lib
  ARCHIVE DESTINATION     lib
  RUNTIME DESTINATION     bin
  INCLUDES DESTINATION    include
)

install(
  EXPORT                  ${REGISTRY_LIBRARY}
  DESTINATION             cmake
  NAMESPACE               vt::lib::
  FILE                    "registryTargets.cmake"
  COMPONENT               runtime
)

configure_file(
  cmake/registryConfig.cmake.in
  "${PROJECT_BINARY_DIR}/registryConfig.cmake" @ONLY
)

install(
  FILES "${PROJECT_BINARY_DIR}/registryConfig.cmake"
  DESTINATION cmake
)

export(
  TARGETS                   ${REGISTRY_LIBRARY}
  FILE                      "registryTargets.cmake"
  NAMESPACE                 vt::lib::
)
