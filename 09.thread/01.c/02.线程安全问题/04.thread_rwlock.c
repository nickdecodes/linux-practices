/*************************************************************************
	> File Name: 04.thread_rwlock.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:15:43 2021
	> 用读写锁进行同步 创建8个线程，3个写线程，5个读线程
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>                

#define NUM 8
pthread_rwlock_t rwlock;
int counter = 0;
 
void *read_routine(void *arg) {
	int id = *(int *)arg;
	free(arg);
	while (1) {
		pthread_rwlock_rdlock(&rwlock);
		printf("read thread %d : %d\n", id, counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(100000);
	}
}
 
void *write_routine(void *arg) {
	int id = *(int *)arg;
	free(arg);
	while (1) {
		int t = counter;
		pthread_rwlock_wrlock(&rwlock);
		printf("write thread %d : t= %d, %d\n", id, t, ++counter);
		pthread_rwlock_unlock(&rwlock);
		usleep(100000);
	}
}

int main() {
    pthread_t tids[NUM];
    pthread_rwlock_init(&rwlock, NULL);
    int i = 0;
    for (i = 0; i < 3; i++) {
		int *p =(int *)malloc(sizeof(int));
		*p = i;
		pthread_create(&tids[i], NULL, write_routine, (void*)p);
    }

    for (i = 0; i < 5; i++) {
		int *p = (int *)malloc(sizeof(int));
		*p = i;
		pthread_create(&tids[3 + i], NULL, read_routine, (void*)p);
    }
 
    for (i = 0; i < NUM; i++) {
      	pthread_join(tids[i], NULL);
    }
 
    pthread_rwlock_destroy(&rwlock);
 
    return 0;
}



