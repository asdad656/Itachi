
add_executable(config_test ./config_test.cpp)

include_directories(config_test ${PROJECT_SOURCE_DIR}/src/Base/include)

target_link_libraries(config_test ITACHI_BASE)

add_dependencies(config_test ITACHI_BASE)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)