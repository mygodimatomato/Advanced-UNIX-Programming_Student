#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h> 

void find_and_print_links(const char *path) {
  DIR *dir;
  struct dirent *entry;

  if ((dir = opendir(path)) == NULL) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }

    char full_path[512];
    snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

    struct stat statbuf;
    if (lstat(full_path, &statbuf) == -1) {
      perror("lstat");
      continue;
    }

    if (S_ISLNK(statbuf.st_mode)) {
      char link_target[512];
      ssize_t len = readlink(full_path, link_target, sizeof(link_target) - 1);
      if (len != -1) {
        link_target[len] = '\0';
        printf("Symbolic link: %s -> %s\n", full_path, link_target);
      } else {
        perror("readlink");
      }
    }

    if (S_ISDIR(statbuf.st_mode)) {
      find_and_print_links(full_path);
    }
  
  }
}

int main(int argc, char *argv[])  {
  if (argc != 2) {
    fprintf(stderr, "You must provide exactly one argument for the given path\n");
    return 1;
  }
  find_and_print_links(argv[1]);
  return 0;
}