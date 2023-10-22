# 更多的结构化命令

- [for命令](#for命令)
    - [读取列表中的值](#读取列表中的值)
    - [从变量中读取值列表](#从变量中读取值列表)
    - [从命令中读取值列表](#从命令中读取值列表)
    - [更改字段分隔符](#更改字段分隔符)
    - [使用通配符读取目录](#使用通配符读取目录)
    - [c语言风格](#c语言风格)
- [while命令](#while命令)
- [until命令](#until命令)
- [嵌套循环](#until命令)
- [循环控制](#循环控制)
    - [break](#break)
    - [continue](#continue)
- [处理循环的输出](#处理循环的输出)
- [实战](#处理循环的输出)
- [小结](#小结)

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## for命令

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### 读取列表中的值

for 循环假定各个值之间是以空格分隔的

- 使用转义字符(反斜线)将单引号转义
- 使用双引号来定义含有单引号的值

```bash
#!/bin/bash
# another example of how not to use the for command
for test in I don\'t know if "this'll" work
do
   echo "word:$test"
done

# an example of how to properly define values
for test in Nevada "New Hampshire" "New Mexico" "New York"
do
   echo "Now going to $test"
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### 从变量中读取值列表

```bash
#!/bin/bash
# using a variable to hold the list
 
list="Alabama Alaska Arizona Arkansas Colorado"
list=$list" Connecticut"
 
for state in $list
do
   echo "Have you ever visited $state?"
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### 从命令中读取值列表

```bash
#!/bin/bash
# reading values from a file
 
file="states"
 
for state in $(cat $file)
do
   echo "Visit beautiful $state"
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### 更改字段分隔符

造成这个问题的原因是特殊的环境变量 IFS(internal field separator，内部字段分隔符)。IFS 环境变量定义了 bash shell 用作字段分隔符的一系列字符。在默认情况下，bash shell 会将下列字 符视为字段分隔符。

- 空格
- 制表符
- 换行符

```bash
#!/bin/bash
# reading values from a file
 
file="states"
 
IFS=$'\n'
for state in $(cat $file)
do
   echo "Visit beautiful $state"
done
```

> 在处理代码量较大的脚本时，可能在一个地方需要修改 IFS 的值，然后再将其恢复原 状，而脚本的其他地方则继续沿用 IFS 的默认值。一种安全的做法是在修改 IFS 之前保 存原来的 IFS 值，之后再恢复它。
>  这种技术可以像下面这样来实现:
>
> IFS.OLD=$IFS IFS=$'\n' <在代码中使用新的 IFS 值> IFS=$IFS.OLD
>
> 这就保证了在脚本的后续操作中使用的是 IFS 的默认值。

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### 使用通配符读取目录

```bash
#!/bin/bash
# iterating through multiple directories
 
for file in /home/rich/.b* /home/rich/badtest
do
   if [ -d "$file" ]
   then
      echo "$file is a directory"
   elif [ -f "$file" ]
   then
      echo "$file is a file"
   else
     echo "$file doesn't exist"
   fi
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### c语言风格

注意，有些地方与 bash shell 标准的 for 命令并不一致。 

- 变量赋值可以有空格。
- 迭代条件中的变量不以美元符号开头。
- 迭代过程的算式不使用 expr 命令格式。

```bash
#!/bin/bash
# testing the C-style for loop
 
for (( i=1; i <= 10; i++ ))
do
   echo "The next number is $i"
done

# multiple variables
 
for (( a=1, b=10; a <= 10; a++, b-- ))
do
   echo "$a - $b"
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## while命令

```bash
#!/bin/bash
# while command test
 
var1=10
while [ $var1 -gt 0 ]
do
   echo $var1
   var1=$[ $var1 - 1 ]
done
```

> while 命令允许在 while 语句行定义多个测试命令。只有最后一个测试命令的退出状态码 会被用于决定是否结束循环。如果你不小心，这可能会导致一些有意思的结果。

```bash
#!/bin/bash
# testing a multicommand while loop
 
var1=10

while echo $var1
      [ $var1 -ge 0 ]
do
   echo "This is inside the loop"
   var1=$[ $var1 - 1 ]
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## until命令

```bash
#!/bin/bash
# using the until command
 
var1=100
 
until [ $var1 -eq 0 ]
do
   echo $var1
   var1=$[ $var1 - 25 ]
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## 嵌套循环

```bash
#!/bin/bash
# nesting for loops
 
for (( a = 1; a <= 3; a++ ))
do
   echo "Starting loop $a:"
   for (( b = 1; b <= 3; b++ ))
   do
      echo "   Inside loop: $b"
   done
done

# placing a for loop inside a while loop
var1=5
 
while [ $var1 -ge 0 ]
do
   echo "Outer loop: $var1"
   for (( var2 = 1; $var2 < 3; var2++ ))
   do
      var3=$[ $var1 * $var2 ]
      echo "  Inner loop: $var1 * $var2 = $var3"
   done
   var1=$[ $var1 - 1 ]
done


# using until and while loops 
var1=3
 
until [ $var1 -eq 0 ]
do
   echo "Outer loop: $var1"
   var2=1
   while [ $var2 -lt 5 ]
   do
      var3=$(echo "scale=4; $var1 / $var2" | bc)
      echo "   Inner loop: $var1 / $var2 = $var3"
      var2=$[ $var2 + 1 ]
   done
   var1=$[ $var1 - 1 ]
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## 循环控制

你可能认为循环一旦启动，在结束之前就哪都去不了了。事实并非如此。有两个命令可以控 制循环的结束时机。

- break 命令
- continue 命令

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### break

跳出单个循环

```bash
#!/bin/bash
# breaking out of a for loop
 
for var1 in 1 2 3 4 5 6 7 8 9 10
do
   if [ $var1 -eq 5 ]
   then
      break
   fi
   echo "Iteration number: $var1"
done
echo "The for loop is completed"

# breaking out of a while loop
var1=1
 
while [ $var1 -lt 10 ]
do
   if [ $var1 -eq 5 ]
   then
      break
   fi
   echo "Iteration: $var1"
   var1=$[ $var1 + 1 ]
done
echo "The while loop is completed"
```

跳出内层循环

```bash
#!/bin/bash
# breaking out of an inner loop
 
for (( a = 1; a < 4; a++ ))
do
   echo "Outer loop: $a"
   for (( b = 1; b < 100; b++ ))
   do
      if [ $b -eq 5 ]
      then
         break
      fi
      echo "   Inner loop: $b"
   done
done
```

跳出外层循环

```bash
#!/bin/bash
# breaking out of an outer loop
 
for (( a = 1; a < 4; a++ ))
do
   echo "Outer loop: $a"
   for (( b = 1; b < 100; b++ ))
   do
      if [ $b -gt 4 ]
      then
         break 2
      fi
      echo "   Inner loop: $b"
   done
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

### continue

```bash
#!/bin/bash
# using the continue command
for (( var1 = 1; var1 < 15; var1++ ))
do
   if [ $var1 -gt 5 ] && [ $var1 -lt 10 ]
   then
      continue
   fi
   echo "Iteration number: $var1"
done

# continuing an outer loop 
for (( a = 1; a <= 5; a++ ))
do
   echo "Iteration $a:"
   for (( b = 1; b < 3; b++ ))
   do
      if [ $a -gt 2 ] && [ $a -lt 4 ]
      then
         continue 2
      fi
      var3=$[ $a * $b ]
      echo "   The result of $a * $b is $var3"
   done
done
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## 处理循环的输出

```bash
#!/bin/bash
# redirecting the for output to a file
for (( a = 1; a < 10; a++ ))
do
   echo "The number is $a"
done > test23.txt
echo "The command is finished."

# piping a loop to another command
for state in "North Dakota" Connecticut Illinois Alabama Tennessee
do
   echo "$state is the next place to go"
done | sort
echo "This completes our travels"

```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## 实战

查找可执行文件

```bash
#!/bin/bash
# finding files in the PATH

IFS=:
for folder in $PATH
do
   echo "$folder:"
   for file in $folder/*
   do
      if [ -x $file ]
      then
         echo "   $file"
      fi
   done
done
```

创建多个用户账户

```bash
#!/bin/bash
# process new user accounts

input="users.csv"
while IFS=',' read -r userid name
do
  echo "adding $userid"
  useradd -c "$name" -m $userid
done < "$input"
```

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)

## 小结

循环是编程不可或缺的一部分。bash shell 提供了 3 种可用于脚本中的循环命令。

for 命令允许遍历一系列的值，无论是在命令行中提供的，还是包含在变量中的，或是通过 文件名通配符匹配获得的文件名和目录名。

while 命令提供了基于命令(使用普通命令或 test 命令)的循环方式。只有在命令(或条 件)产生退出状态码 0 时，while 循环才会继续迭代指定的一组命令。

until 命令提供了迭代命令的另一种方式，但它的迭代建立在命令(或条件)产生非 0 退出 状态码的基础上。这个特性允许你设置一个迭代结束前都必须满足的条件。

你可以在 shell 脚本中组合多种循环方式，生成多层循环。bash shell 提供了 continue 命令 和 break 命令，允许根据循环内的不同值改变循环的正常流程。

bash shell 还允许使用标准的命令重定向和管道来改变循环的输出。你可以将循环的输出重 定向至文件或是通过管道将循环的输出传给另一个命令。这就为控制 shell 脚本执行提供了丰富 的功能。

---
下一篇：[练习4 处理用户输入](../practice-04/)，上一篇：[练习2 结构化命令](../practice-02/)，[目录](#更多的结构化命令)｜[首页](../README.md)