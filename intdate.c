

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>
#include <string.h>

static int seconds = 3;  // Number of seconds between signals
static int caught = 0;  // Number of times SIGUSR1 was caught

/* Handles the SIGALRM
 */
void handler_SIGALRM()
{
    time_t curtime;
    time(&curtime);
    if (time(&curtime) == ((time_t) -1)) {
        printf("time() resulted in an error");
        exit(1);
    }
    
    if (ctime(&curtime) == NULL) {
        printf("ctime() resulted in an error");
        exit(1);
    }
    printf("PID: %d | Current Time: %s", getpid(), ctime(&curtime));
    
    alarm(seconds);
}

/* Handles the SIGUSR1 signal
 */
void handler_SIGUSR1()
{
    caught++;
    printf("SIGUSR1 caught\n");
}

/* Handles the SIGINT signal
 */
void handler_SIGINT()
{
    printf("\nSIGINT received.\n");
    printf("SIGUSR1 was received %d times. Exiting now.\n", caught);
    exit(0);
}

/* Starts the program
 * giving specific details.
 */
int main()
{
    printf("Pid and time will be printed every 3 seconds.\n");
    printf("Enter ^C to end the program.\n");
    struct sigaction sa;  // SIGALRM sigaction
    memset (&sa, 0, sizeof(sa));
    sa.sa_handler = handler_SIGALRM;
    if (sigaction(SIGALRM, &sa, NULL) != 0) {
        printf("Failed to bind handler\n");
        exit(1);
    }
    alarm(seconds);
    struct sigaction sp;  // SIGUSR1 sigaction
    memset(&sp, 0, sizeof(sp));
    sp.sa_handler = handler_SIGUSR1;
    if (sigaction(SIGUSR1, &sp, NULL) != 0) {
        printf("Failed to bind handler\n");
        exit(1);
    }
    struct sigaction si;  // SIGINT sigaction
    memset(&si, 0, sizeof(si));
    si.sa_handler = handler_SIGINT;
    if (sigaction(SIGINT, &si, NULL) != 0){
        printf("Failed to bind handler\n");
        exit(1);
    }
    while (1) {
    }
}
