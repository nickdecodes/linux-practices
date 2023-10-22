# 脚本控制

- [处理信号](#处理信号)
- [重温Linux信号](#重温Linux信号)
- [产生信号](#产生信号)
- [捕获信号](#捕获信号)
- [捕获脚本退出](#捕获脚本退出)
- [修改或移除信号捕获](#修改或移除信号捕获)
- [以后台模式运行脚本](#以后台模式运行脚本)
- [在非控制台下运行脚本](#在非控制台下运行脚本)
- [作业控制](#作业控制)
- [调整谦让度](#调整谦让度)
- [实战](#实战)
- [小结](#小结)

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 处理信号

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

### 重温Linux信号

| 信号 | 值      | 描述                            |
| ---- | ------- | ------------------------------- |
| 1    | SIGHUP  | 挂起(hang up)进程               |
| 2    | SIGINT  | 中断(interrupt)进程             |
| 3    | SIGQUIT | 停止(stop)进程                  |
| 9    | SIGKILL | 无条件终止(terminate)进程       |
| 15   | SIGTERM | 尽可能终止进程                  |
| 18   | SIGCONT | 继续运行停止的进程              |
| 19   | SIGSTOP | 无条件停止，但不终止进程        |
| 20   | SIGTSTP | 停止或暂停(pause)，但不终止进程 |

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

### 产生信号

中断进程`Ctrl+C`

暂停进程`Ctrl+Z`

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

### 捕获信号

你也可以用其他命令在信号出现时将其捕获，而不是忽略信号。trap 命令可以指定 shell 脚本需要侦测并拦截的 Linux 信号。如果脚本收到了 trap 命令中列出的信号，则该信号不再由 shell 处理，而是由本地处理。

trap 命令的格式如下: `trap commands signals`

```bash
#!/bin/bash
#Testing signal trapping

trap "echo ' Sorry! I have trapped Ctrl-C'" SIGINT
echo This is a test script.

count=1
while [ $count -le 5 ]
do
     echo "Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done

echo "This is the end of test script."
exit
```

> 如果脚本中的命令被信号中断，使用带有指定命令的 trap 未必能让被中断的命令继续 14 执行。为了保证脚本中的关键操作不被打断，请使用带有空操作命令的 trap 以及要捕
>
> 获的信号列表，例如:
>
> trap "" SIGINT
>
> 这种形式的 trap 命令允许脚本完全忽略 SIGINT 信号，继续执行重要的工作。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

### 捕获脚本退出

要捕获 shell 脚本的退出，只需在 trap 命令后加上 EXIT 信号即可

```bash
#!/bin/bash
#Testing exit trapping

trap "echo Goodbye..." EXIT
count=1
while [ $count -le 5 ]
do
     echo "Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done
exit
```

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

### 修改或移除信号捕获

要想在脚本中的不同位置进行不同的信号捕获处理，只需重新使用带有新选项的 trap 命令 即可

```bash
#!/bin/bash
# Modifying a set trap 

trap "echo ' Sorry...Ctrl-C is trapped.'" SIGINT
count=1
while [ $count -le 3 ]
do
     echo "Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done

trap "echo ' I have modified the trap!'" SIGINT
count=1
while [ $count -le 3 ]
do
     echo "Second Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done
exit
```

> 如果在交互式 shell 会话中使用 trap 命令，可以使用 trap -p 查看被捕获的信号。如果 什么都没有显示，则说明 shell 会话按照默认方式处理信号。

也可以移除已设置好的信号捕获。在 trap 命令与希望恢复默认行为的信号列表之间加上两 个连字符即可。

```bash
#!/bin/bash
#Removing a set trap 

trap "echo ' Sorry...Ctrl-C is trapped.'" SIGINT
count=1
while [ $count -le 3 ]
do
     echo "Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done

trap -- SIGINT
echo "The trap is now removed."
count=1
while [ $count -le 3 ]
do
     echo "Second Loop #$count"
     sleep 1
     count=$[ $count + 1 ]
done
exit
```

> 也可以在 trap 命令后使用单连字符来恢复信号的默认行为。单连字符和双连字符的效 果一样。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 以后台模式运行脚本

使用 `ps -e` 命令，可以看到 Linux 系统中运行的多个进程

- 后台运行脚本

以后台模式运行 shell 脚本非常简单，只需在脚本名后面加上&即可

- 运行多个后台作业

```bash
testAscript.sh &
testAscript.sh &
testAscript.sh &
```

> 本章先前提到过，当要退出终端会话时，如果还有被停止的进程，就会出现警告信息。 14 但如果是后台进程，则只有部分终端仿真器会在退出终端会话前提醒你尚有后台作业在运行。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 在非控制台下运行脚本

有时候，即便退出了终端会话，你也想在终端会话中启动 shell 脚本，让脚本一直以后台模 式运行到结束。这可以用 nohup 命令来实现。

nohup 命令能阻断发给特定进程的 SIGHUP 信号。当退出终端会话时，这可以避免进程退出。 

nohup 命令的格式如下:  `nohup command`

```bash
nohup ./testAscript.sh &
```

nohup 命令会自动将 STDOUT 和 STDERR 产生的消息重定 向到一个名为 nohup.out 的文件中。

> nohup.out 文件一般在当前工作目录中创建，否则会在$HOME 目录中创建。
>
> 如果使用 nohop 运行了另一个命令，那么该命令的输出会被追加到已有的 nohup.out 文件 中。当运行位于同一目录中的多个命令时，一定要当心，因为所有的命令输出都会发送 到同一个 nohup.out 文件中，结果会让人摸不着头脑。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 作业控制

 `kil`l 命令可以“杀死”该作业。 要重启停止的进程

**查看作业**

`jobs` 是作业控制中的关键命令

| 选项 | 描述                                          |
| ---- | --------------------------------------------- |
| -l   | 列出进程的 PID 以及作业号                     |
| -n   | 只列出上次 shell 发出通知后状态发生改变的作业 |
| -p   | 只列出作业的 PID                              |
| -r   | 只列出运行中的作业                            |
| -s   | 只列出已停止的作业                            |

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 调整谦让度

在多任务操作系统(比如 Linux)中，内核负责为每个运行的进程分配 CPU 时间。调度优先 级[也称为谦让度(nice value)]是指内核为进程分配的 CPU 时间(相对于其他进程)。在 Linux 系统中，由 shell 启动的所有进程的调度优先级默认都是相同的。

调度优先级是一个整数值，取值范围从-20(最高优先级)到+19(最低优先级)。在默认情 况下，bash shell 以优先级 0 来启动所有进程。

> -20(最低值)代表最高优先级，+19(最高值)代表最低优先级，这很容易记混。只要 记住那句俗话“好人难做。”(Nice guys finish last.)即可。越是“谦让”(nice)或是值越 大，获得 CPU 的机会就越低。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 实战

展示一个实用脚本，其中综合运用了本章介绍的部分脚本控制命令:捕获脚本信号，
然后将其置于后台运行。这个脚本最适合辅助那些需要在运行时避免被中断的脚本。

```bash
#!/bin/bash
# Set specified signal traps; then run script in background

####################### Check Signals to Trap #######################

while getopts S: opt   #Signals to trap listed with -S option
do
     case "$opt" in 
          S) # Found the -S option
             signalList="" #Set signalList to null
             for arg in $OPTARG
             do
                  case $arg in
                  1)   #SIGHUP signal is handled
                       signalList=$signalList"SIGHUP "
                  ;;
                  2)   #SIGINT signal is handled
                       signalList=$signalList"SIGINT "
                  ;;
                  20)  #SIGTSTP signal is handled
                       signalList=$signalList"SIGTSTP "
                  ;;
                  *)   #Unknown or unhandled signal
                       echo "Only signals 1 2 and/or 20 are allowed."
                       echo "Exiting script..."
                       exit
                  ;;
                  esac
             done
             ;;
          *) echo 'Usage: -S "Signal(s)" script-to-run-name'
             echo 'Exiting script...'
             exit
             ;;
     esac
done

####################### Check Script to Run #######################

shift $[ $OPTIND - 1 ] #Script name should be in parameter
if [ -z $@ ]
then
     echo
     echo 'Error: Script name not provided.'
     echo 'Usage: -S "Signal(s)"  script-to-run-name'
     echo 'Exiting script...'
     exit 
elif [ -O $@ ] && [ -x $@ ]
then
     scriptToRun=$@
     scriptOutput="$@.out"
else
     echo 
     echo "Error: $@ is either not owned by you or not excecutable."
     echo "Exiting..."
     exit
fi 

######################### Trap and Run ###########################

echo
echo "Running the $scriptToRun script in background"
echo "while trapping signal(s): $signalList"
echo "Output of script sent to: $scriptOutput"
echo
trap "" $signalList  #Ignore these signals
source $scriptToRun > $scriptOutput &  #Run script in background

trap -- $signalList  #Set to default behavior

####################### Exit script #######################
exit
```

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)

## 小结

Linux 系统允许使用信号来控制 shell 脚本。bash shell 可以接收信号并将其传给由 shell 进程 生成的所有进程。Linux 信号可以轻而易举地“杀死”失控的进程或暂停耗时的进程。

你可以在脚本中用 trap 语句捕获信号并执行特定命令。这个功能提供了一种简单的方法来 控制在脚本运行时用户能否将其中断。

在默认情况下，当在终端会话 shell 中运行脚本时，交互式 shell 会被挂起，直到脚本运行完毕。你可以在命令名后加一个&符号使脚本或命令以后台模式运行。当在后台模式运行命令或脚 本时，交互式 shell 会被返回，允许你继续输入其他命令。

通过这种方法运行的后台进程仍与终端会话绑定。如果退出终端会话，那么后台进程也会随之退出。`nohup` 命令可以阻止这种情况发生。该命令可以拦截任何会导致命令停止运行的信号

(比如退出终端会话的信号)。如此一来，即便已经退出了终端会话，脚本也能继续在后台运行。 当你将进程置入后台时，仍然可以对其施加控制。jobs 命令可以查看 shell 会话启动的进程。

只要知道后台进程的作业号，就能用 kill 命令向该进程发送信号，或是用 `fg` 命令将该进程带回 shell 会话的前台。你可以用 `Ctrl+Z` 组合键挂起正在运行的前台进程，然后用 `bg` 命令将其置 入后台模式。

`nice` 命令和 `renice` 命令可以调整进程的优先级。通过降低进程的优先级，可以使其他高优先级进程获得更多的 CPU 时间。当运行消耗大量 CPU 时间的长期进程时，这项特性非常方便。

除了控制处于运行状态的进程，你还可以决定何时启动进程。无须直接在命令行界面运行脚本，你可以将进程安排在指定时间运行。实现方法不止一种。`at` 命令允许在预设的时间运行脚 本。`cron` 程序提供了定期运行脚本的接口，anacron 可以确保及时运行脚本。

最后，Linux 系统提供了一些脚本文件，可以让脚本在启动新的 bash shell 时运行。与此类似， 位于用户主目录中的启动文件(比如.bashrc)提供了一个位置，以存放新 shell 启动时需要运行脚本和命令。

---
下一篇：[练习7 创建函数](../practice-07/)，上一篇：[练习5 呈现数据](../practice-05/)，[目录](#脚本控制)｜[首页](../README.md)