# 01.进程基本使用

## 01.fork()创建进程

fork()函数以父进程为蓝本复制一 个进程，其 ID 号和父进程 ID 号不同。在 Linux 环境下，fork()是以写复制实现的，只有内存等与父进程不同，其它与父进程共享，只有在父进程或者子进程进行了修改后，才重新生成一份。

fork()函数的原型如下，当成功时，fork()函数的返回值是进程的 ID;失败则返回–1。

```c
#include <sys/types.h>
#include <unistd.h>
pid_t fork(void);
```

fork()的特点是执行一次，返回两次。在父进程和子进程中返回的是不同的值，父进程 中返回的是子进程的 ID 号，而子进程中则返回 0。

## 02.system创建进程

system()函数调用 shell 的外部命令在当前进程中开始另一个进程。

system()函数调用“/bin/sh–c command”执行特定的命令，阻塞当前进程直到 command 命令执行完毕。system()函数的原型如下:

```c
#include <stdlib.h>
int system(const char *command);
```

执行 system()函数时，会调用 fork()、execve()、waitpid()等函数，其中任意一个调用失败，将导致 system()函数调用失败。system()函数的返回值如下:

- 失败，返回–1 
- 当 sh 不能执行时，返回 127; 
- 成功，返回进程状态值。

## 03.ececev创建进程

在使用 fork()函数和 system()函数的时候，系统中都会建立一个新的进程，执行调用者的操作，而原来的进程还会存在，直到用户显式地退出；而exec()族的函数与之前的 fork() 和 system()函数不同，exec()族函数会用新进程代替原有的进程，系统会从新的进程运行， 新进程的 PID 值会与原来进程的 PID 值相同。

exec()族函数共有 6 个，其原型如下:

```c
#include <unistd.h>
extern char **environ;
int execl(const char *path, const char *arg, ...);
int execlp(const char *file, const char *arg, ...);
int execle(const char *path, const char *arg, ..., char * const envp[]); int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
```

上述 6 个函数中，只有 execve()函数是真正意义上的系统调用，其他 5 个函数都是在此基础上经过包装的库函数。上述的 exec()函数族的作用是，在当前系统的可执行路径中根据指定的文件名来找到合适的可执行文件名，并用它来取代调用进程的内容，即在原来的进程内部运行一个可执行文件。上述的可执行文件既可以是二进制的文件，也可以是可执行的脚本文件。

与 fork()函数不同，exec()函数族的函数执行成功后不会返回，这是因为执行的新程序已经占用了当前进程的空间和资源，这些资源包括代码段、数据段和堆栈等，它们都已经被新的内容取代，而进程的 ID 等标识性的信息仍然是原来的东西，即 exec()函数族在原来进程的壳上运行了自己的程序，只有程序调用失败了，系统才会返回-1。

使用 exec()函数比较普遍的一种方法是先使用 fork()函数分叉进程，然后在新的进程中 调用 exec()函数，这样 exec()函数会占用与原来一样的系统资源来运行。

Linux 系统针对上述过程专门进行了优化。由于 fork()的过程是对原有系统进行复制， 然后建立子进程，这些过程都比较耗费时间。如果在 fork()系统调用之后进行 exec()系统调用，系统就不会进行系统复制，而是直接使用 exec()指定的参数来覆盖原有的进程。上述的方法在 Linux 系统上叫做“写时复制”，即只有在造成系统的内容发生更改的时候才进行进程的真正更新。