# GrandmaScheduler

## 1. Introduction

GrandmaScheduler is a command-line scheduling application designed to assist individuals with memory impairments by providing an interactive agenda for daily activities. It aims to improve the quality of life for users by reminding them of their scheduled tasks throughout the day.

## 2. Features

1. **Interactive Schedule Query:** Users can input a specific time to see what activity is scheduled at that moment.
2. **Reminders and Alerts:** The application provides alerts for activities about to start and reminders for activities nearing completion, ensuring tasks are completed on time.
3. **Activity State Tracking:** Each activity can be marked as "undone" or "done," allowing users to track their progress throughout the day.
4. **Adjustable Time Flow:** For demonstration or faster simulation, the application allows time flow adjustment to simulate different parts of the day.

## 3. Getting Started

### 3.1 Prerequisites

- A Linux operating system (Windows/MacOS users can use a Linux-like environment such as WSL or a virtual machine).
- GCC compiler for compiling C programs.
- CMake (version 3.22.1 or higher) for building the project.

### 3.2 Installation

1. **Clone the Repository:**

   ```bash
   git clone https://github.com/aabdelghani/GrandmaScheduler
   cd GrandmaScheduler

2. **Build the Project:**
mkdir build && cd build
cmake ..
cmake --build .

This compiles GrandmaScheduler and generates an executable in the build directory.


### 3.3 Running GrandmaScheduler

Navigate to the build directory and execute the binary to run the application:

./GrandmaScheduler
Follow the on-screen instructions to interact with the scheduler. Input times in the HH:MM format to query scheduled activities, or use other commands as prompted by the application.

## 4. Documentation

For more detailed information on how to use GrandmaScheduler, contribute to the project, or understand its architecture, please refer to the following documentation:

- [System Architecture Overview](/docs/markdown/ArchitectureOverview.md): A detailed explanation of the system architecture and design decisions.
- [Flowchart Overview](/docs/markdown/FlowchartOverview.md): A visual representation of the application's logic flow.

