#include <stdio.h>
#include <unistd.h>

void daemonize(const char *);

int main() {
    daemonize("logs");
    printf("running main");
    char* login = getlogin();
    FILE* fl = fopen("assignment11.txt","w");
    if(fl) {
        fprintf(fl,"Login name: %s",login);
    } else puts("Error opening assignment11.txt");
    return 0;
}
