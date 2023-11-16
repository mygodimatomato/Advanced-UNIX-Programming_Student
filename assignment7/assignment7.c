#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid, pgrp, tpgid;
  char command[256];

  // Fork a new child
  pid = fork();

  if (pid < 0) {
    perror("fork failed");
    exit(1);
  }

  if (pid == 0) { // Child process
    // Create a new session
    if (setsid() < 0) {
      perror("setsid failed");
      exit(1);
    }

    // Infinite loop to keep the process running, allowing you to run `ps`
    while(1) {
      sleep(1);
    }
  } else { // Parent process
   
    // Use ps(1) command within the program to get info.
    sprintf(command, "ps -o pid -o pgid=PGRP -o tpgid -p %d", pid);
    FILE *ps_output = popen(command, "r");
    if (ps_output == NULL) {
      perror("popen failed");
      exit(EXIT_FAILURE);
    }

    // print the output of the ps(1) command
    char buf[1024];
    while (fgets(buf, sizeof(buf), ps_output) != NULL) {
      printf("%s",buf);
    }

    // Close the ps command pipe
    pclose(ps_output);
  }

  return 0;
}
