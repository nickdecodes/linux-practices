/*************************************************************************
	> File Name: 04.process_sem.c
	> Author: 
	> Mail: 
	> Created Time: 日  7/25 11:17:38 2021
	> 使用信号量进程间通信
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>

typedef int sem_t;
 
/* 建立信号量, 魔数key和信号量的初始值value */
sem_t CreateSem(key_t key, int value) {
	union semun sem; // 信号量结构变量
	sem_t semid; // 信号量ID
	sem.val = value; // 设置初始值
	semid = semget(key, 0, IPC_CREAT|0666); // 获得信号量的ID
	/* 获得信号量ID失败 */
	if (-1 == semid) {
		printf("create semaphore error\n"); // 打印信息
		return -1;
	}

	semctl(semid, 0, SETVAL, sem);
	return semid;
}

/* 增加信号量 */ 
int Sem_P(sem_t semid) {
	struct sembuf sops = {0, +1, IPC_NOWAIT}; // 建立信号量结构值
    return (semop(semid, &sops, 1)); // 发送命令
}

/* 减小信号量值 */
int Sem_V(sem_t semid) {
    struct sembuf sops={0, -1, IPC_NOWAIT}; // 建立信号量结构值
    return (semop(semid, &sops, 1)); // 发送信号量操作方法
}

/* 设置信号量的值 */
void SetvalueSem(sem_t semid, int value) {
    union semun sem; // 信号量操作的结构
    sem.val = value; // 值初始化
    semctl(semid, 0, SETVAL, sem); // 设置信号量的值
}

/* 获得信号量的值 */
int GetvalueSem(sem_t semid) {
    union semun sem; // 信号量操作的结构
    return semctl(semid, 0, GETVAL, sem); // 获得信号量的值
}

/* 销毁信号量 */
void DestroySem(sem_t semid) {
	union semun sem; // 信号量操作的结构
	sem.val = 0; // 信号量值的初始化
	semctl(semid, 0, IPC_RMID, sem); // 设置信号量
}

int main() {
	key_t key;
	int semid;
	char i;
	int value = 0;
	key = ftok("/tmp/sem", 'a');
	semid = CreateSem(key, 100);

	for (i = 0; i <= 3; i++) {
		Sem_P(semid);
		Sem_V(semid);
	}
	value = GetvalueSem(semid);
	printf("信号量值为:%d\n", value);

	DestroySem(semid);
	return 0;
}