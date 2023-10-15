/*************************************************************************
	> File Name: 04.thred_join_detach.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:11:57 2021
    > 基于线程的并发编程, 连接或分离线程
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

void *thread_routine(void *arg) {
    int tid = *((int *)arg);
    printf("Hello, World of Thread in C, ThreadId: %d\n",tid);
    sleep(1);
    return NULL;
}

int main() {
    printf("start exec!\n");

    // 定义线程的id变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    int index[NUM_THREADS];
    void *status;

    // 定义线程属性
    pthread_attr_t attr;

    // 初始化并设置线程为可连接
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < NUM_THREADS; i++) {
        // 参数依次是： 创建的线程id，线程参数，调用的函数，传入的函数参数
        index[i] = i;
        int ret = pthread_create(&tids[i], NULL, thread_routine, (void *)&index[i]);
        if (ret != 0) {
            printf("pthread_create error: ret = %d\n", ret);
            exit(-1);
        }
    }

    // 删除属性，并等待其他线程
    pthread_attr_destroy(&attr);
    for (int j = 0; j < NUM_THREADS; j++) {
        int ret = pthread_join(tids[j], status);
        if (0 != ret) {
            printf("unable to join thread: %d, ret: %d\n", j, ret);
            exit(-1);
        }
        printf("complete thread id : %d", j);
        printf(" exiting with status: %p\n", status);
    }
 
    printf("program exiting.\n");

    // 等各个线程推出后，进程才结束
    pthread_exit(NULL);

    return 0;
}