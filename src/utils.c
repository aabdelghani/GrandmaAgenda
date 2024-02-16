#include "utils.h"
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool validateTimeFormat(const char* time) {
    // Expected format: HH:MM
    if (strlen(time) != 5) return false;
    if (!isdigit(time[0]) || !isdigit(time[1]) || time[2] != ':' || !isdigit(time[3]) || !isdigit(time[4])) return false;

    int hours = (time[0] - '0') * 10 + (time[1] - '0');
    int minutes = (time[3] - '0') * 10 + (time[4] - '0');

    if (hours < 0 || hours > 23 || minutes < 0 || minutes > 59) return false;

    return true;
}

