# System Architecture Overview

This document outlines the system architecture for the interactive scheduling program designed to assist individuals with memory impairments. The architecture is structured to ensure ease of use, reliability, and extendibility.

## Architecture Pattern

The system follows a **Layered Architecture** pattern, organized into distinct layers with specific responsibilities. This separation of concerns allows for independent development, testing, and maintenance of each layer.

### Layers and Components

1. **Presentation Layer (User Interface Layer):**
   - Responsible for handling all user interactions through the terminal.
   - **SW-C:** Terminal-Based User Interface

2. **Application Layer (Service Layer):**
   - Manages the core functionality of the application, orchestrating the flow between the user interface and the data management systems.
   - **SW-Cs:**
     - Scheduler: Manages daily activities and their scheduling.
     - Alert System: Handles notifications for activity starts and reminders.

3. **Domain Layer (Business Logic Layer):**
   - Defines the business rules and data models of the application.
   - **SW-Cs:**
     - Activity Manager: Manages the states (done/undone) of activities.
     - Time Management: Allows for the manipulation of time flow within the program.

4. **Data Access Layer:**
   - Manages the storage and retrieval of activity data.
   - **SW-C:** In-Memory Data Storage

5. **Utility Layer:**
   - Provides supporting functionalities that are used across the application.
   - **SW-Cs:**
     - Input Validation: Ensures user inputs are valid and in the correct format.
     - Time Conversion: Converts user inputs into a format usable by the scheduler.

## Software Components (SW-Cs)

### Terminal-Based User Interface
- **Description:** Facilitates user interaction with the program, displaying prompts, and collecting user inputs.
- **Responsibilities:**
  - Display the current or queried activity.
  - Collect and validate user inputs.
  - Interact with the Scheduler and Alert System to retrieve and display information.

### Scheduler
- **Description:** Manages the scheduling of daily activities, tracking their times and states.
- **Responsibilities:**
  - Store and manage a list of daily activities and their scheduled times.
  - Update the state of activities based on user interactions.

### Alert System
- **Description:** Sends notifications and reminders related to scheduled activities.
- **Responsibilities:**
  - Notify users at the start of an activity.
  - Send reminders 10 minutes before an activity ends if it is not marked as done.

### Activity Manager
- **Description:** Handles the internal state (done/undone) of each activity.
- **Responsibilities:**
  - Track and update activity states based on user confirmation.

### Time Management
- **Description:** Allows the program's time flow to be adjusted for faster simulation or testing.
- **Responsibilities:**
  - Modify the perception of time within the application to simulate different speeds.

### In-Memory Data Storage
- **Description:** Provides a temporary storage mechanism for activity schedules and states.
- **Responsibilities:**
  - Store activity details and states during the application's runtime.

### Input Validation
- **Description:** Ensures all user inputs meet the expected format and criteria.
- **Responsibilities:**
  - Validate time inputs and other user commands.

### Time Conversion
- **Description:** Converts user time inputs into a standardized format for processing.
- **Responsibilities:**
  - Ensure that time inputs are correctly interpreted by the Scheduler and Alert System.

## Conclusion

This architecture is designed to be robust, yet flexible, accommodating future enhancements and new features. By adhering to the Layered Architecture pattern, each component of the system can be independently developed and maintained, ensuring the application remains adaptable and easy to use for its intended audience.

