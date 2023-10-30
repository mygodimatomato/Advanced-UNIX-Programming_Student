#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

// 20MB
#define BUFF_SIZE 20971520

#define BUFF_SIZE_1 1
#define BUFF_SIZE_2 32
#define BUFF_SIZE_3 1024
#define BUFF_SIZE_4 4096
#define BUFF_SIZE_5 4096
// #define BUFF_SIZE_6 

void func(char *str1, char*str2)
{
  
  FILE *fd, *fd2;
  char *buffer;
  FILE *mem_stream;

  fd = fopen("source2", "rb+"); // read from this file
  fseek(fd, 0, SEEK_END);
  int sz = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  buffer = malloc(sizeof(char) * sz);
  fd2 = fopen("output1", "wb+");// read to this file
  mem_stream = fmemopen(buffer, sizeof(char) * sz, "wb+");

  size_t readed_sz;
  while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_1, fd)) != 0){
    fwrite(mem_stream, sizeof(char), readed_sz, fd2);
  }
  fclose(fd);
  fclose(fd2);
  fclose(mem_stream);
  free(buffer);

}


int main() {
// // // // // ////////////////////////////////////////////////////
//   buffer = malloc(sizeof(char) * sz);
//   fd = fopen("source2", "rb+"); // read from this file
//   fd2 = fopen("output2", "wb+");// read to this file
//   mem_stream = fmemopen(buffer, sizeof(char) * sz, "wb+");

//   while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_2, fd)) != 0){
//     fwrite(mem_stream, sizeof(char), readed_sz, fd2);
//   }

//   fclose(fd);
//   fclose(fd2);
//   free(buffer);
//   fclose(mem_stream);

// // // // ////////////////////////////////////////////////////
//   buffer = malloc(sizeof(char) * sz);
//   fd = fopen("source2", "rb+"); // read from this file
//   fd2 = fopen("output3", "wb+");// read to this file
//   mem_stream = fmemopen(buffer, sizeof(char)*sz, "wb+");

// while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_3, fd)) != 0){
//     fwrite(mem_stream, sizeof(char), readed_sz, fd2);
//   }

//   fclose(fd);
//   fclose(fd2);
//   free(buffer);
//   fclose(mem_stream);
// // // ////////////////////////////////////////////////////
//   buffer = malloc(sizeof(char) * sz);
//   fd = fopen("source2", "rb+"); // read from this file
//   fd2 = fopen("output3", "wb+");// read to this file
//   mem_stream = fmemopen(buffer, sizeof(char)*sz, "wb+");

// while((readed_sz = fread(mem_stream, sizeof(char), BUFF_SIZE_3, fd)) != 0){
//     fwrite(mem_stream, sizeof(char), readed_sz, fd2);
//   }

//   fclose(fd);
//   fclose(fd2);
//   free(buffer);
//   fclose(mem_stream);

// // // ////////////////////////////////////////////////////
// //   buffer = malloc(sizeof(char) * BUFF_SIZE_5);
// //   fd = fopen("source2", "r+"); // read from this file
// //   fd2 = fopen("output5", "w+");// read to this file
// //   mem_stream = fmemopen(buffer, BUFF_SIZE_5, "w+");

// //   while(fread(mem_stream, sizeof(char), BUFF_SIZE_5, fd) != 0){
// //     fwrite(mem_stream, sizeof(char), BUFF_SIZE_5, fd2);
// //   }
// //   fclose(fd);
// //   fclose(fd2);
// //   free(buffer);
// //   free(mem_stream);
// // ////////////////////////////////////////////////////
// //   // fd = fopen("source2", "r+"); // read from this file
// //   // fd2 = fopen("output6", "w+");// read to this file

  return 0;
}