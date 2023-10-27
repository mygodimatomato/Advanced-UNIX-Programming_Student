#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define BUFF_SIZE_1 1
#define BUFF_SIZE_2 32
#define BUFF_SIZE_3 1024
#define BUFF_SIZE_4 4096
#define BUFF_SIZE_5 4096
// #define BUFF_SIZE_6 

int main() {
  FILE *fd, *fd2;
  char *buffer;
  FILE *mem_stream;
  buffer = malloc(sizeof(char) * BUFF_SIZE_1);
  fd = fopen("source2", "rb+"); // read from this file
  fd2 = fopen("output1", "wb+");// read to this file
  mem_stream = fmemopen(buffer, BUFF_SIZE_1, "wb+");

  while(fread(mem_stream, sizeof(char), BUFF_SIZE_1, fd) != 0){
    fwrite(mem_stream, sizeof(char), BUFF_SIZE_1, fd2);
  }
  fclose(fd);
  fclose(fd2);
  fclose(mem_stream);
  free(buffer);

// // // ////////////////////////////////////////////////////
  buffer = malloc(sizeof(char) * BUFF_SIZE_2);
  fd = fopen("source2", "rb+"); // read from this file
  fd2 = fopen("output2", "wb+");// read to this file
  mem_stream = fmemopen(buffer, BUFF_SIZE_2, "wb+");

  while(fread(mem_stream, sizeof(char), BUFF_SIZE_2, fd) != 0){
    fwrite(mem_stream, sizeof(char), BUFF_SIZE_2, fd2);
  }

  fclose(fd);
  fclose(fd2);
  free(buffer);
  fclose(mem_stream);

// // // ////////////////////////////////////////////////////
  buffer = malloc(sizeof(char) * BUFF_SIZE_3);
  fd = fopen("source2", "rb+"); // read from this file
  fd2 = fopen("output3", "wb+");// read to this file
  mem_stream = fmemopen(buffer, BUFF_SIZE_3, "wb+");

  while(fread(mem_stream, sizeof(char), BUFF_SIZE_3, fd) != 0){
    fwrite(mem_stream, sizeof(char), BUFF_SIZE_3, fd2);
  }

  fclose(fd);
  fclose(fd2);
  free(buffer);
  fclose(mem_stream);
// // ////////////////////////////////////////////////////
  FILE *mem_stream2;
  buffer = malloc(sizeof(char) * BUFF_SIZE_3);
  fd = fopen("source2", "rb+"); // read from this file
  fd2 = fopen("output4", "wb+");// read to this file
  mem_stream2 = fmemopen(buffer, BUFF_SIZE_3, "wb+");

  while(fread(mem_stream, sizeof(char), BUFF_SIZE_4, fd) != 0){
    fwrite(mem_stream, sizeof(char), BUFF_SIZE_4, fd2);
  }
  fclose(fd);
  fclose(fd2);
  free(buffer);
  fclose(mem_stream2);
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