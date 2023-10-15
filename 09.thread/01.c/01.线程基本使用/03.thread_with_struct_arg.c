/*************************************************************************
	> File Name: 03.thread_with_struct_arg.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:11:26 2021
	> 基于线程的并发编程,向线程传递参数(传递结构体)
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

#define NUM_THREADS 10

typedef struct thread_data{
    int thread_id;
    char message;
} THDATA, *PTHDATA;

void *thread_routine(void *arg) {
    PTHDATA tid = (PTHDATA)arg;
    printf("This is Pthread : %d; info : %c \n",tid->thread_id, tid->message);
    sleep(1);
    return NULL;
}

int main() {
    printf("start exec!\n");

    // 定义线程的id变量，多个变量使用数组
    pthread_t tids[NUM_THREADS];
    // 构造线程数据
    THDATA index[NUM_THREADS];

    for (int i = 0; i < NUM_THREADS; i++) {
        index[i].thread_id = i;
        index[i].message = 'A' + i % 10;
        // 参数依次是： 创建的线程id，线程参数，调用的函数，传入的函数参数
        int ret = pthread_create(&tids[i], NULL, thread_routine, (void *)&index[i]);
        if (ret != 0) {
            printf("pthread_create error: ret = %d\n", ret);
            exit(-1);
        }
    }

    // 等各个线程推出后，进程才结束
    pthread_exit(NULL);

    return 0;
}