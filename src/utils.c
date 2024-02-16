#include "utils.h"
#include "scheduler.h" // Assuming addActivity is declared here
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


extern char* descriptions[];

bool validateTimeFormat(const char* time) {
    // Expected format: HH:MM
    if (strlen(time) != 5) return false;
    if (!isdigit(time[0]) || !isdigit(time[1]) || time[2] != ':' || !isdigit(time[3]) || !isdigit(time[4])) return false;

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return false;

    return true;
}

void addAutomaticActivities(int descriptionsSize) {
    int interval = 24 * 60 / 8; // Divide the day into 8 equal intervals
    for (int i = 0; i < 8; i++) {
        char startTime[6], endTime[6];
        int startHour = (i * interval) / 60;
        int startMinute = (i * interval) % 60;
        sprintf(startTime, "%02d:%02d", startHour, startMinute);
        
        int endHour = startHour;
        int endMinute = startMinute + 30;
        if (endMinute >= 60) {
            endMinute -= 60;
            endHour++;
        }
        sprintf(endTime, "%02d:%02d", endHour, endMinute);
        
        char* description = descriptions[rand() % descriptionsSize];
        
        addActivity(startTime, endTime, description);
    }
}

