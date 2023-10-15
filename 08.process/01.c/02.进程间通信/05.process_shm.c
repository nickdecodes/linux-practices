/*************************************************************************
	> File Name: 05.process_shm.c
	> Author: 
	> Mail: 
	> Created Time: 日  7/25 11:18:19 2021
	> 使用共享内存进程间通信
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <sys/shm.h> 
#include <sys/ipc.h> 
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/msg.h>
#include <unistd.h>

static char msg[] = "你好,共享内存\n";
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

int main(void) {
	key_t key;
	int semid, shmid;
	char i, *shms, *shmc;
	struct semid_ds buf;
	int value = 0;
	char buffer[80];
	pid_t pid;
	key = ftok("/ipc/sem", 'a'); // 生成键值
	shmid = shmget(key, 1024, IPC_CREAT|0604); // 获得共享内存,大小为 1024 个字节
	semid = CreateSem(key, 0); // 建立信号量
	pid = fork(); // 分叉程序

	if (pid > 0) {
		/* 父进程 */
    	shms = (char *)shmat(shmid, 0, 0); // 挂接共享内存
    	memcpy(shms, msg, strlen(msg) + 1); // 复制内容
		sleep(10); // 等待 10s,另一个进程将数据读出
		Sem_P(semid); // 获得共享内存的信号量
		shmdt(shms); // 摘除共享内存
		DestroySem(semid); // 销毁信号量
	} else if (pid == 0) {
		/* 子进程 */
		shmc = (char *)shmat(shmid, 0, 0); // 挂接共享内存
		Sem_V(semid); // 减小信号量
		printf("共享内存的值为:%s\n",shmc); // 打印信息
		shmdt(shmc); // 摘除共享内存
	}
	return 0;
}

