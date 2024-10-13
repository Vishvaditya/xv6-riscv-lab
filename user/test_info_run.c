// Sample program to run custom system call

#include "kernel/types.h"
#include "kernel/stat.h"
#include "user.h"

int main(){
    printf('Testing custom system call\n');
    info(0);
    info(1);
    exit(0);
}