/*************************************************************************
	> File Name: 02.thread_condition.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 23:13:22 2021
	> 用条件变量进行同步 创建两个线程一个wait print,一个signal sleep()
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>             
 
pthread_cond_t cond;
pthread_mutex_t mutex;
 
void *thread_wait(void *arg) {
  	while (1) {
		pthread_cond_wait(&cond, &mutex);
		printf("running!\n");
  	}
	return NULL;
}

void *thread_signal(void *arg) {
	while (1) {
		sleep(1);
		pthread_cond_signal(&cond);
	}
}
 
int main() {
	pthread_t tid1, tid2;
	pthread_cond_init(&cond, NULL);
	pthread_mutex_init(&mutex, NULL);
	
	pthread_create(&tid1, NULL, thread_wait, NULL);
	pthread_create(&tid2, NULL, thread_signal, NULL);
	
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	
	pthread_cond_destroy(&cond);
	pthread_mutex_destroy(&mutex);
	return 0;
}



