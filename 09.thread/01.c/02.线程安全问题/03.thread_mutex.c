/*************************************************************************
	> File Name: 03.thread_mutex.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:13:59 2021
    > 用互斥锁进行同步
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <sched.h>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>
 
// #define LENGTH 3 // 自增计算次数
// #define NUM_THREADS 10 // 设置线程的长度
 
// int count = 1; // 在数据段共享资源，多个进程抢占临界资源
// // 对于临界资源，应该添加互斥锁
// pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
 
// void *thread_routine(void *arg) {
//     int tid = *((int *)arg);
//     int val;
//     printf("thread_id : %d \n",tid);
 
//     for (int i = 0; i < LENGTH; i++) {
//         pthread_mutex_lock(&mutex);
//         val = count;
//         printf("val = %d \n",val++);
//         count = val;
//         pthread_mutex_unlock(&mutex);
//     }
 
//     return NULL;
// }
 
// int main() {
//     int ret; // 存放命令的返回值
//     pthread_t tids[NUM_THREADS]; // 创建线程
//     int index[NUM_THREADS];
 
//     for (int i = 0; i < NUM_THREADS; i++) {
//         index[i] = i;
//         // 创建线程
//         ret = pthread_create(&tids[i], NULL, thread_routine, (void *)&index[i]);
//         if (0 != ret) {
//            printf("Error: 创建线程失败！\n");
//            exit(-1);
//         }
//     }
 
//     for (int i = 0; i < NUM_THREADS; i++) {
//         // 汇合线程
//         pthread_join(tids[i], NULL);
//     }
//     printf("count = %d\n",count);
//     pthread_exit(NULL);
//     return 0;
// }
 
// 在运行此程序无互斥锁时，我们不仅得到错误的答案，而且每次得到的答案都不相同
// 分析
// 当多个对等线程在一个处理器上并发运行时，机器指令以某种顺序完成，每个并发执行定义了线程中指令的某种顺序


/*************************************************************************
    > 用互斥信号量进行同步
 ************************************************************************/

int buffer_has_item =0; // 缓冲区计数值
pthread_mutex_t mutex; // 互斥区
int running = 1; // 线程运行控制

/* 生产者线程程序 */
void *producter_f(void *arg) {
    while (running) {
        pthread_mutex_lock (&mutex); // 进入互斥区 
        buffer_has_item++; // 增加计数值
        printf("生产,总数量:%d\n", buffer_has_item); // 打印信息
        pthread_mutex_unlock(&mutex); // 离开互斥区
    }
    return NULL; 
}

void *consumer_f(void *arg) {
    while (running) {
        pthread_mutex_lock(&mutex); // 进入互斥区 
        buffer_has_item--; // 减少s计数值
        printf("消费,总数量:%d\n", buffer_has_item); // 打印信息
        pthread_mutex_unlock(&mutex); // 离开互斥区
    }
    return NULL;
}


int main() {
    pthread_t consumer_t;
    pthread_t producter_t;
    pthread_mutex_init(&mutex, NULL);
    pthread_create(&producter_t, NULL, (void*)producter_f, NULL); // 建立生产者线程
    pthread_create(&consumer_t, NULL, (void *)consumer_f, NULL); // 建立消费者线程
    usleep(1); // 等待,线程创建完毕
    running = 0; // 设置线程退出值

    pthread_join(consumer_t, NULL);
    pthread_join(producter_t, NULL);
    pthread_mutex_destroy(&mutex);

    return 0; 
}