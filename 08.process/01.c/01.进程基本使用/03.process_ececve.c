/*************************************************************************
	> File Name: 03.process_ececve.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 22:48:07 2021
	> ececve创建进程
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	char *args[] = {"/bin/ls", NULL};
	printf("系统分配的进程号是: %d\n", getpid()); 
	if (execve("/bin/ls", args, NULL) < 0) {
		printf("创建进程出错!\n"); 
	}
	return 0;
}

