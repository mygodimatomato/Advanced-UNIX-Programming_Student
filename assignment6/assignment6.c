#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main(void) {
  pid_t child_pid;
  char command[256];

  // Fork a child process
  child_pid = fork();

  if (child_pid == 0) {
    // Child process : immediately exit to become a zombie
    printf("Child process is terminating...\n");
    _exit(0);
  } else {
    // Parent process
    printf("Parent process is sleeping...\n");
    sleep(10); // Sleep to ensure child process terminates first

    // Use ps(1) command within the program to check for zombie processes
    sprintf(command, "ps -o pid,state -p %d", child_pid);
    FILE *ps_output = popen(command, "r");
    if (ps_output == NULL) {
      perror("popen failed");
      exit(EXIT_FAILURE);
    }

    // Read the output of the ps(1) command
    char buf[1024];
    while (fgets(buf, sizeof(buf), ps_output) != NULL) {
      // Check if the process state is 'Z' for zombie
      if (strstr(buf, " Z ")) {
        printf("Zombie process found: %s", buf);
        // This is where we verify that the child is a zombie process
      }
    }

    // Close the ps command pipe
    pclose(ps_output);

    // Parent does some work
    printf("Parent process is doing some work...\n");

    // Clean up the zombie by waiting for the child process to change state
    waitpid(child_pid, NULL, 0);

    printf("Parent process has cleaned up the zombie.\n"); 
  }

  return 0;
}