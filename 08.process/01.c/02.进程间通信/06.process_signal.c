/*************************************************************************
	> File Name: 06.process_signal.c
	> Author: 
	> Mail: 
	> Created Time: 日  7/25 11:18:41 2021
	> 使用信号进程间通信
 ************************************************************************/

#include <stdio.h>
#include <signal.h>

typedef void (*sighandler_t)(int);

/* 信号处理函数 */
static void sig_handle(int signo) {
	if (SIGSTOP == signo) {
		/* 为SIGSTOP信号 */
		printf("接收到信号 SIGSTOP\n"); // 打印信息
	} else if (SIGKILL == signo) {
		/* 为 SIGKILL 信号 */
		printf("接收到信号 SIGKILL\n"); // 打印信息
	} else {
		/* 其他信号 */
		printf("接收到信号:%d\n", signo); // 打印信息
	} 
	return ;
}

int main() {
    sighandler_t ret;
	ret = signal(SIGSTOP, sig_handle); // 挂接SIGSTOP信号处理函数 
	if (SIG_ERR == ret) {
		/* 挂接失败 */
		printf("为 SIGSTOP 挂接信号处理函数失败\n");
		return -1;
	}

	ret = signal(SIGKILL, sig_handle); // 挂接 SIGKILL 处理函数
	if (SIG_ERR == ret) {
		/* 挂接失败 */
		printf("为 SIGKILL 挂接信号处理函数失败\n");
		return -1;
	}
	/* 等待程序退出 */
	for (;;); 
	return 0;
}

