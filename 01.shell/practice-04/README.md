# 处理用户输入

- [传递参数](#传递参数)
    - [读取参数](#读取参数)
    - [读取脚本名](#读取脚本名)
    - [参数测试](#参数测试)
- [特殊参数变量](#特殊参数变量)
    - [参数统计](#参数统计)
    - [获取所有的数据](#获取所有的数据)
- [移动参数](#移动参数)
- [处理选项](#处理选项)
    - [查找选项](#查找选项)
    - [使用getopt命令](#使用getopt命令)
    - [使用getopts命令](#使用getopts命令)
- [获取用户输入](#获取用户输入)
    - [基本的读取](#基本的读取)
    - [超时](#超时)
    - [无显示读取](#无显示读取)
    - [从文件中读取](#从文件中读取)
- [实战](#实战)
- [小结](#小结)

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)


## 传递参数

```bash
#!/bin/bash
# Adding command-line parameters

if [ $# -ne 2 ] 
then
     echo Usage: $(basename $0) parameter1 parameter2
else
     total=$[ $1 + $2 ]
     echo $1 + $2 is $total
fi
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 读取参数

$0 对应脚本名，$1 对应第一个命令行参数，$2 对应第二个命令行参数，以此类推，直到$9

```bash
#!/bin/bash
# Using one command-line parameter
factorial=1
for (( number = 1; number <= $1; number++ ))
do
     factorial=$[ $factorial * $number ]
done
echo The factorial of $1 is $factorial
exit

# Using two command-line parameters
product=$[ $1 * $2 ]
echo The first parameter is $1.
echo The second parameter is $2.
echo The product value is $product.
exit
```

参数之间是以空格分隔的，所以 shell 会将字符串包含的空格视为两个参数的分隔符。 要想在参数值中加入空格，必须使用引号(单引号或双引号均可)

```bash
#!/bin/bash
# Using one command-line string parameter

echo Hello $1, glad to meet you.
exit 
```

> 将文本字符串作为参数传递时，引号并不是数据的一部分，仅用于表明数据的起止位置

如果脚本需要的命令行参数不止 9 个，则仍可以继续加入更多的参数，但是需要稍微修改一 下位置变量名。在第 9 个位置变量之后，必须在变量名两侧加上花括号，比如${10}

```bash
#!/bin/bash
# Handling lots of command-line parameters

product=$[ ${10} * ${11} ]
echo The tenth parameter is ${10}.
echo The eleventh parameter is ${11}.
echo The product value is $product.
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 读取脚本名

`basename` 命令可以返回不包含路径的脚本名

```bash
#!/bin/bash
# Using the $0 command-line parameter in messages

scriptname=$(basename $0)
echo The $scriptname run at $(date) >> $HOME/scripttrack.log
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 参数测试

在使用位置变量之前一定要检查是否为空

```bash
#!/bin/bash
# Using one command-line parameter

if [ -n "$1" ]
then
     factorial=1
     for (( number = 1; number <= $1; number++ ))
     do
          factorial=$[ $factorial * $number ]
     done
     echo The factorial of $1 is $factorial
else
     echo "You did not provide a parameter."
fi
exit 
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 特殊参数变量

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 参数统计

特殊变量`$#`含有脚本运行时携带的命令行参数的个数

```bash
#!/bin/bash
# Counting command-line parameters

if [ $# -eq 1 ] 
then
     fragment="parameter was"
else
     fragment="parameters were"
fi
echo $# $fragment supplied.
exit
```

获取命令行中最后一个参数

```bash
#!/bin/bash
# Testing grabbing the last parameter

echo The number of parameters is $#
echo The last parameter is ${!#}
exit
```

> 当命令行中没有任何参数时，`$#`的值即为 0，但`${!#}`会返回命令行中的脚本名。

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 获取所有的数据

`$*`变量和`$@`变量可以轻松访问所有参数

$*变量会将所有的命令行参数视为一个单词。这个单词含有命令行中出现的每一个参数。 基本上，$*变量会将这些参数视为一个整体，而不是一系列个体。

```bash
#!/bin/bash
# Testing different methods for grabbing all the parameters

echo
echo "Using the \$* method: $*"
echo 
echo "Using the \$@ method: $@"
echo 
exit
```

`$@`变量会将所有的命令行参数视为同一字符串中的多个独立的单词

```bash
#!/bin/bash
# Exploring different methods for grabbing all the parameters

echo
echo "Using the \$* method: $*"
count=1
for param in "$*"
do
     echo "\$* Parameter #$count = $param"
     count=$[ $count + 1 ]
done

echo 
echo "Using the \$@ method: $@"
count=1
for param in "$@"
do
     echo "\$@ Parameter #$count = $param"
     count=$[ $count + 1 ]
done
echo 
exit
```

> `$*`变量会将所有参数视为单个参数，而`$@`变量会单独处理每个参数
>
> 这里再详细说明一下`$*`和`$@`的区别。当`$*`出现在双引号内时，会被扩展成由多个命令行参数组成的单个单词，每 个参数之间以 IFS 变量值的第一个字符分隔，也就是说，`$*`会被扩展"$1c$2c.."(其中 c 是 IFS 变量值 的第一个字符)。当`$@`出现在双引号内时，其所包含的各个命令行参数会被扩展成独立的单词，也就是说，`$@`会被扩展为"$1""$2"

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 移动参数

在使用 shift 命令时，默认情况下会将每个位置的变量值都向左移动一个位置。因此，变 量$3 的值会移入$2，变量$2 的值会移入$1，而变量$1 的值则会被删除(注意，变量$0 的值， 也就是脚本名，不会改变)。

```bash
#!/bin/bash
# Shifting through the parameters

echo 
echo "Using the shift method:"
count=1
while [ -n "$1" ]
do
     echo "Parameter #$count = $1"
     count=$[ $count + 1 ]
     shift
done
echo 
exit
```

> 使用 shift 命令时要小心。如果某个参数被移出，那么它的值就被丢弃了，无法再恢复。

也可以一次性移动多个位置。只需给 shift 命令提供一个参数，指明要移动的位置 数即可

```bash
#!/bin/bash
# Shifting mulitiple positions through the parameters

echo 
echo "The original parameters: $*"
echo "Now shifting 2..."
shift 2
echo "Here's the new first parameter: $1"
echo
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 处理选项

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 查找选项

处理简单选项

```bash
#!/bin/bash
# Extract command-line options

echo 
while [ -n "$1" ]
do
     case "$1" in
          -a) echo "Found the -a option" ;;
          -b) echo "Found the -b option" ;;
          -c) echo "Found the -c option" ;;
          *) echo "$1 is not an option" ;;
     esac
     shift
done
echo 
exit
```

分离参数和选项

```bash
#!/bin/bash
# Extract command-line options and parameters

echo 
while [ -n "$1" ]
do
     case "$1" in
          -a) echo "Found the -a option" ;;
          -b) echo "Found the -b option" ;;
          -c) echo "Found the -c option" ;;
          --) shift
              break;;
          *) echo "$1 is not an option" ;;
     esac
     shift
done
#
echo
count=1
for param in $@
do
     echo "Parameter #$count: $param"
     count=$[ $count + 1 ]
done
echo 
exit
```

处理含值的选项

```bash
#!/bin/bash
# Extract command-line options and values

echo 
while [ -n "$1" ]
do
     case "$1" in
          -a) echo "Found the -a option" ;;
          -b) param=$2 
              echo "Found the -b option with parameter value $param" 
              shift;;
          -c) echo "Found the -c option" ;;
          --) shift
              break;;
          *) echo "$1 is not an option" ;;
     esac
     shift
done
#
echo
count=1
for param in $@
do
     echo "Parameter #$count: $param"
     count=$[ $count + 1 ]
done
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 使用getopt命令

`getopt optstring parameters`

```bash
#!/bin/bash
# Extract command-line options and values with getopt

set -- $(getopt -q ab:cd "$@")

echo 
while [ -n "$1" ]
do
     case "$1" in
          -a) echo "Found the -a option" ;;
          -b) param=$2 
              echo "Found the -b option with parameter value $param" 
              shift;;
          -c) echo "Found the -c option" ;;
          --) shift
              break;;
          *) echo "$1 is not an option" ;;
     esac
     shift
done

echo
count=1
for param in $@
do
     echo "Parameter #$count: $param"
     count=$[ $count + 1 ]
done
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 使用getopts命令

`getopts optstring variable`

```bash
#!/bin/bash
# Extract command-line options and values with getopts

echo 
while getopts :ab:c opt
do
     case "$opt" in
          a) echo "Found the -a option" ;;
          b) echo "Found the -b option with parameter value $OPTARG";;
          c) echo "Found the -c option" ;;
          *) echo "Unknown option: $opt" ;;
     esac
done
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 获取用户输入

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 基本的读取

read 命令从标准输入(键盘)或另一个文件描述符中接受输入。获取输入后，read 命令会 将数据存入变量。

```bash
#!/bin/bash
# Using the read command with REPLY variable

read -p "Enter your name: "
echo
echo "Hello $REPLY, welcome to my script."
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 超时

使用 read 命令时要当心。脚本可能会一直苦等着用户输入。如果不管是否有数据输入，脚 本都必须继续执行，你可以用-t 选项来指定一个计时器。-t 选项会指定 read 命令等待输入的 秒数。如果计时器超时，则 read 命令会返回非 0 退出状态码

```bash
#!/bin/bash
# Using the read command with a timer

if read -t 5 -p "Enter your name: " name
then
     echo "Hello $name, welcome to my script."
else
     echo
     echo "Sorry, no longer waiting for name."
fi
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 无显示读取

-s 选项可以避免在 read 命令中输入的数据出现在屏幕上(其实数据还是会被显示，只不 过 read 命令将文本颜色设成了跟背景色一样)。

```bash
#!/bin/bash
# Hiding input data

read -s -p "Enter your password: " pass
echo
echo "Your password is $pass"
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

### 从文件中读取

```bash
#!/bin/bash
# Using the read command to read a file

count=1
cat $HOME/scripts/test.txt | while read line
do
     echo "Line $count: $line"
     count=$[ $count + 1 ]
done
echo "Finished processing the file."
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 实战

该脚本在处理用户输入的同时，使用 ping 命令或 ping6 命令 来测试与其他网络主机的连通性

```bash
#!/bin/bash
# Check systems on local network
# allowing for a variety of input
# methods.


########### Determine Input Method ###################


# Check for command-line options here using getopts. 
# If none, then go on to File Input Method

while getopts t: opt 
do
     case "$opt" in
          t) # Found the -t option 
             if [ $OPTARG = "IPv4" ]
             then
                  pingcommand=$(which ping)
             
             elif [ $OPTARG = "IPv6" ]
             then
                  pingcommand=$(which ping6)
             
             else
                  echo "Usage: -t IPv4 or -t IPv6"
                  echo "Exiting script..."
                  exit
             fi
             ;;
          *) echo "Usage: -t IPv4 or -t IPv6"
             echo "Exiting script..."
             exit;;
     esac
     
     shift $[ $OPTIND - 1 ]
     
     if [ $# -eq 0 ]
     then
          echo
          echo "IP Address(es) parameters are missing."
          echo
          echo "Exiting script..."
          exit
     fi

     for ipaddress in "$@"
     do
          echo
          echo "Checking system at $ipaddress..."
          echo
          $pingcommand -q -c 3 $ipaddress
          echo
     done
     exit
done

########### File Input Method ###################

echo
echo "Please enter the file name with an absolute directory reference..."
echo
choice=0
while [ $choice -eq 0 ] 
do
     read -t 60 -p "Enter name of file: " filename
     if [ -z $filename ]
     then
          quitanswer=""
          read -t 10 -n 1 -p "Quit script [Y/n]? " quitanswer
          #
          case $quitanswer in 
          Y | y) echo
                 echo "Quitting script..."
                 exit;;
          N | n) echo
                 echo "Please answer question: "
                 choice=0;;
          *)     echo 
                 echo "No response. Quitting script..."
                 exit;;
          esac
     else
          choice=1
     fi
done

if [ -s $filename ] && [ -r $filename ]
     then
          echo "$filename is a file, is readable, and is not empty."
          echo
          cat $filename | while read line
          do
               ipaddress=$line
               read line
               iptype=$line
               if [ $iptype = "IPv4" ]
               then
                    pingcommand=$(which ping)
               else
                    pingcommand=$(which ping6)
               fi
               echo "Checking system at $ipaddress..."
               $pingcommand -q -c 3 $ipaddress
               echo
          done
          echo "Finished processing the file. All systems checked."
     else
          echo 
          echo "$filename is either not a file, is empty, or is"
          echo "not readable by you. Exiting script..."
fi 
#################### Exit Script #####################
exit
```

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)

## 小结

本章展示了从脚本用户处获取数据的 3 种方法。命令行参数允许用户运行脚本时直接在命令 行中输入数据。脚本可通过位置变量获取命令行参数。

shift 命令通过对位置变量进行轮转(rotating)的方式来操作命令行参数。就算不知道参 数的数量，也可以轻松遍历所有参数。

有 3 个特殊变量可以用来处理命令行参数。shell 会将$#变量设为命令行参数的个数。$*变 量会将所有命令行参数保存为一个字符串。$@变量会将所有命令行参数保存为独立的单词。这些 变量在处理参数列表时非常有用。

除了命令行参数，还可以通过命令行选项向脚本传递信息。命令行选项是以连字符起始的单 个字母。可以使用不同选项改变脚本的行为。

bash shell 提供了 3 种方法来处理命令行选项。第一种方法是将其像命令行参数一样处理。利 用位置变量遍历选项并进行相应的处理。第二种方法是使用 getopt 将命令行选项和参数转换成 可以在脚本中处理的标准格式。最后一种方法是使用拥有更多高级功能的 getopts 命令。

read 命令能够以交互式方法从脚本用户处获得数据。该命令允许脚本向用户询问并等待用 户回答。read 命令会将脚本用户输入的数据存入一个或多个变量，以方便在脚本中使用。

read 命令有一些选项支持自定义脚本的输入数据，比如不显示用户输入、超时选项以及限 制输入的字符数量。

---
下一篇：[练习5 呈现数据](../practice-05/)，上一篇：[练习3 更多的结构化命令](../practice-03/)，[目录](#处理用户输入)｜[首页](../README.md)