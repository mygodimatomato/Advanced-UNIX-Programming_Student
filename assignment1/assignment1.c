#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main() {
  int fd = open("sample.txt", O_WRONLY); // Open file with read-write permissions
  // int fd = open("sample.txt", O_APPEND); // Open file with append permissions
  if (fd == -1) {
    perror("Failed to open file");
    return 1;
  }

  char buffer[9];
  lseek(fd, 14, SEEK_SET);
  read(fd, buffer, 8);
  printf("%s\n", buffer);

  // Write "NTHU student."
  lseek(fd, 14, SEEK_SET);
  write(fd, "NTHU student.", 13); // Adding NTHU student.

  // Read and print the whole file
  char finalBuffer[30];
  lseek(fd, 0, SEEK_SET);
  read(fd, finalBuffer, 30);
  printf("%s\n", finalBuffer);

  // close(fd); // Close the file descriptor
  return 0;
}
