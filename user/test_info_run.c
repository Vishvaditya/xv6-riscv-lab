// Sample program to run custom system call

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(){
    printf("Testing custom system call\n");
    info(0);
    printf("--1. Number of processes running --\n");
    printf("---------%d---------\n", info(1));
    exit(0);
}