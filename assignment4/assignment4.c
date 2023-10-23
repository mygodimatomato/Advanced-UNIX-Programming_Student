#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
  time_t rawtime;
  struct tm * timeinfo;
  char buffer [80];

  //Set the time zone to Asia/Taipei
  setenv("TZ", "Asia/Taipei", 1);
  tzset();

  // Obtain the current time
  time(&rawtime);

  // Convert it to local time
  timeinfo = localtime(&rawtime);

  // Format the time using strftime
  strftime(buffer, 80, "%a %b %d %H:%M:%S %Z %Y", timeinfo);
  printf("%s\n", buffer);

  // Change the time zone to America/New_York
  setenv("TZ", "PST8PDT", 1);
  tzset();

  // Obtain the current time again
  time(&rawtime);

  // Convert it to local time
  timeinfo = localtime(&rawtime);

  // Format the time using strftime
  strftime(buffer, 80, "%a %b %d %H:%M:%S %Z %Y", timeinfo);
  // printf("%s\n", buffer);

  return 0;
}