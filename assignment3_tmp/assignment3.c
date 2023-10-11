#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 100

typedef struct {
  char *data;
  size_t size;
  size_t position;
  const char *mode;
} mem_file_t;

// Read function for funopen
int mem_read(void *cookie, char *buf, int size) {
  mem_file_t *mem_file = (mem_file_t *)cookie;

  // Todo : Check if the file is opened in read mode
  
  // If the size of the read is bigger than the size of the file, read the rest of the whole file
  if (mem_file->position + size > mem_file->size) {
    size = mem_file->size - mem_file->position;
  }
  memcpy(buf, mem_file->data + mem_file->position, size);
  mem_file->position += size;
  return size;
}

// Write function for funopen
int mem_write(void *cookie, const char *buf, int size) {
  mem_file_t *mem_file = (mem_file_t *)cookie;

  // Todo : Check if the file is opened in write mode

  // there is no space left for writing
  if (mem_file->position + size > mem_file->size) {
    return -1;
  }
  memcpy(mem_file->data + mem_file->position, buf, size);
  mem_file->position += size;
  return size;
}

// Seek function for funopen
fpos_t mem_seek(void *cookie, fpos_t offset, int whence){
  mem_file_t *mem_file = (mem_file_t *)cookie;

  switch (whence) {
    case SEEK_SET:
      mem_file->position = offset;
      break;
    case SEEK_CUR:
      mem_file->position += offset;
      break;
    case SEEK_END:
      mem_file->position = mem_file->size + offset;
      break;
    default:
      return -1;
  }

  return mem_file->position;
}

// Close function for funopen
int mem_close(void *cookie){
  if (cookie == NULL)
    return -1;
  free(cookie);

  return 0;
}

// done
FILE *fmemopen(void *buf, size_t size, const char *mode){
  mem_file_t *mem_file = malloc(sizeof(mem_file_t));
  mem_file->data = buf;
  mem_file->size = size;
  mem_file->position = 0;
  mem_file->mode = mode;

  return funopen(mem_file, mem_read, mem_write, mem_seek, mem_close);
}

int main() {

  // expected execution : Write -> Seek -> Read -> ( Seek -> Read ) -> Close
  char buffer[BUFF_SIZE] = {0};

  FILE *mem_stream = fmemopen(buffer, sizeof(buffer), "w+"); // not sure if we only need w+
  
  mem_write(mem_stream, "hello world\n", 12);

  mem_seek(mem_stream, 7, SEEK_SET);

  mem_read(mem_stream, buffer, 5);
  printf("%s\n", buffer);

  mem_seek(mem_stream, 0, SEEK_SET);

  mem_read(mem_stream, buffer, 12);
  printf("%s\n", buffer);

  mem_close(mem_stream);
  return 0;
}

/*
funopen(const  void  *cookie, 
        int    (*readfn)(void  *,  char  *,	 int),
        int	   (*writefn)(void     *,     const	char	 *,	 int),
        fpos_t (*seekfn)(void *, fpos_t, int), 
        int    (*closefn)(void *));
*/