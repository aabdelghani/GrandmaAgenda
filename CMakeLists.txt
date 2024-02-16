cmake_minimum_required(VERSION 3.0.0)
project(GrandmaScheduler VERSION 0.1.0 LANGUAGES C)

# Include the CTest module for enabling testing capabilities
include(CTest)
enable_testing()

# Specify directories to search for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

# Correct the path to Unity's include directory
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

# Add Unity test executable
add_executable(test_scheduler tests/test_scheduler.c)
# Include Unity's directory for the test_scheduler target specifically
target_include_directories(test_scheduler PRIVATE ${PROJECT_SOURCE_DIR}/lib/Unity/src)
# Adding Unity's source file to the test_scheduler target
target_sources(test_scheduler PRIVATE ${PROJECT_SOURCE_DIR}/lib/Unity/src/unity.c src/scheduler.c src/utils.c src/time_management.c src/alerts.c)

# Register the test with CTest
add_test(NAME SchedulerTest COMMAND test_scheduler)

# Set the CPack variables for packaging/distribution
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

