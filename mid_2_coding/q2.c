#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

void find_and_print_links(const char *path) {
    DIR *dir;
    struct dirent *entry;
    struct stat statbuf;
    char link_target[512];

    // Open the directory
    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        return;
    }

    // Read entries in the directory
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".."
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // Construct full path
        char full_path[512];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        // Get file status
        if (lstat(full_path, &statbuf) == -1) {
            perror("lstat");
            continue;
        }

        // Check if it's a symbolic link
        if (S_ISLNK(statbuf.st_mode)) {
            ssize_t len = readlink(full_path, link_target, sizeof(link_target) - 1);
            if (len != -1) {
                link_target[len] = '\0'; // Null-terminate the link target
                printf("Symbolic link: %s -> %s\n", full_path, link_target);
            } else {
                perror("readlink");
            }
        }

        // If it's a directory, recursively search it
        if (S_ISDIR(statbuf.st_mode)) {
            find_and_print_links(full_path);
        }
    }

    // Close the directory
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    find_and_print_links(argv[1]);

    return EXIT_SUCCESS;
}
