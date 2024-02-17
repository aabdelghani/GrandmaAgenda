cmake_minimum_required(VERSION 3.5)

project(GrandmaScheduler VERSION 0.1.0 LANGUAGES C)

# Specify directories to search for header files
include_directories(${PROJECT_SOURCE_DIR}/include)

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

# Set the CPack variables for packaging/distribution
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)

