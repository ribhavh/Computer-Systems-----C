


#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

/* Starts the program and
 * checks the command prompt argument
 * and functions accordingly. 
 */
int main(int argc, char* argv[]) {
    if (argc != 3 || (strcmp(argv[1], "-u") && strcmp(argv[1], "-i"))) {
        printf("Usage: <signal type> <pid>\n");
        exit(1);
    }
    if (!strcmp(argv[1], "-u")) {
        if (kill(atoi(argv[2]), SIGUSR1) == -1) {
            printf("Error - Could not send SIGUSR1\n");
            exit(1);
        }
    }
    
    if (!strcmp(argv[1], "-i")) {
        if (kill(atoi(argv[2]), SIGINT) == -1) {
            printf("Error - Could not send SIGINT\n");
            exit(1);
        }
    }
}
