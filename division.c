

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

static int counter = 0;  // Number of successful times

/* Handles the SIGFPE signal
 */
void handler_SIGFPE() {
    printf("Error: a division by 0 operation was attempted.\n");
    printf("Total number of operations completed successfully: ");
    printf("%d\nThe program will be terminated.\n", counter);
    exit(0);
}

/* Handles the SIGINT signal
 */
void handler_SIGINT() {
    printf("\nTotal number of operations completed successfully: ");
    printf("%d\nThe program will be terminated.\n", counter);
    exit(0);
}

/* Starts the program and asks user for input
 * and gives the remainer. Continues till SIGINT
 * is caught. 
 */
int main(int argc, char* argv[]) {
    char buf[100];  // Characters entered by user
    struct sigaction sa;  // SIGFPE sigaction
    memset (&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGFPE;
    if (sigaction(SIGFPE, &sa, NULL) != 0) {
        printf("Error with SIGFPE handler\n");
        exit(1);
    }
    struct sigaction sb;  // SIGINT sigaction
    memset (&sb, 0, sizeof(sb));
    sb.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &sb, NULL) != 0) {
        printf("Error with SIGINT handler\n");
        exit(1);
    }
    while (1) {
        printf("Enter first integer: ");
        fgets(buf, 100, stdin);
        int first = atoi(buf);
        printf("Enter second integer: ");
        fgets(buf, 100, stdin);
        int second = atoi(buf);
        printf("%d / %d is %d with a ", first, second, first/second);
        printf("remainder of %d\n", first%second);
        counter++;
    }
}
