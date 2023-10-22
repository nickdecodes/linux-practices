# 创建函数

- [脚本函数基础](#脚本函数基础)
- [函数返回值](#函数返回值)
- [在函数中使用变量](#在函数中使用变量)
    - [向函数传递参数](#向函数传递参数)
    - [在函数中处理变量](#在函数中处理变量)
- [数组变量和函数](#数组变量和函数)
- [函数递归](#函数递归)
- [创建库](#创建库)
- [小结](#小结)

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)


## 脚本函数基础

bash shell 提供了这种功能。函数是一个脚本代码块，你可以为其命名并在脚本中的任何位置重用它。

```bash
#!/bin/bash
# testing using a duplicate function name

function func1 {
echo "This is the first definition of the function name"
}

func1

function func1 {
   echo "This is a repeat of the same function name"
}

func1
echo "This is the end of the script"
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 函数返回值

可以使用标准变量$?来确定函数的退出状态码

- 函数执行一结束就立刻读取返回值。
- 退出状态码必须介于 0~255

```bash
#!/bin/bash
# using the echo to return a value

function dbl {
   read -p "Enter a value: " value
   echo $[ $value * 2 ]
}

result=$(dbl)
echo "The new value is $result"
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 在函数中使用变量

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

### 向函数传递参数

函数可以使用标准的位置变量来表示在命令行中传给函数的任何参数。例如，函数名保存在 `$0` 变量中，函数参数依次保存在`$1`、`$2` 等变量中。也可以用特殊变量$#来确定传给函数的参数数量。

```bash
#!/bin/bash
# trying to access script parameters inside a function

function func7 {
   echo $[ $1 * $2 ]
}

if [ $# -eq 2 ]
then
   value=$(func7 $1 $2)
   echo "The result is $value"
else
   echo "Usage: badtest1 a b"
fi
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

### 在函数中处理变量

给 shell 脚本程序员带来麻烦的情况之一就是变量的作用域。作用域是变量的有效区域。在 函数中定义的变量与普通变量的作用域不同。也就是说，对脚本的其他部分而言，在函数中定义 的变量是无效的。

函数有两种类型的变量。

- 全局变量
- 局部变量

**全局变量**

```bash
#!/bin/bash
# using a global variable to pass a value

function dbl {
   value=$[ $value * 2 ]
}

read -p "Enter a value: " value
dbl
echo "The new value is: $value"
```

**局部变量**

无须在函数中使用全局变量，任何在函数内部使用的变量都可以被声明为局部变量。为此， 只需在变量声明之前加上 `local` 关键字即可

```bash
#!/bin/bash
# demonstrating the local keyword

function func1 {
   local temp=$[ $value + 5 ]
   result=$[ $temp * 2 ]
}

temp=4
value=6

func1
echo "The result is $result"
if [ $temp -gt $value ]
then
   echo "temp is larger"
else
   echo "temp is smaller"
fi
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 数组变量和函数

向函数传递数组

```bash
#!/bin/bash
# array variable to function test

function testit {
   local newarray
   newarray=(`echo "$@"`)
   echo "The new array value is: ${newarray[*]}"
}

myarray=(1 2 3 4 5)
echo "The original array is ${myarray[*]}"
testit ${myarray[*]}
```

```bash
#!/bin/bash
# adding values in an array

function addarray {
   local sum=0
   local newarray
   newarray=(`echo "$@"`)
   for value in ${newarray[*]}
   do
      sum=$[ $sum + $value ]
   done
   echo $sum
}

myarray=(1 2 3 4 5)
echo "The original array is: ${myarray[*]}"
arg1=$(echo ${myarray[*]})
result=$(addarray $arg1)
echo "The result is $result"
```

从函数返回数组

```bash
#!/bin/bash
# returning an array value

function arraydblr {
   local origarray
   local newarray
   local elements
   local i
   origarray=($(echo "$@"))
   newarray=($(echo "$@"))
   elements=$[ $# - 1 ]
   for (( i = 0; i <= $elements; i++ ))
   {
      newarray[$i]=$[ ${origarray[$i]} * 2 ]
   }
   echo ${newarray[*]}
}

myarray=(1 2 3 4 5)
echo "The original array is: ${myarray[*]}"
arg1=$(echo ${myarray[*]})
result=($(arraydblr $arg1))
echo "The new array is: ${result[*]}"
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 函数递归

```bash
#!/bin/bash
# using recursion

function factorial {
   if [ $1 -eq 1 ]
   then
      echo 1
   else
      local temp=$[ $1 - 1 ]
      local result=$(factorial $temp)
      echo $[ $result * $1 ]
   fi
}
 
read -p "Enter value: " value
result=$(factorial $value)
echo "The factorial of $value is: $result"
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 创建库

```bash
# my script functions

function addem {
   echo $[ $1 + $2 ]
}

function multem {
   echo $[ $1 * $2 ]
}

function divem {
   if [ $2 -ne 0 ]
   then
      echo $[ $1 / $2 ]
   else
      echo -1
   fi
}
```

```bash
#!/bin/bash
# using functions defined in a library file
. ./myfuncs

value1=10
value2=5
result1=$(addem $value1 $value2)
result2=$(multem $value1 $value2)
result3=$(divem $value1 $value2)
echo "The result of adding them is: $result1"
echo "The result of multiplying them is: $result2"
echo "The result of dividing them is: $result3"
```

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)

## 小结

shell 脚本函数允许将脚本中多处用到的代码放到一处。你可以创建一个包含该代码块的函 数，然后在脚本中通过函数名来引用这部分代码，无须再一次次地重写。只要看到函数名，bash shell 就会自动跳到对应的函数代码块处。

你甚至可以创建能返回值的函数。这样函数就能够同脚本进行交互，返回数值和字符串。函数可以通过最后一个命令的退出状态码或 return 命令来返回值。return 命令能够基于函数的结果，通过编程的方式将函数的退出状态码设为特定值。

函数也能用标准的 echo 语句返回值。跟其他 shell 命令一样，可以用反引号来获取输出的数据，这样就能从函数中返回任意类型的数据(包括字符串和浮点数)了。

你可以在函数中使用 shell 变量，对其赋值以及从中取值，以此在主脚本和函数之间传入和传出各种类型的数据。函数也支持定义仅用于函数内部的局部变量。局部变量允许创建自成体系 19 的函数，它们不会影响主脚本中的变量或其中的处理过程。

函数也可以调用包括自身在内的其他函数。函数的自调用行为称为递归。递归函数通常包含作为函数终结条件的基准值。函数在调用自身的同时会不停地减少参数值，直到达到基准值。

如果需要在 shell 脚本中使用大量函数，可以创建函数库文件。可以用 source 命令(或该 命令的别名)在任意 shell 脚本文件中引用库文件，这种方法称为源引。shell 并不运行库文件， 但会使这些函数在运行该脚本的 shell 中生效。用同样的方法可以创建在普通 shell 命令行中使用的函数:直接在命令行中定义函数，或者将函数添加到.bashrc 文件中，后一种方法能在每次启动 新的 shell 会话时都使用这些函数。这是一种创建实用工具的简便方法，不管 PATH 环境变量设置 成什么，都可以直接拿来使用。

---
下一篇：[练习8 初识sed和gawk](../practice-08/)，上一篇：[练习6 脚本控制](../practice-06/)，[目录](#创建函数)｜[首页](../README.md)