# 呈现数据

- [理解输入和输出](#理解输入和输出)
    - [标准文件描述符](#标准文件描述符)
    - [重定向错误](#重定向错误)
- [在脚本中重定向输出](#在脚本中重定向输出)
    - [临时重定向](#临时重定向)
    - [永久重定向](#永久重定向)
- [在脚本中重定向输入](#在脚本中重定向输入)
- [创建自己的重定向](#创建自己的重定向)
    - [创建输出文件描述符](#创建输出文件描述符)
    - [重定向文件描述符](#重定向文件描述符)
    - [创建输入文件描述符](#创建输入文件描述符)
    - [创建读/写文件描述符](#创建读/写文件描述符)
    - [关闭文件描述符](#关闭文件描述符)
- [列出打开的文件描述符](#列出打开的文件描述符)
- [抑制命令输出](#抑制命令输出)
- [使用临时文件](#使用临时文件)
- [记录消息](#记录消息)
- [实战](#记录消息)
- [小结](#小结)

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)


## 理解输入和输出

两种显示脚本输出的方法。

- 在显示器屏幕上显示输出。
- 将输出重定向到文件中。

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 标准文件描述符

| 文件描述符 | 缩写   | 描述     |
| ---------- | ------ | -------- |
| 0          | STDIN  | 标准输入 |
| 1          | STDOUT | 标准输出 |
| 2          | STDERR | 标准错误 |

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 重定向错误

重定向错误消息和正常输出

```bash
ls -al test test2 test3 badtest 2> test6 1> test7
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 在脚本中重定向输出

在脚本中重定向输出的方法有两种。

- 临时重定向每一行。
- 永久重定向脚本中的所有命令。

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 临时重定向

在重定向到文件描述符时，必须在文件 描述符索引值之前加一个`&`

```bash
#!/bin/bash
# testing STDERR messages
 
echo "This is an error" >&2
echo "This is normal output"
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 永久重定向

如果脚本中有大量数据需要重定向，那么逐条重定向所有的 echo 语句会很烦琐。这时可以 用 exec 命令，它会告诉 shell 在脚本执行期间重定向某个特定文件描述符

```bash
#!/bin/bash
# redirecting output to different locations
 
exec 2>testerror
 
echo "This is the start of the script"
echo "now redirecting all output to another location"
 
exec 1>testout
 
echo "This output should go to the testout file"
echo "but this should go to the testerror file" >&2
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 在脚本中重定向输入

可以使用与重定向 STDOUT 和 STDERR 相同的方法，将 STDIN 从键盘重定向到其他位置。 在 Linux 系统中，exec 命令允许将 STDIN 重定向为文件

```bash
#!/bin/bash
# redirecting file input
 
exec 0< testfile
count=1
 
while read line
do
   echo "Line #$count: $line"
   count=$[ $count + 1 ]
done
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 创建自己的重定向

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 创建输出文件描述符

可以用 exec 命令分配用于输出的文件描述符。和标准的文件描述符一样，一旦将替代性文 件描述符指向文件，此重定向就会一直有效，直至重新分配

```bash
#!/bin/bash
# using an alternative file descriptor
 
exec 3>test13out
 
echo "This should display on the monitor"
echo "and this should be stored in the file" >&3
echo "Then this should be back on the monitor"
```

> 这里说明一下:在重定向时，如果使用大于 9 的文件描述符，那么一定要小心，因为有可能会与 shell 内部使用的 文件描述符发生冲突。

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 重定向文件描述符

有一个技巧能帮助你恢复已重定向的文件描述符。你可以将另一个文件描述符分配给标准 文件描述符，反之亦可。这意味着可以将 STDOUT 的原先位置重定向到另一个文件描述符，然 后再利用该文件描述符恢复 STDOUT。

```bash
#!/bin/bash
# storing STDOUT, then coming back to it
 
exec 3>&1
exec 1>test14out
 
echo "This should store in the output file"
echo "along with this line."
 
exec 1>&3
 
echo "Now things should be back to normal"
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 创建输入文件描述符

可以采用和重定向输出文件描述符同样的办法来重定向输入文件描述符。在重定向到文件之 前，先将 STDIN 指向的位置保存到另一个文件描述符，然后在读取完文件之后将 STDIN 恢复到 原先的位置

```bash
#!/bin/bash
# redirecting input file descriptors
 
exec 6<&0
 
exec 0< testfile
 
count=1
while read line
do
   echo "Line #$count: $line"
   count=$[ $count + 1 ]
done
exec 0<&6
read -p "Are you done now? " answer
case $answer in
Y|y) echo "Goodbye";;
N|n) echo "Sorry, this is the end.";;
esac
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 创建读/写文件描述符

尽管看起来可能很奇怪，但你也可以打开单个文件描述符兼做输入和输出，这样就能用同一 个文件描述符对文件进行读和写两种操作了

> 但使用这种方法时要特别小心。由于这是对一个文件进行读和写两种操作，因此 shell 会维 护一个内部指针，指明该文件的当前位置。任何读或写都会从文件指针上次的位置开始。如果粗 心的话，这会产生一些令人瞠目的结果。

```bash
#!/bin/bash
# testing input/output file descriptor
 
exec 3<> testfile
read line <&3
echo "Read: $line"
echo "This is a test line" >&3
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

### 关闭文件描述符

如果创建了新的输入文件描述符或输出文件描述符，那么 shell 会在脚本退出时自动将其关 闭。然而在一些情况下，需要在脚本结束前手动关闭文件描述符。

要关闭文件描述符，只需将其重定向到特殊符号`&-`即可。

```bash
#!/bin/bash
# testing closing file descriptors
 
exec 3> test17file
echo "This is a test line of data" >&3
exec 3>&-
 
cat test17file
 
exec 3> test17file
echo "This’ll be bad" >&3
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 列出打开的文件描述符

```bash
$ /usr/sbin/lsof -a -p $$ -d 0,1,2
COMMAND  PID USER   FD   TYPE DEVICE SIZE NODE NAME
bash    3344 rich    0u   CHR  136,0	2 /dev/pts/0
bash    3344 rich    1u   CHR  136,0	2 /dev/pts/0
bash    3344 rich    2u   CHR  136,0	2 /dev/pts/0
```

| 列      | 描述                                                         |
| ------- | ------------------------------------------------------------ |
| COMMAND | 进程对应的命令名的前 9 个字符                                |
| PID     | 进程的 PID                                                   |
| USER    | 进程属主的登录名                                             |
| FD      | 文件描述符编号以及访问类型(r 代表读，w 代表写，u 代表读/写)  |
| TYPE    | 文件的类型(CHR 代表字符型，BLK 代表块型，DIR 代表目录，REG 代表常规文件) |
| DEVICE  | 设备号(主设备号和从设备号)                                   |
| SIZE    | 如果有的话，表示文件的大小                                   |
| NODE    | 本地文件的节点号                                             |
| NAME    | 文件名                                                       |

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 抑制命令输出

有时候，你可能不想显示脚本输出。将脚本作为后台进程运行时这很常见(参见第 16 章)。 如果在后台运行的脚本出现错误消息，那么 shell 就会将其通过邮件发送给进程属主。这会很麻烦，尤其是当运行的脚本生成很多烦琐的小错误时。

要解决这个问题，可以将 STDERR 重定向到一个名为 null 文件的特殊文件。跟它的名字很像，null 文件里什么都没有。shell 输出到 null 文件的任何数据都不会被保存，全部会被丢弃。

在 Linux 系统中，null 文件的标准位置是/dev/null。重定向到该位置的任何数据都会被丢弃，不再显示

```bash
ls -al > /dev/null
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 使用临时文件

Linux 系统有一个专供临时文件使用的特殊目录/tmp，其中存放那些不需要永久保留的文件。 大多数 Linux 发行版配置系统在启动时会自动删除/tmp 目录的所有文件。

系统中的任何用户都有权限读写/tmp 目录中的文件。这个特性提供了一种创建临时文件的简 单方法，而且还无须担心清理工作。

甚至还有一个专门用于创建临时文件的命令 mktemp，该命令可以直接在/tmp 目录中创建唯 一的临时文件。所创建的临时文件不使用默认的 umask 值(参见第 7 章)。作为临时文件属主， 你拥有该文件的读写权限，但其他用户无法访问(当然，root 用户除外)。

创建本地临时文件

在默认情况下，mktemp 会在本地目录中创建一个文件。在使用 mktemp 命令时，只需指定 一个文件名模板即可。模板可以包含任意文本字符，同时在文件名末尾要加上 6 个`x`

```bash
mktemp testing.XXXXXX
```

在/tmp 目录中创建临时文件

`-t` 选项会强制 mktemp 命令在系统的临时目录中创建文件。在使用这个特性时，mktemp 命令会返回所创建的临时文件的完整路径名，而不只是文件名

```bash
mktemp -t test.XXXXXX
```

创建临时目录

`-d` 选项会告诉 mktemp 命令创建一个临时目录。你可以根据需要使用该目录，比如在其中 创建其他的临时文件

```bash
#!/bin/bash
# using a temporary directory
 
tempdir=$(mktemp -d dir.XXXXXX)
cd $tempdir
tempfile1=$(mktemp temp.XXXXXX)
tempfile2=$(mktemp temp.XXXXXX)
exec 7> $tempfile1
exec 8> $tempfile2
 
echo "Sending data to directory $tempdir"
echo "This is a test line of data for $tempfile1" >&7
echo "This is a test line of data for $tempfile2" >&8
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 记录消息

有时候，也确实需要将输出同时送往显示器和文件。与其对输出进行两次重定向，不如改用 特殊的 tee 命令。

`tee` 命令就像是连接管道的 T 型接头，它能将来自 STDIN 的数据同时送往两处。一处是 21 STDOUT，另一处是 tee 命令行所指定的文件名

```bash
#!/bin/bash
# using the tee command for logging
 
tempfile=test22file
 
echo "This is the start of the test" | tee $tempfile
echo "This is the second line of the test" | tee -a $tempfile
echo "This is the end of the test" | tee -a $tempfile
```

如果想将数据追加到指定文件中，就必须使用`-a` 选项

> 注意，在默认情况下，tee 命令会在每次 使用时覆盖指定文件的原先内容

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 实战

无论是将文件读入脚本，还是将数据从脚本输出到文件，都会用到文件重定向，这是一种很 常见的操作。本节中的示例脚本两种功能皆有。它会读取 CSV 格式的数据文件，输出 SQL INSERT 语句，并将数据插入数据库。

shell 脚本使用命令行参数指定待读取的 CSV 文件。CSV 格式用于从电子表格中导出数据， 你可以把这些数据库数据放入电子表格，将电子表格保存为 CSV 格式，读取文件，然后创建 INSERT 语句将数据插入 MySQL 数据库。

```bash
#!/bin/bash
# read file and create INSERT statements for MySQL

outfile=‘members.sql’
IFS=‘,’
while read lname fname address city state zip
do
   cat >> $outfile << EOF
   INSERT INTO members (lname,fname,address,city,state,zip) VALUES (‘$lname’, ‘$fname’, ‘$address’, ‘$city’, ‘$state’, ‘$zip’);
EOF
done < ${1}
```

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)

## 小结

在创建脚本时，能够理解 bash shell 如何处理输入和输出会带来很多方便。你可以改变脚本 获取数据和显示数据的方式，对脚本进行定制以适应各种环境。脚本的输入/输出都可以从标准 输入(STDIN)/标准输出(STDOUT)重定向到系统中的任意文件。

除了 STDOUT，你可以通过重定向 STDERR 来改变错误消息的流向。这是通过重定向与 STDERR 关联的文件描述符(文件描述符 2)来实现的。你可以将 STDERR 和 STDOUT 重定向到 同一个文件，也可以重定向到不同的文件，以此区分脚本的正常输出和错误消息。

bash shell 允许在脚本中创建自己的文件描述符。你可以创建文件描述符 3 到 8，将其分配给 要用到的任何输出文件。一旦创建了文件描述符，就可以利用标准的重定向符号将任意命令的输 出重定向到那里。

bashshell也允许重定向输入，这样就能方便地将文件数据读入脚本。你可以用lsof命令来 显示 shell 中所使用的文件描述符。

Linux 系统提供了一个特殊文件`/dev/null`，用于重定向无用的输出。Linux 系统会丢弃重定向 到/dev/null 的任何数据。你也可以通过将`/dev/null` 的内容重定向到文件来清空该文件的内容。

`mktemp` 命令很有用，它可以直接创建临时文件和目录。只需给 `mktemp` 命令指定一个模板， 它就能在每次调用时基于该文件模板的格式创建一个唯一的文件。你也可以在 Linux 系统的/tmp 目录中创建临时文件和目录，系统启动时会清空这个特殊位置中的内容。

`tee` 命令便于将输出同时发送给标准输出和日志文件。这样你就可以在屏幕上显示脚本消息 的同时，将其保存在日志文件中。

---
下一篇：[练习6 脚本控制](../practice-06)，上一篇：[练习4 处理用户输入](../practice-04/)，[目录](#呈现数据)｜[首页](../README.md)
