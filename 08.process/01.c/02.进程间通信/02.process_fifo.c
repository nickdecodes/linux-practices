/*************************************************************************
	> File Name: 02.process_fifo.c
	> Author: 
	> Mail: 
	> Created Time: 日  7/25 11:14:34 2021
	> 使用命名管道进程间通信
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "fifo"
#define K 1024
#define WRITELEN (128 * K)

int main() {
	int result = -1; // 创建管道结果
	int fifo_fd, nbytes; // 文件描述符,字符个数

	/* PID值 */
	pid_t pid; 
	char string[WRITELEN] = "你好,管道";
	char readbuffer[10 * K]; // 读缓冲区

	/* 先删除之前可能遗留的管道文件，然后再次创建它 */
	unlink(FIFO_NAME);
	result = mkfifo(FIFO_NAME, 0777);
	/* 建立管道文件失败 */
	if (-1 == result) {
		printf("建立管道文件失败\n"); // 打印信息
		return -1; // 返回错误结果
	}
	/* 分叉程序 */
	pid = fork();
	if (-1 == pid) {
		printf("fork 进程失败\n"); // 打印信息
		return -1; // 返回错误结果
	}
	/* 子进程 */
	if (0 == pid) {
    	int write_size = WRITELEN; // 写入的长度
    	result = 0; // 结果
		/* 以只写的方式打开管道文件 */
		fifo_fd = open(FIFO_NAME, O_WRONLY);
		/* 如果没有将数据写入继续操作 */
		while (write_size >= 0) {
			result = write(fifo_fd, string, write_size); // 写入管道数据
			/* 写入成功 */
			if (result > 0) {
				write_size -= result; /*写入的长度*/
				printf("写入%d个数据, 剩余%d个数据\n", result, write_size);
			} else { // 写入失败
				sleep(10); // 等待 10s,读端将数据读出
			} 
		}
		close(fifo_fd);
		unlink(FIFO_NAME);
		return 0; 
	} else { // 父进程
		/* 以只写的方式打开管道文件 */
		fifo_fd = open(FIFO_NAME, O_RDONLY);
		/* 一直读取数据 */
		while (1) {
			nbytes = read(fifo_fd, readbuffer, sizeof(readbuffer)); // 读取数据
			/* 读取失败 */
			if (nbytes <= 0)  {
				printf("没有数据写入了\n"); // 打印信息
				break; // 退出循环 
			}
			printf("接收到%d个数据, 内容为:%s\n", nbytes, readbuffer); 
		}
		close(fifo_fd);
		unlink(FIFO_NAME);
	}

	return 0; 
}



