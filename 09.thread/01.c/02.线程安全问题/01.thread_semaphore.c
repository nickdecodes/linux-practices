/*************************************************************************
	> File Name: 01.thread_semaphore.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:12:55 2021
    > 用信号量进行同步
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <semaphore.h>

// #define LENGTH 100

// sem_t bin_sem;
// char work_area[LENGTH]; // 存放输入内容

// void *thread_routine(void *arg) {
//     // 等待信号量有大于0的值然后退出
//     sem_wait(&bin_sem);
//     while (0 != strncmp("end", work_area, 3)) {
//         printf("Input %ld characters\n", strlen(work_area) - 1);
//     }
//     return NULL;
// }

// int main() {
//     printf("start exec!\n");

//     int ret; // 存放命令的返回值
//     pthread_t tid; // 创建线程
//     void *thread_result; // 存放线程处理结果

//     // 初始化信号量，并设置初始值为0
//     ret = sem_init(&bin_sem, 0, 0);
//     if (0 != ret) {
//         perror("Semaphore initialization failes");
//         exit(EXIT_FAILURE);
//     }

//     // 创建新线程 0
//     ret = pthread_create(&tid, NULL, thread_routine, NULL);
//     if (0 != ret)
//     {
//         perror("Thread creation failed");
//         exit(EXIT_FAILURE);
//     }
//     printf("Enter 'end' to finish\n");

//     // 当工作区内不是以end开头的字符串，则继续输入
//     while (0 != strncmp("end", work_area, 3))
//     {
//         // 以标准输入获取输入到工作区内
//         fgets(work_area, LENGTH, stdin);
//         sem_post(&bin_sem);  // 信号量+1
//     }
//     printf("\n Waiting for thread to finish...\n");

//     // 等待线程结束
//     ret = pthread_join(tid, &thread_result);
//     if (0 != ret)
//     {
//         perror("Thread join failed");
//         exit(EXIT_FAILURE);
//     }

//     printf("Thread joined\n");
//     sem_destroy(&bin_sem);  // 销毁信号量
//     exit(EXIT_SUCCESS);

//     // 等各个线程推出后，进程才结束
//     pthread_exit(NULL);

//     return 0;
// }

sem_t sem;
int running = 1;

/* 生产者处理程序代码 */
void *producter_f(void *arg) {
    int semval = 0; // 信号量的初始值为 0
    /* 运行状态为可运行 */
    while (running) {
        usleep(1); // 等待
        sem_post(&sem); // 信号量增加
        sem_getvalue(&sem, &semval); // 获得信号量的值
        printf("生产,总数量:%d\n", semval); // 打印信息
    }
    return NULL;
}

/* 消费者处理程序代码 */
void *consumer_f(void *arg) {
    int semval = 0; // 信号量的初始值为 0
    while (running) {
        usleep(1); // 等待
        sem_wait(&sem); // 信号量增加
        sem_getvalue(&sem, &semval); // 获得信号量的值
        printf("消费,总数量:%d\n", semval); // 打印信息
    }
    return NULL;
}

int main() {
    pthread_t consumer_t; // 消费者线程参数
    pthread_t producter_t; // 生产者线程参数

    sem_init(&sem, 0, 16); // 信号量初始化

    pthread_create(&producter_t, NULL, (void*)producter_f, NULL ); // 建立生产者线程
    pthread_create(&consumer_t, NULL, (void *)consumer_f, NULL); // 建立消费者线程

    sleep(1); // 等待
    running = 0; // 设置线程退出
    pthread_join(consumer_t,NULL); // 等待消费者线程退出
    pthread_join(producter_t,NULL); // 等待生产者线程退出
    sem_destroy(&sem); // 销毁信号量

    return 0;
}