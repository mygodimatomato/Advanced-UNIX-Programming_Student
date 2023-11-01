#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
  pid_t pid, pgrp, tpgid;

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

    // Fetch and display process IDs
    pid = getpid();
    pgrp = getpgrp();
    tpgid = tcgetpgrp(STDIN_FILENO);

    printf("        PID          PGRP         TPGID\n");
    printf("%10d %10d %10d\n", pid, pgrp, tpgid);

    // Infinite loop to keep the process running, allowing you to run `ps`
    while(1) {
      sleep(1);
    }
  } else { // Parent process
    // Do nothing, parent can terminate or also run forever based on your requirement
  }

  return 0;
}