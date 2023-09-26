#include <stdio.h>
#include <stdlib.h>
#define BUFFER_SIZE 4096

void copy_file(const char *source, const char *destination) {
  FILE *src_file = fopen(source, "rb");
  FILE *dest_file = fopen(destination, "wb");
  if (src_file == NULL || dest_file == NULL) {
    printf("Error: Unable to open file.\n");
    exit(1);
  }

  char buffer[BUFFER_SIZE];
  size_t bytes_read;
  while ((bytes_read = fread(buffer, sizeof(char), BUFFER_SIZE, src_file)) > 0) {
    fwrite(buffer, 1, bytes_read, dest_file);
  }

  fclose(src_file);
  fclose(dest_file);
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    printf("Usage: %s <source> <destination>\n", argv[0]);
    return 1;
  }

  copy_file(argv[1], argv[2]);
  return 0;
}