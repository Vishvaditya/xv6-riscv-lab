// Sample program to run custom system call

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(){
    printf("Testing custom system call\n");
    info(0);
    // printf("--1. Number of processes running --\n");
    // printf("---------%d---------\n", info(1));
    printf("--2. Number of system calls by the current process --\n");
    printf("---------%d---------\n", info(2));
    for(int i = 0; i < 5; i++)
    {
    write(1, ".", 1);
    }
  
    printf("\nSystem call count after writes: %d\n", info(2));
    exit(0);
}