#include "scheduler.h" // Assuming addActivity is declared here
#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


extern char* descriptions[];


void readActivitiesFromCSV() {
    FILE* file = fopen(CSV_FILE_PATH, "r");
    if (!file) {
        perror("Unable to open activities.txt file or doesn't exist in db folder");
        return;
    }

    char line[MAX_LINE_LENGTH];
    // Skip the header line
    fgets(line, MAX_LINE_LENGTH, file);

    while (fgets(line, MAX_LINE_LENGTH, file)) {
        char *startTime, *endTime, *description;
        
        // Assuming CSV format is: Start Time,End Time,Description,Status (ignoring Status)
        startTime = strtok(line, ",");
        endTime = strtok(NULL, ",");
        description = strtok(NULL, ",");
        
        if (startTime && endTime && description) {
            addActivity(startTime, endTime, description);
        }
    }

    fclose(file);
}



void parseAndConvertTime(const char* startTimeStr, const char* endTimeStr, const char* currentTimeStr,
                         int* startTimeInMinutes, int* endTimeInMinutes, int* currentTimeInMinutes) {
    int startHour, startMinute, endHour, endMinute, currentHour, currentMinute;

    sscanf(startTimeStr, "%d:%d", &startHour, &startMinute);
    sscanf(endTimeStr, "%d:%d", &endHour, &endMinute);
    sscanf(currentTimeStr, "%d:%d", &currentHour, &currentMinute);

    *startTimeInMinutes = startHour * 60 + startMinute;
    *endTimeInMinutes = endHour * 60 + endMinute;
    *currentTimeInMinutes = currentHour * 60 + currentMinute;
}