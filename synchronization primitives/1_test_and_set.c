#include<stdio.h>
#include<stdatomic.h>

atomic_flag lock = ATOMIC_FLAG_INIT;

void acquire_lock(atomic_flag *l){
    while (atomic_flag_test_and_set(l) == 1); //spin until lock is acquired
}

void release_lock(atomic_flag *l){
    atomic_flag_clear(l); //release the lock
}

