/*************************************************************************
	> File Name: 02.process.system.c
	> Author: 
	> Mail: 
	> Created Time: 六  7/24 22:44:30 2021
	> system方式创建进程
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
	int ret;
	printf("系统分配的进程号是:%d\n", getpid());
	ret = system("ping www.baidu.com -c 2");
	printf("返回值为:%d\n", ret);
	return 0;
}
