cmake_minimum_required(VERSION 3.0.0)
project(GrandmaScheduler VERSION 0.1.0 LANGUAGES C)

# Include the CTest module for enabling testing capabilities
include(CTest)
enable_testing()

# Specify directories to search for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Update your minimum required version based on the deprecation warning
cmake_minimum_required(VERSION 3.5...3.19)

# Debugging Unity path
file(GLOB UNITY_SRC "${PROJECT_SOURCE_DIR}/lib/Unity/src/unity.c")
message(STATUS "Unity Source: ${UNITY_SRC}")

# Include the Unity directory
include_directories(${PROJECT_SOURCE_DIR}/lib/Unity/src)

# Add an executable target named 'GrandmaScheduler' to the project
add_executable(GrandmaScheduler
    src/main.c
    src/scheduler.c
    src/ui.c
    src/utils.c
    src/time_management.c
    src/alerts.c
    # Add any other source files here
)

# Assuming you have the rest of your CMake configuration here...

# Add Unity test executable, now using UNITY_SRC variable
add_executable(test_scheduler tests/test_scheduler.c)
target_include_directories(test_scheduler PRIVATE ${PROJECT_SOURCE_DIR}/lib/Unity/src)
target_sources(test_scheduler PRIVATE ${UNITY_SRC} src/scheduler.c src/utils.c src/time_management.c src/alerts.c)

# Register the test with CTest
add_test(NAME SchedulerTest COMMAND test_scheduler)

# Set the CPack variables for packaging/distribution
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

