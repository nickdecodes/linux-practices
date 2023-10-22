# 结构化命令

- [使用if-then语句](#使用if-then语句)
- [if-then-else语句](#if-then-else语句)
- [嵌套if语句](#嵌套if语句)
- [test命令](#test命令)
    - [数值比较](#数值比较)
    - [字符串比较](#字符串比较)
    - [文件比较](#文件比较)
- [复合条件测试](#复合条件测试)
- [if-then的高级特性](#if-then的高级特性)
- [case命令](#case命令)
- [实战](#实战)
- [小结](#小结)

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)


## 使用if-then语句

测试if语句

```bash
#!/bin/bash
# testing the if statement

if pwd
then
     echo "It worked"
fi
```

测试不正确的命令

```bash
#!/bin/bash
# testing an incorrect command

if IamNotaCommand
then
     echo "It worked"
fi
echo "We are outside the if statement"
```

在then块中测试多个命令

```bash
#!/bin/bash
# testing multiple commands in the then block

testuser=NoSuchUser
if grep $testuser /etc/passwd
then
     echo "This is my first command in the then block."
     echo "This is my second command in the then block."
     echo "I can even put in other commands besides echo:"
     ls /home/$testuser/*.sh
fi
echo "We are outside the if statement"
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## if-then-else语句

测试else部分

```bash
#!/bin/bash
# testing the else section

testuser=NoSuchUser
if grep $testuser /etc/passwd
then
     echo "The script files in the home directory of $testuser are:"
     ls /home/$testuser/*.sh
     echo
else
     echo "The user $testuser does not exist on this system."
     echo
fi
echo "We are outside the if statement"

```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## 嵌套if语句

测试嵌套的if -使用elif和else

```bash
#!/bin/bash
# testing nested ifs - using elif and else

testuser=NoSuchUser
if grep $testuser /etc/passwd
then
     echo "The user $testuser account exists on this system."
     echo
elif ls -d /home/$testuser/
     then 
          echo "The user $testuser has a directory,"
          echo "even though $testuser doesn't have an account."
     else
          echo "The user $testuser does not exist on this system,"
          echo "and no directory exists for the $testuser."
fi
echo "We are outside the nested if statements."
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## test命令

如果 test 命令中列出的条件成立，那么 test 命令就会退出并返回退出状态码 0

test 命令的格式非常简单: `test condition`

测试变量是否有内容

```bash
#!/bin/bash
# testing if a variable has content

my_variable=""
if test $my_variable
then
     echo "The my_variable variable has content and returns a True."
     echo "The my_variable variable content is: $my_variable"
else 
     echo "The my_variable variable doesn't have content,"
     echo "and returns a False."
fi
```

bash shell 提供了另一种条件测试方式: `if [ condition ]`

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

### 数值比较

| 比较      | 描述                     |
| --------- | ------------------------ |
| n1 -eq n2 | 检查 n1是否等于 n2       |
| n1 -ge n2 | 检查 n1是否大于或等于 n2 |
| n1 -gt n2 | 检查 n1是否大于 n2       |
| n1 -le n2 | 检查 n1是否小于或等于 n2 |
| n1 -lt n2 | 检查 n1是否小于 n2       |
| n1 -ne n2 | 检查 n1是否不等于 n2     |

使用数值测试评估

```bash
#!/bin/bash
# Using numeric test evaluations

value1=10
value2=11

if [ $value1 -gt 5 ]
then
     echo "The test value $value1 is greater than 5."
fi

if [ $value1 -eq $value2 ]
then 
     echo "The values are equal."
else
     echo "The values are different."
fi
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

### 字符串比较

| 比较         |            描述            |
| :----------- | :------------------------: |
| str1 = str2  | 检查 str1 是否和 str2 相同 |
| str1 != str2 | 检查 str1 是否和 str2 不同 |
| str1 < str2  |  检查 str1 是否小于 str2   |
| str1 > str2  |  检查 str1 是否大于 str2   |
| -n str1      | 检查 str1 的长度是否不为 0 |
| -z str1      |  检查 str1 的长度是否为 0  |

字符串相等性

```bash
#!/bin/bash
# Using string test evaluations

testuser=christine

if [ $testuser = christine ]
then
     echo "The testuser variable contains: christine"
else
     echo "The testuser variable contains: $testuser"
fi
```

```bash
#!/bin/bash
# Using string test not equal evaluations

testuser=rich

if [ $testuser != christine ]
then
     echo "The testuser variable does NOT contain: christine"
else
     echo "The testuser variable contains: christine"
fi
```

字符串顺序

- 大于号和小于号必须转义，否则 shell 会将其视为重定向符，将字符串值当作文件名。
- 大于和小于顺序与 sort 命令所采用的不同。

```bash
#!/bin/bash
# Properly using string comparisons

string1=soccer
string2=zorbfootball

if [ $string1 \> $string2 ]
then
     echo "$string1 is greater than $string2"
else
     echo "$string1 is less than $string2"
fi
```

> 字符串 soccer 小于 zorbfootball，因为在比较的时候使用的是每个字符的 Unicode 编码值。小写字母 s 的编码值是 115，而 z 的编码值是 122。因此，s 小于 z，进而， soccer 小于 zorbfootball。

在比较测试中，大写字母被认为是小于小写字母的。但 sort 命令正好相反。当你将同样的 字符串放进文件中并用 sort 命令排序时，小写字母会先出现。这是由于各个命令使用了不同的 排序技术。

比较测试中使用的是标准的 Unicode 顺序，根据每个字符的 Unicode 编码值来决定排序结果。 sort 命令使用的是系统的语言环境设置中定义的排序顺序。对于英语，语言环境设置指定了在 排序顺序中小写字母出现在大写字母之前。

> test 命令和测试表达式使用标准的数学比较符号来表示字符串比较，而用文本代码来 表示数值比较。这个细微的特性被很多程序员理解反了。如果你对数值使用了数学运算 符号，那么 shell 会将它们当成字符串值，并可能产生错误结果。

字符串大小

-n 和-z 可以很方便地用于检查一个变量是否为空

```bash
#!/bin/bash
# Testing string length

string1=Soccer
string2=''

if [ -n $string1 ]
then
     echo "The string '$string1' is NOT empty"
else
     echo "The string '$string1' IS empty"
fi

if [ -z $string2 ]
then
     echo "The string '$string2' IS empty"
else
     echo "The string '$string2' is NOT empty"
fi

if [ -z $string3 ]
then
     echo "The string '$string3' IS empty"
else
     echo "The string '$string3' is NOT empty"
fi
```

> 空变量和未初始化的变量会对 shell 脚本测试造成灾难性的影响。如果不确定变量的内容， 那么最好在将其用于数值或字符串比较之前先通过-n 或-z 来测试一下变量是否为空。

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

### 文件比较

| 比较            | 描述                                     |
| --------------- | ---------------------------------------- |
| -d file         | 检查 file 是否存在且为目录               |
| -e file         | 检查 file 是否存在                       |
| -f file         | 检查 file 是否存在且为文件               |
| -r file         | 检查 file 是否存在且可读                 |
| -s file         | 检查 file 是否存在且非空                 |
| -w file         | 检查 file 是否存在且可写                 |
| -x file         | 检查 file 是否存在且可执行               |
| -O file         | 检查 file 是否存在且属当前用户所有       |
| -G file         | 检查 file 是否存在且默认组与当前用户相同 |
| file1 -nt file2 | 检查 file1 是否比 file2 新               |
| file1 -ot file2 | 检查 file1 是否比 file2 旧               |

检查目录

```bash
#!/bin/bash
# Look before you leap

jump_directory=/home/Torfa

if [ -d $jump_directory ]
then
     echo "The $jump_directory directory exists."
     cd $jump_directory
     ls 
else
     echo "The $jump_directory directory does NOT exist."
fi
```

检查对象是否存在

```bash
#!/bin/bash
# Check if either a directory or file exists

location=$HOME
file_name="sentinel"

if [ -d $location ]
then
     echo "OK on the $location directory"
     echo "Now checking on the file, $file_name..."
     if [ -e $location/$file_name ]
     then
          echo "OK on the file, $file_name."
          echo "Updating file's contents."
          date >> $location/$file_name
     #
     else
          echo "File, $location/$file_name, does NOT exist."
          echo "Nothing to update."
     fi

else
     echo "Directory, $location, does NOT exist."
     echo "Nothing to update."
fi
```

检查文件

```bash
#!/bin/bash
# Check if object exists and is a directory or a file

object_name=$HOME
echo
echo "The object being checked: $object_name"
echo

if [ -e $object_name ]
then
     echo "The object, $object_name, does exist,"
     #
     if [ -f $object_name ]
     then
          echo "and $object_name is a file."
     #
     else
          echo "and $object_name is a directory."
     fi

else
     echo "The object, $object_name, does NOT exist."
fi
```

检查是否可读

```bash
#!/bin/bash
# Check if you can read a file

pwfile=/etc/shadow
echo
echo "Checking if you can read $pwfile..."

# Check if file exists and is a file.

if [ -f $pwfile ]
then
     # File does exist. Check if can read it.
     
     if [ -r $pwfile ]
     then
          echo "Displaying end of file..."
          tail $pwfile
     
     else
          echo "Sorry, read access to $pwfile is denied."
     fi

else
     echo "Sorry, the $pwfile file does not exist."
fi
```

检查空文件

```bash
#!/bin/bash
# Check if a file is empty

file_name=$HOME/sentinel
echo
echo "Checking if $file_name file is empty..."
echo 

# Check if file exists and is a file.

if [ -f $file_name ]
then
     # File does exist. Check if it is empty.
     
     if [ -s $file_name ]
     then
          echo "The $file_name file exists and has data in it."
          echo "Will not remove this file."
     
     else
          echo "The $file_name file exits, but is empty."
          echo "Deleting empty file..."
          rm $file_name
     fi

else
     echo "The $file_name file does not exist."
fi
```

检查是否可写

```bash
#!/bin/bash
# Check if a file is writable

item_name=$HOME/sentinel
echo
echo "Checking if you can write to $item_name..."

# Check if file exists and is a file.

if [ -f $item_name ]
then
     # File does exist. Check if can write to it.
     
     if [ -w $item_name ]
     then
          echo "Writing current time to $item_name"
          date +%H%M >> $item_name
     
     else
          echo "Sorry, write access to $item_name is denied."
     fi

else
     echo "Sorry, the $item_name does not exist"
     echo "or is not a file."
fi
```

检查文件是否可以执行

```bash
#!/bin/bash
# Check if you can run a file

item_name=$HOME/scripts/can-I-write-to-it.sh
echo
echo "Checking if you can run $item_name..."

# Check if file is executable.

if [ -x $item_name ]
then
     echo "You can run $item_name."
     echo "Running $item_name..."
     $item_name

else
     echo "Sorry, you cannot run $item_name."
fi
```

检查所有权

```bash
#!/bin/bash
# Check if you own a file

if [ -O /etc/passwd ]
then
     echo "You are the owner of the /etc/passwd file."

else
     echo "Sorry, you are NOT /etc/passwd file's owner."
fi
```

检查默认属组关系

```bash
#!/bin/bash
# Compare file and script user's default groups

if [ -G $HOME/TestGroupFile ]
then
     echo "You are in the same default group as"
     echo "the $HOME/TestGroupFile file's group."

else
     echo "Sorry, your default group and $HOME/TestGroupFile"
     echo "file's group are different."

fi
```

检查文件日期

```bash
#!/bin/bash
# Compare two file's creation dates/times

if [ $HOME/Downloads/games.rpm -nt $HOME/software/games.rpm ]
then
     echo "The $HOME/Downloads/games.rpm file is newer"
     echo "than the $HOME/software/games.rpm file." 

else
     echo "The $HOME/Downloads/games.rpm file is older"
     echo "than the $HOME/software/games.rpm file." 

fi
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## 复合条件测试

if-then 语句允许使用布尔逻辑将测试条件组合起来。可以使用以下两种布尔运算符。 

-  [ condition1 ] && [ condition2 ]
-  [ condition1 ] || [ condition2 ]

```bash
#!/bin/bash
# Testing an AND Boolean compound condition 

if [ -d $HOME ] && [ -w $HOME/newfile ]
then
     echo "The file exists and you can write to it."
else
     echo "You cannot write to the file."
fi
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## if-then的高级特性

bash shell 还提供了 3 个可在 if-then 语句中使用的高级特性。 

- 在子 shell 中执行命令的单括号。
- 用于数学表达式的双括号。
- 用于高级字符串处理功能的双方括号。

使用单括号`(command)`

```bash
#!/bin/bash
# Testing a single parentheses condition 

echo $BASH_SUBSHELL

if (echo $BASH_SUBSHELL)
then
     echo "The subshell command operated successfully."
else
     echo "The subshell command was NOT successful."
fi
```

> 当你在 if test 语句中使用进程列表(参见第 5 章)时，可能会出现意料之外的结果。 哪怕进程列表中除最后一个命令之外的其他命令全都失败，子 shell 仍会将退出状态码设 为 0，then 部分的命令将得以执行。

使用双括号`(( expression ))`

expression 可以是任意的数学赋值或比较表达式。除了 test 命令使用的标准数学运算符

| 符号  | 描述       |
| :---- | :--------- |
| val++ | 后增       |
| val-- | 后减       |
| ++val | 先增       |
| --val | 先减       |
| !     | 逻辑求反   |
| ～    | 位求反     |
| **    | 幂运算     |
| <<    | 左位移     |
| >>    | 右位移     |
| &     | 位布尔 AND |
| \|    | 位布尔OR   |
| &&    | 逻辑AND    |
| \|\|  | 逻辑OR     |

```bash
#!/bin/bash
# Testing a double parentheses command 

val1=10

if (( $val1 ** 2 > 90 ))
then
     (( val2 = $val1 ** 2 ))
     echo "The square of $val1 is $val2,"
     echo "which is greater than 90."
fi
```

使用双方括号`[[ expression ]]`

expression 可以使用 test 命令中的标准字符串比较。除此之外，它还提供了 test 命令 所不具备的另一个特性——模式匹配。

> 双方括号在 bash shell 中运行良好。不过要小心，不是所有的 shell 都支持双方括号

```bash
#!/bin/bash
# Using double brackets for pattern matching 

if [[ $BASH_VERSION == 5.* ]]
then
     echo "You are using the Bash Shell version 5 series."
fi
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## case命令

```bash
#!/bin/bash
# Using a short case statement 

case $USER in
rich | christine)
     echo "Welcome $USER"
     echo "Please enjoy your visit.";;
barbara | tim)
     echo "Hi there, $USER"
     echo "We're glad you could join us.";;
testing)
     echo "Please log out when done with test.";;
*)
     echo "Sorry, you are not allowed here."
esac
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## 实战

检查系统中流行的包管理器

```bash
#!/bin/bash
# Checks system for popular package managers 

#################### User Introduction ######################
echo "########################################################"
echo 
echo "     This script checks your Linux system for popular"
echo "package managers and application containers, lists" 
echo "what's available, and makes an educated guess on your"
echo "distribution's base distro (Red Hat or Debian)."
echo
echo "#######################################################"

##################### Red Hat Checks #######################

echo 
echo "Checking for Red Hat-based package managers &" 
echo "application containers..."

if (which rpm &> /dev/null)
then
     item_rpm=1
     echo "You have the basic rpm utility."
else
     item_rpm=0
fi

if (which dnf &> /dev/null)
then
     item_dnfyum=1
     echo "You have the dnf package manager."
elif (which yum &> /dev/null)
then
     item_dnfyum=1
     echo "You have the yum package manager."
else
     item_dnfyum=0
fi

if (which flatpak &> /dev/null)
then
     item_flatpak=1
     echo "You have the flatpak application container."
else
     item_flatpak=0
fi

redhatscore=$[$item_rpm + $item_dnfyum + $item_flatpak]

##################### Debian Checks #######################
echo 
echo "Checking for Debian-based package managers &" 
echo "application containers..."

if (which dpkg &> /dev/null)
then
     item_dpkg=1
     echo "You have the basic dpkg utility."
else
     item_dpkg=0
fi

if (which apt &> /dev/null)
then
     item_aptaptget=1
     echo "You have the apt package manager."
elif (which apt-get &> /dev/null)
then
     item_aptaptget=1
     echo "You have the apt-get/apt-cache package manager."
else
     item_aptaptget=0
fi

if (which snap &> /dev/null)
then
     item_snap=1
     echo "You have the snap application container."
else
     item_snap=0
fi

debianscore=$[$item_dpkg + $item_aptaptget + $item_snap]

##################### Determine Distro #######################
echo
if [ $debianscore -gt $redhatscore ]
then
   echo "Most likely your Linux distribution is Debian-based."
elif [ $redhatscore -gt $debianscore ]
then
   echo "Most likely your Linux distribution is Red Hat-based."
else
   echo "Unable to determine Linux distribution base."
fi
echo
#############################################################
exit 
```

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)

## 小结

结构化命令允许改变 shell 脚本的正常执行流程。最基础的结构化命令是 if-then 语句。该 语句允许你评估命令并根据该命令的结果来执行其他命令。

你也可以扩展 if-then 语句，加入一组当指定命令失败后由 bash shell 执行的命令。仅在测 试命令返回非 0 退出状态码时，if-then-else 语句才允许执行这些命令。

你还可以使用 elif 语句将多个 if-then-else 语句组合起来。elif 等同于 else if，会 在测试命令失败时提供额外的检查。

在多数脚本中，你可能希望测试一种条件而不是命令，比如数值、字符串内容、文件或目录 的状态。test 命令为你提供了测试所有这些条件的简单方法。如果条件为真，test 命令会为 if-then 语句产生退出状态码 0。如果条件为假，test 命令则会为 if-then 语句产生非 0 的退 出状态码。

方括号是与 test 命令同义的特殊 bash 命令。你可以在 if-then 语句中将测试条件放入方 括号中来测试数值、字符串和文件条件。

双括号命令会使用另一批运算符执行高级数学运算。你可以在双方括号中进行字符串模式 匹配。

最后，本章讨论了 case 命令。该命令是执行多个 if-then-else 命令的便捷方式，它会 参照一个值列表来检查单个变量的值

---
下一篇：[练习3 更多的结构化命令](../practice-03/)，上一篇：[练习1 构建基础脚本](../practice-01/)，[目录](#结构化命令)｜[首页](../README.md)