cmake_minimum_required(VERSION 3.5)
project(GrandmaScheduler C)

set(CMAKE_C_STANDARD 99)

set(THREADS_PREFER_PTHREAD_FLAG ON)

# Specify directories to search for header files
include_directories(${PROJECT_SOURCE_DIR}/include)
find_package(Threads REQUIRED)
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

target_link_libraries(GrandmaScheduler PRIVATE Threads::Threads)
