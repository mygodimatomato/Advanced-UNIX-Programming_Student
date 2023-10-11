#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  char *data;
  size_t size;
  size_t position;
  const char *mode;
} memfile_t;

// Read function for funopen
int memread(void *cookie, char *buf, int size) {
  memfile_t *memfile = (memfile_t *)cookie;

  // Todo : Check if the file is opened in read mode
  
  // If the size of the read is bigger than the size of the file, read the rest of the whole file
  if (memfile->position + size > memfile->size) {
    size = memfile->size - memfile->position;
  }
  memcpy(buf, memfile->data + memfile->position, size);
  memfile->position += size;
  return size;
}

// Write function for funopen
int memwrite(void *cookie, const char *buf, int size) {
  memfile_t *memfile = (memfile_t *)cookie;

  // Todo : Check if the file is opened in write mode

  // there is no space left for writing
  if (memfile->position + size > memfile->size) {
    return -1;
  }
  memcpy(memfile->data + memfile->position, buf, size);
  memfile->position += size;
  return size;
}

// Seek function for funopen
fpos_t memseek(void *cookie, fpos_t offset, int whence){
  memfile_t *memfile = (memfile_t *)cookie;

  switch (whence) {
    case SEEK_SET:
      memfile->position = offset;
      break;
    case SEEK_CUR:
      memfile->position += offset;
      break;
    case SEEK_END:
      memfile->position = memfile->size + offset;
      break;
    default:
      return -1;
  }

  return memfile->position;
}

// Close function for funopen
int memclose(void *cookie){
  if (cookie == NULL)
    return -1;
  free(cookie);

  return 0;
}

// done
FILE *fmemopen(void *buf, size_t size, const char *mode){
  memfile_t *memfile = malloc(sizeof(memfile_t));
  memfile->data = buf;
  memfile->size = size;
  memfile->position = 0;
  memfile->mode = mode;

  return funopen(memfile, memread, memwrite, memseek, memclose);
}

int main() {

  // expected execution : Write -> Seek -> Read -> ( Seek -> Read ) -> Close
  char buffer[100] = {0};

  FILE *memstream = fmemopen(buffer, sizeof(buffer), "w+");
  memseek(memstream, 7, SEEK_SET);


  return 0;
}

/*
funopen(const  void  *cookie, 
        int    (*readfn)(void  *,  char  *,	 int),
        int	   (*writefn)(void     *,     const	char	 *,	 int),
        fpos_t (*seekfn)(void *, fpos_t, int), 
        int    (*closefn)(void *));
*/