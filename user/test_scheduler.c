#include "kernel/types.h"
#include "user/user.h"

const int MAX_N_PROC = 1 << 5;
const int MAX_TICKETS = 1 << 10;

int main(int argc, char **argv) {
    if (argc < 4) {
        printf("Usage: %s [SLEEP_TIME in ms] [N_PROC] [TICKET1] [TICKET2]...\n", argv[0]);
        exit(-1);
    }
    int sleep_time = atoi(argv[1]);
    int n_proc = atoi(argv[2]);
    if (n_proc > MAX_N_PROC) {
        printf("Error: Maximum number of processes is %d (%d received)\n", MAX_N_PROC, n_proc);
        exit(-1);
    }
    int tickets[MAX_N_PROC];
    for (int i = 0; i < n_proc; i++) {
        tickets[i] = atoi(argv[i + 3]);
        if (tickets[i] < 1 || tickets[i] > MAX_TICKETS) {
            printf("Error: Ticket value must be between 1 and %d (%d received)\n", MAX_TICKETS, tickets[i]);
            exit(-1);
        }
    }

    int *childs = malloc(n_proc * sizeof(int));
    for (int i = 0; i < n_proc; ++i) {
        int pid = fork();
        if (pid == 0) {
            // Child process
            settickets(tickets[i]);
            while (1) ; // Infinite loop to keep the child process running
        } else if (pid > 0) {
            // Parent process
            childs[i] = pid;
            printf("Created child process with PID: %d and tickets: %d\n", pid, tickets[i]);
        } else {
            printf("Error: Fork failed\n");
            exit(-1);
        }
    }
    sleep(sleep_time);
    for (int i = 0; i < n_proc; ++i) {
        printf("Child PID: %d, ticks spent: %d\n", childs[i], getticks(childs[i]));
        kill(childs[i]);
    }
    return 0;
}