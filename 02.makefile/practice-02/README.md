# 创建基本的Makefile 

- [温故知新](#温故知新)
- [优化准备](#优化准备)
- [创建Makefile文件](#创建makefile文件)
- [转化compile.sh内容](#转化compilesh内容)
- [完善Makefile内容](#完善makefile内容)

---
下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)

## 温故知新

- [练习1 理解编译的基本过程](../practice-01/)  

经过以上练习，我们大致了解了，源码编译的基本流程，有的人可能会说对于`练习1`只有一个原文件一行命令`g++ main.cpp`就结束了，
是的，日常几乎没有人去细扣这些编译的细节，正因为这样，我们才更应该去了解！  

在`练习1`的最后，我们使用了一个shell脚本去执行繁杂的操作，其实这也就是Makefile的初衷了，Makefile本质上也是shell，它的command中就是支持shell命令的，当然使用Makefile可以更加通用化，不然每人写一个编译脚本，  

大家还要去理解，那不烦死了。那么接下来让我们将`练习1`中的shell脚本过渡成一个Makefile。在这个过程中，我们将创建一个更灵活、可维护和通用的构建系统。

---
下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)

## 优化准备

还是这个main.cpp源文件

```cpp
/**
@Author  : nickdecodes
@Email   : 
@Usage   : 
@Filename: main.cpp
@DateTime: 2023/10/07 17:29
@Software: vscode
**/

#include <iostream>
using namespace std;


int main(int argc, char const *argv[]) {
    cout << "hello world" << endl;
    return 0;
}

```

直接编译还记得吧，`g++ main.cpp`

还是这个shell脚本**compile.sh**

```bash
# !/bin/bash

# 源文件和目标可执行文件的名称
SOURCE_FILE="main.cpp"
TARGET_EXECUTABLE="a.out"

# 编译器和编译选项
CXX="g++" 
CXXFLAGS="-Wall -g" 

# 预处理（Preprocessing）
echo "1. Preprocessing: $SOURCE_FILE -> ${SOURCE_FILE%.cpp}.i"
$CXX -E $SOURCE_FILE -o ${SOURCE_FILE%.cpp}.i

# 编译（Compiling）
echo "2. Compiling: ${SOURCE_FILE%.cpp}.i -> ${SOURCE_FILE%.cpp}.s"
$CXX $CXXFLAGS -S ${SOURCE_FILE%.cpp}.i -o ${SOURCE_FILE%.cpp}.s

# 汇编（Assembling）
echo "3. Assembling: ${SOURCE_FILE%.cpp}.s -> ${SOURCE_FILE%.cpp}.o"
$CXX $CXXFLAGS -c ${SOURCE_FILE%.cpp}.s -o ${SOURCE_FILE%.cpp}.o

# 链接（Linking）
echo "4. Linking: ${SOURCE_FILE%.cpp}.o -> $TARGET_EXECUTABLE"
$CXX $CXXFLAGS ${SOURCE_FILE%.cpp}.o -o $TARGET_EXECUTABLE

# 清理临时文件
# echo "5. Cleaning up temporary files"
# rm -f ${SOURCE_FILE%.cpp}.i ${SOURCE_FILE%.cpp}.s ${SOURCE_FILE%.cpp}.o ${TARGET_EXECUTABLE}

echo "Compilation completed!"
```

---
下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)

## 创建Makefile文件

接下来我们新建一个文件，名字叫做makefile 或者Makefile，在这里我们使用Makefile

```bash
touch Makefile
```
---
下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)

## 转化compile.sh内容

一个基本的 Makefile 由以下形式的格式构成，Makefile称之为`规则`：

```makefile
target ... : prerequisites ...
    recipe
    ...
    ...
```

其中

- target - 目标文件, 可以是 Object File, 或者是可执行文件, 也可以是要执行的操作的名称，
- prerequisites - 生成 target 所需要的文件或者目标， 通常取决于多个文件。我们称之为依赖
- recipe - 配方是一个Shell命令(任意的shell命令)，用于构建目标 , makefile中的命令必须以 [tab] 开头

那么，规则解释了如何以及何时重新制作作为特定规则的目标的某些文件。` make`根据创建或更新`target`的`prerequisites`执行命令。规则还可以解释如何以及何时执行操作。

这次我们主要是展示一下makefile的功能，如果只是写一个最基础的，我们直接将compile.sh的内容转化一下就好啦，转化之后内容如下

```makefile
main : main.cpp
    g++ -Wall -g main.cpp
```

这就是最简单的makefile了, 接下来我们可以在相同目录下执行`make`, 你就可以看到编译输出，以及编译结果啦

不过这只是一个非常简略的Makefile，还有很多地方需要优化。

---
下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)

## 完善Makefile内容

上面我们所有写的Makefile着实太过精简，根本就体现不出Makefile的全貌，接下来我们就对当下的文件情况，去进一步完善一下，中间可能会有一些不理解的地方，放心后面会一一介绍的

首先我们把之前的Makefile备份一下，就叫做`Makefile_simple`吧

```bash
cp Makefile Makefile_simple
```

我暂时不会直接说该怎么写，我们就作为一个开发者而言，看有什么地方需要优化！

1.  首先`g++ -Wall -g`我们现在是硬编码去写的，一旦出现更改，我们就得改一次，现在我们就只有一个`main.cpp`也还好，也就改一次就完事了，但是要是多了怎么办，复制粘贴大法吗？大家一定会想到模块化对吧！

    那么怎么去模块化呢，我们在`compile.sh`中也说明了，`g++`是指编译器、`-Wall -g`是指编译参数，👌那我们就命名两个变量就可以了，其它地方就使用命名的变量，万一改变值，也就是在定义的地方改变一次就可以了，实现如下

    ```makefile
    CXX = g++ # 编译命令
    CXXFLAGS = -Wall -g # 编译参数
    
    main: main.cpp
        $(CXX) $(CXXFLAGS) main.cpp
    ```

    >   其中注释是像shell一样以`#`开头的文本
    >
    >   `$(CXX)` 是引用变量的格式
    >
    >   看来`Makefile`人家也想到了模块化，我们直接就可以使用相应的语法了，这样我们通过思考去深刻记忆也是更加深刻的

2.  接下来我们看看还有什么地方看着不太舒服呢？不知道`main.cpp`能不能继续抽离出来呢，同样多文件的情况下，改起来也是挺麻烦的，那我们在优化一下吧

    ```makefile
    CXX = g++ # 编译命令
    CXXFLAGS = -Wall -g # 编译参数
    OBJS = main.o # 生成对象
    
    # 链接过程
    main : $(OBJS)
        $(CC) $(CFLAGS) $(OBJS) -o test
    
    # 编译过程
    main.o: main.cpp
        $(CXX) -c $(CXXFLAGS) main.cpp
    ```

    现在我们将编译和链接拆解开了，有人肯定说这不是改复杂了吗？其实这是方便理解的一个过渡，不然接下来肯定更加不理解了，你不信我们就一步到位看看

    ```makefile
    CXX = g++ # 编译命令
    CXXFLAGS = -Wall -g # 编译参数
    OBJS = main.o # 生成对象
    
    all:
        $(CXX)  -c $(CXXFLAGS) *.cpp # 编译所有.cpp文件省去链接文件过程
        $(CXX) $(CXXFLAGS) $(OBJS) -o test # 直接生成对象文件
    ```
    
    这下简单了吧，连`main.cpp`都不用写了，其实就是一种shell的缺省匹配`*.cpp`是匹配所有后缀为`.cpp`的文件
    


3.   至此，好像也没什么了吧！但是细心的一定会发现，当你执行一次`make`之后，再次执行`make`，会提示你不会做任何更改。有的人肯定会觉得这么反人类吗？还不允许重复执行了？其实人家`Makefile`底层有判断是否需要执行或者更新的逻辑，相比来说，其实是更加注重了效率，不过对于我们就想看效果的，我们也可以加一些清理操作，顺便清理一下生成的垃圾，然后在从头编译就好了

     ```makefile
     CXX = g++ # 编译命令
     CXXFLAGS = -Wall -g # 编译参数
     OBJS = main.o # 生成对象
     
     .PHONY: clean # 伪目标 通常用于clean操作
     
     all:
        $(CXX)  -c $(CXXFLAGS) *.cpp # 编译所有.cpp文件省去链接文件过程
        $(CXX) $(CXXFLAGS) $(OBJS) -o main # 直接生成对象文件
         
     clean:
        rm -rf *.o main
     ```

     这样我们可以执行`make clean`就可以清除生成的文件，想要再次生成就在执行一遍`make`，是不是很方便

---

下一篇：[练习3 Makefile之简单介绍](../practice-03/)，上一篇：[练习1 理解编译的基本过程](../practice-01/)，[目录](#创建基本的makefile)｜[首页](../README.md)
