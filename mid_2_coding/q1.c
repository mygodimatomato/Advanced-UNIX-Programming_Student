#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#define MAXSZ 500

int main(int argc, char* argv[])
{
	time_t current_time;	
	struct tm* tmptr;
	unsigned int cnt = 0;
	char filename[MAXSZ];
	time(&current_time);
	tmptr = localtime(&current_time);
	size_t filename_len = strftime(filename, MAXSZ, "q1-%F-%T.txt", tmptr);
	filename[filename_len] = '\0';

	while(1)
	{
		cnt++;
		sleep(10u);	
		if (cnt > 5)
		{
			FILE * file = fopen(filename, "a");
			cnt = 0;
			time(&current_time);
			tmptr = localtime(&current_time);
			fprintf(file, "%d\n", tmptr->tm_sec);
			printf("%d\n", tmptr->tm_sec);
			fclose(file);
		}
	}
	return 0;
}

