#include <stdio.h>
#include <time.h>
#include <stdlib.h>

int main() {
   setenv("TZ", "Asia/Taipei", 1);
   tzset();

   time_t tme;
   struct tm *tstruct;
   time(&tme);
   tstruct = localtime(&tme);

   char buff[100];
   strftime(buff, 100, "%H:%M:%S, %A %B %d, %Y", tstruct);
   printf("%s\n", buff);
}
