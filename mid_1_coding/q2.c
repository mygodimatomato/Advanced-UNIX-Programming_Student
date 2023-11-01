#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/times.h>
#include <string.h>
#include <time.h>

// 20MB
#define BUFF_SIZE 20971520

#define BUFF_SIZE_1 1
#define BUFF_SIZE_2 32
#define BUFF_SIZE_3 1024
#define BUFF_SIZE_4 4096
#define BUFF_SIZE_5 4096
// #define BUFF_SIZE_6 

void func(char* source_file, char* output_file, size_t buff_size)
{
  FILE *fd, *fd2;
  char *buffer;
  FILE *mem_stream;

  fd = fopen(source_file, "rb+"); // read from this file
  fseek(fd, 0, SEEK_END);
  int sz = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * sz);
  fd2 = fopen(output_file, "wb+");// read to this file
  mem_stream = fmemopen(buffer, sizeof(char) * sz, "wb+");

	long clktck = 0;
	clktck = sysconf(_SC_CLK_TCK);

	struct tms start, end;
  size_t readed_sz;
	clock_t t_start, t_end;
	t_start = times(&start);
  while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_1, fd)) != 0){
  }
	t_end = times(&end);

	printf("utime: %llf ", (end.tms_utime - start.tms_utime)/(double)(clktck));
	printf("stime: %llf ", (end.tms_stime - start.tms_stime)/(double)(clktck));
	printf("clock: %llf\n", (t_end - t_start)/(double)(clktck));

	fseek(fd, 0, SEEK_SET);
  while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_1, fd)) != 0){
    fwrite(mem_stream, sizeof(char), readed_sz, fd2);
  }
  fclose(fd);
  fclose(fd2);
  fclose(mem_stream);
  free(buffer);
}
/*
void func_fgets(char* source_file, char* output_file, size_t buff_size)
{
  FILE *fd, *fd2;
  char *buffer;
  FILE *mem_stream;

  fd = fopen(source_file, "rb+"); // read from this file
  fseek(fd, 0, SEEK_END);
  int sz = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * sz);
  fd2 = fopen(output_file, "wb+");// read to this file
  mem_stream = fmemopen(buffer, sizeof(char) * sz, "wb+");

	long clktck = 0;
	clktck = sysconf(_SC_CLK_TCK);

	struct tms start, end;
  size_t readed_sz;
	clock_t t_start, t_end;
	t_start = times(&start);
  while((fgets(buffer, buff_size, fd)) != 0){
  }
	t_end = times(&end);

	printf("utime: %llf ", (end.tms_utime - start.tms_utime)/(double)(clktck));
	printf("stime: %llf ", (end.tms_stime - start.tms_stime)/(double)(clktck));
	printf("clock: %llf\n", (t_end - t_start)/(double)(clktck));

  while((fgets(buffer, buff_size, fd)) != 0){
		buffer[buff_size]='\0';
		fputs(buffer, fd2);
  }
  fclose(fd);
  fclose(fd2);
  fclose(mem_stream);
  free(buffer);
}

void func_fgets(char* source_file, char* output_file, size_t buff_size)
{
  FILE *fd, *fd2;
  char *buffer;
  FILE *mem_stream;

  fd = fopen(source_file, "rb+"); // read from this file
  fseek(fd, 0, SEEK_END);
  int sz = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * sz);
  fd2 = fopen(output_file, "wb+");// read to this file
  mem_stream = fmemopen(buffer, sizeof(char) * sz, "wb+");

	long clktck = 0;
	clktck = sysconf(_SC_CLK_TCK);

	struct tms start, end;
  size_t readed_sz;
	clock_t t_start, t_end;
	t_start = times(&start);
  while((fgets(buffer, buff_size, fd)) != 0){
  }
	t_end = times(&end);

	printf("utime: %llf ", (end.tms_utime - start.tms_utime)/(double)(clktck));
	printf("stime: %llf ", (end.tms_stime - start.tms_stime)/(double)(clktck));
	printf("clock: %llf\n", (t_end - t_start)/(double)(clktck));

  while((fgets(buffer, buff_size, fd)) != 0){
		buffer[buff_size]='\0';
		fputs(buffer, fd2);
  }
  fclose(fd);
  fclose(fd2);
  fclose(mem_stream);
  free(buffer);
}
*/

int main() {
	func("source2", "output1", BUFF_SIZE_1);
	func("source2", "output2", BUFF_SIZE_2);
	func("source2", "output3", BUFF_SIZE_3);
	func("source2", "output4", BUFF_SIZE_4);
//	func("source2", "output2", BUFF_SIZE_5);

// // ////////////////////////////////////////////////////
//   buffer = malloc(sizeof(char) * BUFF_SIZE_5);
//   fd = fopen("source2", "r+"); // read from this file
//   fd2 = fopen("output5", "w+");// read to this file
//   mem_stream = fmemopen(buffer, BUFF_SIZE_5, "w+");

//   while(fread(mem_stream, sizeof(char), BUFF_SIZE_5, fd) != 0){
//     fwrite(mem_stream, sizeof(char), BUFF_SIZE_5, fd2);
//   }
//   fclose(fd);
//   fclose(fd2);
//   free(buffer);
//   free(mem_stream);
// ////////////////////////////////////////////////////
//   // fd = fopen("source2", "r+"); // read from this file
//   // fd2 = fopen("output6", "w+");// read to this file

  return 0;
}
