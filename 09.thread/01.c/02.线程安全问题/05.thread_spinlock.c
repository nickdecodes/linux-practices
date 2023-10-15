/*************************************************************************
	> File Name: 05.thread_spinlock.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:15:56 2021
	> 使用自旋锁进行同步
 ************************************************************************/

#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/timeb.h>
 
static int num = 0;
static int count = 10000000;
static pthread_spinlock_t spin;
 
void Perror(const char *s) {
    perror(s);
    exit(EXIT_FAILURE);
}
 
long long getSystemTime() {
    struct timeb t;
    ftime(&t);
    return 1000 * t.time + t.millitm;
}
 
void *fun2(void *arg) {
    pthread_t thread_id = pthread_self();
    printf("the thread2 id is %ld\n", (long)thread_id);
    int i = 1;
    for (; i <= count; ++i) {
        pthread_spin_lock(&spin);
        num += 1;
        pthread_spin_unlock(&spin);
    }
}
 
int main() {
    int err;
    pthread_t thread1;
    pthread_t thread2;
 
    pthread_spin_init(&spin, PTHREAD_PROCESS_PRIVATE);
 
    thread1 = pthread_self();
    printf("the thread1 id is %ld\n", (long)thread1);
 
    long long start = getSystemTime();
 
    // Create thread
    err = pthread_create(&thread2, NULL, fun2, NULL);
    if (err != 0) {
        Perror("can't create thread2\n");
    }
 
    int i = 1;
    for (; i <= count; ++i) {
        pthread_spin_lock(&spin);
        num += 1;
        pthread_spin_unlock(&spin);
    }
 
    pthread_join(thread2, NULL);
    long long end = getSystemTime();
 
    printf("The num is %d, pay %lld ms\n", num, (end-start));
    pthread_spin_destroy(&spin);
    return 0;
}

