# 初识sed和gawk

- [文本处理](#文本处理)
    - [sed编辑器](sed编辑器)
    - [gawk编辑器](#gawk编辑器)
- [sed编辑器基础命令](#sed编辑器基础命令)
    - [更多的替换选项](#更多的替换选项)
    - [使用地址](#使用地址)
    - [删除行](#删除行)
    - [插入和附加文本](#插入和附加文本)
    - [修改行](#修改行)
    - [转换命令](#转换命令)
- [实战](#实战)
- [小结](#小结)

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

## 文本处理

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### sed编辑器

sed 编辑器被称作流编辑器(stream editor)，与普通的交互式文本编辑器截然不同。在交互 式文本编辑器(比如 Vim)中，可以用键盘命令交互式地插入、删除或替换文本数据。

sed 编辑器根据命令来处理数据流中的数据，这些命令要么从命令行中输入，要么保存在命 令文本文件中。sed 编辑器可以执行下列操作。

1. 从输入中读取一行数据。
2. 根据所提供的编辑器命令匹配数据。
3. 按照命令修改数据流中的数据。
4. 将新的数据输出到 STDOUT。

sed 命令的格式如下。 `sed options file`

| 选项        | 描述                                                 |
| ----------- | ---------------------------------------------------- |
| -e commands | 在处理输入时，加入额外的 sed 命令                    |
| -f file     | 在处理输入时，将 file 中指定的命令添加到已有的命令中 |
| -n          | 不产生命令输出，使用 p(print)命令完成输出            |

在命令行中定义编辑器命令

```bash
$ echo "This is a test" | sed 's/test/big test/' 
This is a big test
```

在命令行中使用多个编辑器命令

```bash
$ sed -e 's/brown/red/; s/dog/cat/' data1.txt 
The quick red fox jumps over the lazy cat. 
The quick red fox jumps over the lazy cat. 
The quick red fox jumps over the lazy cat. 
The quick red fox jumps over the lazy cat.
```

从文件中读取编辑器命令

```bash
$ cat script1.sed 
s/brown/green/ 
s/fox/toad/ 
s/dog/cat/
$
$ sed -f script1.sed data1.txt
The quick green toad jumps over the lazy cat. 
The quick green toad jumps over the lazy cat. 
The quick green toad jumps over the lazy cat. 
The quick green toad jumps over the lazy cat. 
$
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### gawk编辑器

gawk 是 Unix 中最初的 awk 的 GNU 版本。gawk 比 sed 的流编辑提升了一个“段位”，它提 供了一种编程语言，而不仅仅是编辑器命令。在 gawk 编程语言中，可以实现以下操作

- 定义变量来保存数据。 
- 使用算术和字符串运算符来处理数据。
- 使用结构化编程概念(比如 if-then 语句和循环)为数据处理添加处理逻辑。
-  提取文件中的数据将其重新排列组合，最后生成格式化报告。

gawk 的基本格式如下。 `gawk options program file`

| 选项         | 描述                             |
| ------------ | -------------------------------- |
| -F fs        | 指定行中划分数据字段的字段分隔符 |
| -f file      | 从指定文件中读取 gawk 脚本代码   |
| -v var=value | 定义 gawk 脚本中的变量及其默认值 |
| -L [keyword] | 指定 gawk 的兼容模式或警告级别   |

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

## sed编辑器基础命令

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 更多的替换选项

替换标志

有 4 种可用的替换标志。

- 数字，指明新文本将替换行中的第几处匹配。
- g，指明新文本将替换行中所有的匹配。
- p，指明打印出替换后的行。
- w file，将替换的结果写入文件。

```bash
$ cat data4.txt 18 This is a test of the test script.
This is the second test of the test script.
$
$ sed 's/test/trial/' data4.txt
This is a trial of the test script.
This is the second trial of the test script. 
$
$ sed 's/test/trial/2' data4.txt
This is a test of the trial script.
This is the second test of the trial script. 
$
$ sed 's/test/trial/g' data4.txt
This is a trial of the trial script.
This is the second trial of the trial script.
$
$ cat data5.txt
This is a test line.
This is a different line.
$
$ sed -n 's/test/trial/p' data5.txt This is a trial line.
$
$ sed 's/test/trial/w test.txt' data5.txt This is a trial line.
This is a different line.
$
$ cat test.txt
This is a trial line. 
$
```

替代字符

```bash
$ sed 's!/bin/bash!/bin/csh!' /etc/passwd
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 使用地址

在 sed 编辑器中有两种形式的行寻址。

- 以数字形式表示的行区间。
- 匹配行内文本的模式。

```bash
$ cat data1.txt
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy dog. 
$
$ sed '2s/dog/cat/' data1.txt
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy cat. 
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy dog. 
$
The quick brown fox jumps over the lazy dog.
$ sed '2,3s/dog/cat/' data1.txt
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy cat. 
The quick brown fox jumps over the lazy cat.
The quick brown fox jumps over the lazy dog.
$
$ sed '2,$s/dog/cat/' data1.txt 
The quick brown fox jumps over the lazy dog.
The quick brown fox jumps over the lazy cat.
The quick brown fox jumps over the lazy cat.
The quick brown fox jumps over the lazy cat.
$
```

使用文本模式过滤

```bash
$ grep /bin/bash /etc/passwd 
root:x:0:0:root:/root:/bin/bash 
christine:x:1001:1001::/home/christine:/bin/bash 
rich:x:1002:1002::/home/rich:/bin/bash
$
$ sed '/rich/s/bash/csh/' /etc/passwd 
root:x:0:0:root:/root:/bin/bash daemon:x:1:1:daemon:/usr/sbin:/usr/sbin/nologin 
[...] 
christine:x:1001:1001::/home/christine:/bin/bash 
sshd:x:126:65534::/run/sshd:/usr/sbin/nologin 
rich:x:1002:1002::/home/rich:/bin/csh
$
```

命令组

```bash
$ sed '2{
> s/fox/toad/
> s/dog/cat/
> }' data1.txt
The quick brown fox jumps over the lazy dog. 
The quick brown toad jumps over the lazy cat. 
The quick brown fox jumps over the lazy dog. 
The quick brown fox jumps over the lazy dog. 
$
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 删除行

文本替换命令并非 sed 编辑器唯一的命令。如果需要删除文本流中的特定行，可以使用删除 (d)命令。

```bash
$ cat data6.txt
This is line number 1. 
This is line number 2.
This is the 3rd line. 
This is the 4th line. 
$
$ sed '3d' data6.txt 
This is line number 1.
This is line number 2. 
This is the 4th line. 
$
```

> 记住，sed 编辑器不会修改原始文件。你删除的行只是从 sed 编辑器的输出中消失了。原 始文件中仍然包含那些“被删掉”的行。

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 插入和附加文本

如你所望，跟其他编辑器类似，sed 编辑器也可以向数据流中插入和附加文本行。这两种操 作的区别可能比较费解。

- 插入(insert)(i)命令会在指定行前增加一行。
- 附加(append)(a)命令会在指定行后增加一行。

```bash
$ cat data6.txt
This is line number 1.
This is line number 2.
This is the 3rd line.
This is the 4th line.
$
$ sed '3i\
> This is an inserted line.
> ' data6.txt
This is line number 1. 
This is line number 2. 
This is an inserted line. 
This is the 3rd line. 
This is the 4th line.
$
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 修改行

```bash
$ sed '2c\
> This is a changed line of text. > ' data6.txt
This is line number 1.
This is a changed line of text. This is the 3rd line.
This is the 4th line.
$
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

### 转换命令

转换(y)命令是唯一可以处理单个字符的 sed 编辑器命令。该命令格式如下所示

`[address]y/inchars/outchars/`

```bash
$ cat data9.txt
This is line 1.
This is line 2.
This is line 3.
This is line 4.
This is line 5.
This is line 1 again.
This is line 3 again.
This is the last file line. $
$ sed 'y/123/789/' data9.txt This is line 7.
This is line 8.
This is line 9.
This is line 4.
This is line 5.
This is line 7 again.
This is line 9 again.
This is the last file line.
$
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

## 实战

```bash
#!/bin/bash
# Change the shebang used for a directory of scripts

################## Function Declarations ##########################

function errorOrExit {
	echo
	echo $message1
	echo $message2
	echo "Exiting script..."
	exit
}

function modifyScripts {
	echo
	read -p "Directory name in which to store new scripts? " newScriptDir
	
	echo "Modifying the scripts started at $(date +%N) nanoseconds"
	
	count=0
	for filename in $(grep -l "/bin/sh" $scriptDir/*.sh)
	do
		newFilename=$(basename $filename)
		cat $filename | 
		sed '1c\#!/bin/bash' > $newScriptDir/$newFilename
		count=$[$count + 1] 
	done
	echo "$count modifications completed at $(date +%N) nanoseconds"
}

################# Check for Script Directory ######################
if [ -z $1 ]
then 
	message1="The name of the directory containing scripts to check"
	message2="is missing. Please provide the name as a parameter."
        errorOrExit
else
	scriptDir=$1
fi 

################ Create Shebang Report ############################

sed -sn '1F; 
1s!/bin/sh!/bin/bash!' $scriptDir/*.sh | 
gawk 'BEGIN {print ""
print "The following scripts have /bin/sh as their shebang:"
print "==================================================="}
{print $0}
END {print ""
print "End of Report"}'

################## Change Scripts? #################################

echo
read -p "Do you wish to modify these scripts' shebang? (Y/n)? " answer

case $answer in
Y | y)
	modifyScripts
	;;
N | n)
	message1="No scripts will be modified."
	message2="Run this script later to modify, if desired."
	errorOrExit
	;;
*)
	message1="Did not answer Y or n."
	message2="No scripts will be modified."
	errorOrExit
	;;
esac
```

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)

## 小结

虽然 shell 脚本本身就能完成不少工作，但在处理数据时往往会有困难。为此，Linux 提供了 两款方便的工具。sed 是一款流编辑器，可以在读取数据时快速地即时进行处理，但你必须给 sed 编辑器指定用于处理数据的编辑命令。

gawk 程序是一款来自 GNU 组织的实用工具，它模仿并扩展了 Unix 中 awk 程序的功能。gawk 内建了编程语言，可用来编写数据处理脚本。gawk 脚本可以从大型数据文件中提取数据元素，并 将其按照需要的格式输出。这非常有助于处理大型日志文件以及从数据文件中生成定制报表。

使用 sed 和 gawk 的关键在于懂得正则表达式。在提取和处理文本文件数据时，正则表达式 是创建定制过滤器的关键。第 20 章将深入探索经常被人们误解的正则表达式，演示如何构建正 则表达式，以处理各种各样的数据

---
下一篇：[练习9 sed进阶](../practice-09/)，上一篇：[练习7 创建函数](../practice-07/)，[目录](#初识sed和gawk)｜[首页](../README.md)