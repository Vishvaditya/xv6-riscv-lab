#include "user/thread.h"
#include "user/user.h"
#include "kernel/riscv.h"

/**
 * Create a new thread.
 * 
 * 1. Allocate a new user stack for the new thread 
 * and move the stack base to proper point (how does the stack grow in xv6?).
 * 2. Call `clone()` system call.
 * 3. return.
 * 
 * TODO:
 * @param start_routine The function to be executed by the new thread.
 * @param arg The argument to be passed to the new thread.
 * @return 0 on success, -1 on failure.
 * 
 */
int thread_create(void *(*start_routine)(void*), void *arg) {
    void *stack = malloc(2*PGSIZE);
    // printf("Initialized Stack\n");
    
    int thread_id;

    // printf("Calling Clone Function \n");
    thread_id = clone((void *)stack);
    printf("THREAD ID: %d", thread_id);
    if(thread_id != 0) {
        return 0;
    }
    start_routine(arg);
    free(stack);
    exit(0);
    return thread_id;
}


// For lock implementation, you can refer to kernel/spinlock.c.
/**
 * Initialize a lock.
 * 
 * TODO:
 * @param lk The lock to be initialized.
 */
void lock_init(struct lock_t* lk) {
    lk->locked = 0;             // Mark the lock as initially unlocked
}

/**
 * Acquire a lock.
 * 
 * TODO:
 * @param lk The lock to be acquired.
 */
void lock_acquire(struct lock_t* lk) {
    while (__sync_lock_test_and_set(&lk->locked, 1)!=0) {
        // Busy-wait until the lock becomes available
    }
    __sync_synchronize();

}

/**
 * Release a lock.
 * 
 * TODO:
 * @param lk The lock to be released.
 */
void lock_release(struct lock_t* lk) {
    __sync_lock_release(&lk->locked);
}