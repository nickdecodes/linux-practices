# 构建基础脚本

- [使用多个命令](#使用多个命令)
- [创建shell脚本文件](#创建shell脚本文件)
- [显示消息](#显示消息)
- [使用变量](#使用变量)
- [命令替换](#命令替换)
- [重定向输入和输出](#重定向输入和输出)
- [管道](#管道)
- [执行数学运算](#执行数学运算)
- [退出脚本](#退出脚本)
- [实战](#实战)
- [小结](#小结)

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 使用多个命令

如果想让两个命令一起运行，可以将其放在同一行中，彼此用分号隔开

```bash
date ; who
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 创建shell脚本文件

在创建 shell 脚本文件时，必须在文件的第一行指定要使用的 shell，格式如下:

```bash
#!/bin/bash 
```

> #后面的惊叹号会告诉 shell 用哪个 shell 来运行脚本
>
> 在指明了 shell 之后，可以在文件的各行输入命令，每行末尾加一个换行符。之前提到过， 注释可用#添加

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 显示消息

显示日期和登录的用户

```bash
#!/bin/bash
# This script displays the date and who's logged on

echo  The time and date are:
date
echo "Let's see who's logged into the system:"
who
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 使用变量

环境变量

```bash
#!/bin/bash
# display user information from the system

echo "User info for userid: $USER"
echo UID: $UID
echo HOME: $HOME
```

用户自定义变量

```bash
#!/bin/bash
# testing variables

days=10
guest="Katie"
echo "$guest checked in $days days ago"
days=5
guest="Jessica"
echo "$guest checked in $days days ago"
```

将一个变量赋值给另一个变量

```bash
#!/bin/bash
# assigning a variable value to another variable

value1=10
value2=$value1
echo The resulting value is $value2
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 命令替换

有两种方法可以将命令输出赋给变量。

-  反引号`
-  $( )格式

执行命令替换符内的命令

```bash
#!/bin/bash
# Execute the command in the command substitution character

# testing=`date`
testing=$(date)
echo "The date and time are: " $testing
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 重定向输入和输出

输出重定向：bash shell 使用大于号(>)来实现该操作

```bash
#!/bin/bash
# command > outputfile

date > t.txt
```

输入重定向：输入重定向运算符是小于号(<)

```bash
#!/bin/bash
# command < inputfile

wc < t.txt
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 管道

bash shell 使用 ｜ 来实现该操作

```bash
command1 | command2
```

可别以为由管道串联起的两个命令会依次执行。实际上，Linux 系统会同时运行这两个命令， 在系统内部将二者连接起来。当第一个命令产生输出时，它会被立即传给第二个命令。数据传输 不会用到任何中间文件或缓冲区。

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 执行数学运算

| 运算符                   | 描述                                                         |
| ------------------------ | ------------------------------------------------------------ |
| ARG1 ｜ARG2              | 如果 ARG1 既不为 null 也不为 0，就返回 ARG1;否则，返回 ARG2  |
| ARG1 & ARG2              | 如果 ARG1 和 ARG2 都不为 null 或 0，就返回 ARG1;否则，返回 0 |
| ARG1 < ARG2              | 如果 ARG1 小于 ARG2，就返回 1;否则，返回 0                   |
| ARG1 <= ARG2             | 如果 ARG1 小于或等于 ARG2，就返回 1;否则，返回 0             |
| ARG1 = ARG2              | 如果 ARG1 等于 ARG2，就返回 1;否则，返回 0                   |
| ARG1 != ARG2             | 如果 ARG1 不等于 ARG2，就返回 1;否则，返回 0                 |
| ARG1 >= ARG2             | 如果 ARG1 大于或等于 ARG2，就返回 1;否则，返回 0             |
| ARG1 > ARG2              | 如果 ARG1 大于 ARG2，就返回 1;否则，返回 0                   |
| ARG1 + ARG2              | 返回 ARG1 和 ARG2 之和                                       |
| ARG1 - ARG2              | 返回 ARG1 和 ARG2 之差                                       |
| ARG1 * ARG2              | 返回 ARG1 和 ARG2 之积                                       |
| ARG1 / ARG2              | 返回 ARG1 和 ARG2 之商                                       |
| ARG1 % ARG2              | 返回 ARG1 和 ARG2 之余数                                     |
| STRING : REGEXP          | 如果 REGEXP 模式匹配 STRING，就返回该模式匹配的内容          |
| match STRING REGEXP      | 如果 REGEXP 模式匹配 STRING，就返回该模式匹配的内容          |
| substr STRING POS LENGTH | 返回起始位置为 POS(从 1 开始计数)、长度为 LENGTH 的子串      |
| index STRING CHARS       | 返回 CHARS 在字符串 STRING 中所处的位置;否则，返回 0         |
| length STRING            | 返回字符串 STRING 的长度                                     |
| \+ TOKEN                 | 将 TOKEN 解释成字符串，即使 TOKEN 属于关键字                 |
| (EXPRESSION)             | 返回 EXPRESSION 的值                                         |

**expr**命令

```bash
#!/bin/bash
# An example of using the expr command

var1=10
var2=20
var3=$(expr $var2 / $var1)
echo The result is $var3
```

使用方括号

```bash
#!/bin/bash
# Using square brackets to perform mathematical operations is much more convenient than using the expr command

var1=100
var2=50
var3=45
var4=$[$var1 * ($var2 - $var3)]
echo The final result is $var4
```

浮点数解决方案

```bash
#!/bin/bash
# Use BC to handle floating point numbers in the script

var1=20
var2=3.14159
var3=$(echo "scale=4; $var1 * $var1" | bc)
var4=$(echo "scale=4; $var3 * $var2" | bc)
echo The final result is $var4
```

bc输入重定向处理更多字符

```bash
#!/bin/bash
# BC input redirection handles more characters

var1=10.46
var2=43.67
var3=33.2
var4=71

var5=$(bc << EOF
scale = 4
a1 = ( $var1 * $var2)
b1 = ($var3 * $var4)
a1 + b1
EOF
)
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 退出脚本

| 状态码 |              描述              |
| :----: | :----------------------------: |
|   0    |          命令成功结束          |
|   1    |         一般性未知错误         |
|   2    |      不适合的 shell 命令       |
|  126   |          命令无法执行          |
|  127   |           没找到命令           |
|  128   |         无效的退出参数         |
| 128+x  | 与 Linux 信号 x 相关的严重错误 |
|  130   |     通过 Ctrl+C 终止的命令     |
|  255   |    正常范围之外的退出状态码    |

```bash
#!/bin/bash
# testing the exit status

var1=10
var2=30
var3=$[ $var1 * var2 ]
echo The value is $var3
exit $var3
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 实战

计算两个日期之间的天数

```bash
#!/bin/bash
# calculate the number of days between two dates

date1="Jan 1, 2020"
date2="May 1, 2020"

time1=$(date -v "$date1" +%s)
time2=$(date -v "$date2" +%s)

diff=$(expr $time2 - $time1)
secondsinday=$(expr 24 \* 60 \* 60)
days=$(expr $diff / $secondsinday)

echo "The difference between $date2 and $date1 is $days days"
```

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)

## 小结

bash shell 脚本允许将多个字符串命令依次放入脚本。创建脚本的最基本方式是将命令行中 的多个命令以分号隔开。shell 会按顺序逐个执行命令，在屏幕上显示每个命令的输出。

你也可以创建一个 shell 脚本文件，将多个命令放进去，让 shell 依次执行。shell 脚本文件必 须定义用于运行该脚本的 shell。这可以通过#!符号在脚本文件的第一行指定，随后跟上 shell 的 完整路径。

在 shell 脚本内，你既可以在变量名前使用美元符号来引用环境变量，也可以定义自己的变 量并对其赋值，甚至还可以通过反引号或$()获取命令的输出。

bash shell 允许重定向命令的标准输入和标准输出。你可以使用大于号以及文件名将命令输 出从屏幕重定向到该文件中。你也可以使用双大于号将输出数据追加到已有文件。小于号则用来 重定向命令输入，比如将命令输入重定向到文件。

Linux 管道命令(断条符号)允许将命令的输出直接传给另一个命令。Linux 系统会同时运 行这两个命令，将第一个命令的输出作为第二个命令的输入，不借助任何中间文件。

bash shell 提供了两种方式以在 shell 脚本中执行数学运算。expr 命令是一种执行整数运算的 简便方法。在 bash shell 中，也可以通过将美元符号放在由方括号包围的表达式之前来执行基础 数学运算。对于浮点数运算，要用到 bc 命令，将内联数据重定向到输入，然后将输出保存到用 户自定义变量中。

最后，本章讨论了如何在 shell 脚本中使用退出状态码。shell 中运行的每个命令都会产生一 个退出状态码，这是 0~255 的一个整数值，表明命令是否成功执行，如果没有成功，可能的原 因是什么。退出状态码 0 表明命令成功执行。你可以在 shell 脚本中用 exit 命令来指定脚本完 成时的退出状态码。

到目前为止，shell 脚本中的命令都是按照有序的方式一个接着一个执行。第 12 章将介绍如 何用一些逻辑流程控制来更改命令的执行次序

---
下一篇：[练习2 结构化命令](../practice-02/)，[目录](#构建基础脚本)｜[首页](../README.md)