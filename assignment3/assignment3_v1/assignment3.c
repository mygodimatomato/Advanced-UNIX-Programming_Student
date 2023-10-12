#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 100

typedef struct {
  char *data;
  size_t size;
  size_t position;
} mem_file_t;

// Read function for funopen
int mem_read(void *cookie, char *buf, int size) {
  mem_file_t *mem_file = (mem_file_t *)cookie;

  // If the size of the read is bigger than the size of the file, read the rest of the whole file
  if (mem_file->position + size > mem_file->size) {
    size = mem_file->size - mem_file->position;
  }

  for (int i = 0; i < size; i++){
    buf[i] = mem_file->data[mem_file->position + i];
  }
  mem_file->position += size;
  return size;
}

// Write function for funopen
int mem_write(void *cookie, const char *buf, int size) {
  mem_file_t *mem_file = (mem_file_t *)cookie;

  // there is no space left for writing
  if (mem_file->position + size > mem_file->size) {
    printf("%d, %d\n", (int)mem_file->position + size, (int)mem_file->size);
    return -1;
  }
  // memcpy(mem_file->data + mem_file->position, buf, size);

  for (int i = 0; i < size; i++){
    mem_file->data[mem_file->position + i] = buf[i];
  }
  mem_file->position += size;

  // printf("Finish Writing to the file\n");
  // printf("%s", (char *)mem_file->data);
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

  printf("Closing the file\n");
  free(cookie);

  return 0;
}

// done
FILE *fmemopen(void *buf, size_t size, const char *mode){
  mem_file_t *mem_file = malloc(sizeof(mem_file_t));
  mem_file->data = buf;
  mem_file->size = size;
  mem_file->position = 0;

  if (mode == NULL) {
    free(mem_file);
    return NULL;
  }

  // checking for the mode
  if (mode[1] == '+') {
    if (mode[0] == 'a') {
      while (mem_file->position < mem_file->size){
        mem_file->position++;
      }
      return funopen(mem_file, mem_read, mem_write, mem_seek, mem_close);
    } else if (mode[0] == 'w' || mode[0] == 'r'){
      return funopen(mem_file, mem_read, mem_write, mem_seek, mem_close);
    } else {
      return NULL;
    }
  } else {
    switch (mode[0]){
      case 'r':
        return funopen(mem_file, mem_read, NULL, mem_seek, mem_close);
        break;
      case 'w':
        return funopen(mem_file, NULL, mem_write, mem_seek, mem_close);
        break;
      case 'a':    
        while (mem_file->position < mem_file->size){
          mem_file->position++;
        }
        return funopen(mem_file, NULL, mem_write, mem_seek, mem_close);
        break;
      default:
        free(mem_file);
        return NULL;
        break;
    }
  }
  return funopen(mem_file, mem_read, mem_write, mem_seek, mem_close);
}

int main() {
  // expected execution : Write -> Seek -> Read -> ( Seek -> Read ) -> Close
  char *buffer = malloc(sizeof(char) * BUFF_SIZE);
  char output_buffer[BUFF_SIZE] = {0};

  FILE *mem_stream = fmemopen(buffer, BUFF_SIZE, "w+"); // in this case, the mode is not really working, we didn't use it
  /*
    r      The stream is opened for reading.

    w      The stream is opened for writing.

    a      Append; open the stream for writing, with the initial
          buffer position set to the first null byte.

    r+     Open the stream for reading and writing.

    w+     Open the stream for reading and writing.  The buffer
          contents are truncated (i.e., '\0' is placed in the first
          byte of the buffer).

    a+     Append; open the stream for reading and writing, with the
          initial buffer position set to the first null byte.

  */

  mem_file_t *tmp = (mem_file_t *)mem_stream->_cookie;
  // printf("%d\n", (int)tmp->size);

  int out = mem_write(mem_stream->_cookie, "hello, world\n", 13);
  // printf("Write %d bytes\n", out);

  mem_seek(mem_stream->_cookie, 7, SEEK_SET);

  mem_read(mem_stream->_cookie, output_buffer, 5);
  printf("%s\n", output_buffer);

  mem_seek(mem_stream->_cookie, 0, SEEK_SET);

  mem_read(mem_stream->_cookie, output_buffer, 13);
  printf("%s", output_buffer);

  free(mem_stream->_cookie);
  return 0;
}

/*
funopen(const  void  *cookie, 
        int    (*readfn)(void  *,  char  *,	 int),
        int	   (*writefn)(void     *,     const	char	 *,	 int),
        fpos_t (*seekfn)(void *, fpos_t, int), 
        int    (*closefn)(void *));
*/