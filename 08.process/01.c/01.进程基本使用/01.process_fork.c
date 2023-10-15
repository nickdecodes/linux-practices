/*************************************************************************
	> File Name: 01.process_fork.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 22:32:58 2021
	> fork方式创建进程
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	pid_t pid;
	/* 分叉进程 */
	pid = fork();
	/* 判断是否执行成功 */
	if (-1 == pid) {
		printf("进程创建失败!\n");
		return -1;
	} else if (0 == pid) {
		/* 子进程中执行此段代码 */ 
		printf("子进程, fork返回值:%d, ID:%d, 父进程ID:%d\n", pid, getpid(), getppid());
	} else {
		/* 父进程中执行此段代码 */
		printf("父进程, fork返回值:%d, ID:%d, 父进程ID:%d\n", pid, getpid(), getppid());
	}
	return 0;
}