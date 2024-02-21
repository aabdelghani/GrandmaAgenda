#ifndef UTILS_H
#define UTILS_H

#define MAX_LINE_LENGTH 1024
#define MAX_TIME_LENGTH 6
#define MAX_DESC_LENGTH 256
#define CSV_FILE_PATH "../db/activities.csv"




void readActivitiesFromCSV();
void parseAndConvertTime(const char* startTimeStr, const char* endTimeStr, const char* currentTimeStr,
                         int* startTimeInMinutes, int* endTimeInMinutes, int* currentTimeInMinutes);

#endif // UTILS_H

