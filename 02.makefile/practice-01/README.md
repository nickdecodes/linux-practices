# 理解编译的基本过程

- [预处理(Preprocessing)](#预处理preprocessing)
- [编译(Compiling)](#编译compiling)
- [汇编(Assembling)](#汇编assembling)
- [链接(Linking)](#链接linking)
- [gcc/g++编译器参数](#gccg编译器参数)
- [简单分析实践](#简单分析实践)
    - [预处理实践](#预处理实践)
    - [编译实践](#编译实践)
    - [汇编实践](#汇编实践)
    - [链接实践](#链接实践)
    - [过程脚本](#过程脚本)

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

C/C++编译的过程可以分为多个阶段，包括预处理、编译、汇编和链接。以下是C++编译的主要步骤：

## 预处理(Preprocessing)

- 在这个阶段，C++预处理器（通常是 cpp 命令）会处理源代码文件。主要任务如下
- 移除注释：删除源代码中的注释。  
- 处理预处理指令：执行以 # 开头的预处理指令，如 #include 用于包含头文件，#define 用于宏定义等。  
- 展开宏：替换源代码中定义的宏为其实际内容。  
- 展开头文件：将头文件的内容插入到源文件中。  
- 结果是一个经过预处理的源文件。(通常以`.i`为扩展名)

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

## 编译(Compiling)

- 在这个阶段，编译器（如 g++ 或 clang++）将预处理后的源文件编译成汇编语言（Assembly）代码。
- 编译器会进行词法分析、语法分析和语义分析，生成中间表示（如抽象语法树）。
- 检查语法错误和类型错误。
- 输出一个或多个汇编文件，每个源文件通常对应一个汇编文件。(通常以`.s`为扩展名)

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

## 汇编(Assembling)

- 汇编器（如 as）将汇编语言代码转换为目标机器代码。
- 汇编过程包括将汇编指令翻译成机器指令、解析数据和指令标签、生成可执行的目标文件。
- 结果是一个或多个目标文件（通常以 .o 或 .obj 为扩展名）。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

## 链接(Linking)

- 在最后一个阶段，链接器（如 ld）将所有目标文件以及必要的库文件连接在一起，生成最终的可执行文件。
- 链接器会解析目标文件中的符号引用，将它们解析为实际的内存地址。
- 合并目标文件中的代码段和数据段。
- 处理库文件，将它们链接到可执行文件中。
- 生成可执行文件，通常具有 .exe（在Windows上）或没有扩展名（在Unix/Linux上）等可执行文件扩展名。

这些是C++编译的基本步骤。每个步骤都有特定的工具和选项，以及与编译器和操作系统相关的细节。在复杂的项目中，可能会涉及更多的细节，如生成共享库、符号解析、优化等。不同的编译器和操作系统可能有一些差异，但上述步骤是通用的。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

## gcc/g++编译器参数

- 基本用法

```bash
gcc/g++ source_file.c -o output_executable
```
> source_file.c: 源代码文件。  
> -o output_executable: 指定输出的可执行文件名称。

- 编译选项
> -c: 仅编译不链接，生成目标文件。  
> -E: 只运行预处理器，不进行编译。

- 优化选项
> -O0, -O1, -O2, -O3: 启用不同级别的优化，-O0 表示没有优化，-O3 表示最高级别的优化。

- 调试选项
> -g: 生成调试信息，以便调试器使用。

- 预处理器定义
> -Dname[=value]: 定义宏。  
> -Uname: 取消宏定义。

- C++特定选项
> -std=c++11, -std=c++14, -std=c++17, -std=c++20: 指定 C++ 标准。

- 链接选项：
> -l library: 指定链接时要使用的库。  
> -L path: 指定库文件的搜索路径。

- 更多选项可以查看man手册
```bash
man gcc
man g++
man clang
man clang++
```

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

## 简单分析实践

这是一个main.cpp源文件

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

对于单个文件的编译运行，我猜测平时大家都是这么用的`g++ main.cpp` 然后执行`./a.out`对吧，那其中的细节流程到底是怎样的呢？

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

### 预处理实践

```bash
g++ -E main.cpp -o main.i
```

这行命令的作用于对一个C++源代码文件 (main.cpp) 进行预处理，并将预处理输出保存到名为 main.i 的文件中。以下是对这个命令的解释：

> g++：这是GNU编译器集合的C++编译器。  
> -E：此选项告诉编译器仅执行预处理阶段，停在编译之前。预处理包括宏展开、文件包含和条件编译。它对于生成中间的预处理源文件以进行调试或检查非常有用。  
> main.cpp：这是要预处理的输入源文件。  
> -o main.i：命令的这一部分指定了预处理代码的输出文件名。在这种情况下，预处理后的代码将保存到名为 main.i 的文件中。

运行此命令后，您将获得一个 main.i 文件，其中包含了 main.cpp 的预处理版本。此文件将具有所有宏展开和任何包含的文件合并到一个文件中，使得在编译的这个阶段更容易检查代码。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

### 编译实践

```bash
g++ -Wall -g -S main.i -o main.s
```

这个命令是将预处理后的源文件 main.i 编译成汇编文件 main.s 的命令。以下是对这个命令的解释：

> g++: 这是GNU C++编译器的命令。  
> -Wall: 这个选项告诉编译器生成所有警告信息，以提高代码质量。  
> -g: 这个选项告诉编译器生成可执行文件中的调试信息，以便在调试时能够查看源代码。  
> -S: 这个选项告诉编译器只生成汇编代码文件而不进行后续的汇编和链接步骤。  
> main.i: 这是输入文件的名称，它是预处理后的源文件，通常是 .i 扩展名。  
> -o main.s: 这是输出文件的名称，它是生成的汇编文件，通常是 .s 扩展名。  

通过运行这个命令，您会将预处理后的源文件 main.i 编译成汇编文件 main.s。汇编文件 main.s 包含了源代码的汇编语言表示，它是接下来汇编和链接步骤的中间文件。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

### 汇编实践

```bash
g++ -Wall -g -c main.s -o main.o
```

这个命令是将汇编文件 main.s 编译成目标对象文件 main.o 的命令。以下是对这个命令的解释：

> g++: 这是GNU C++编译器的命令。  
> -Wall: 这个选项告诉编译器生成所有警告信息，以提高代码质量。  
> -g: 这个选项告诉编译器生成可执行文件中的调试信息，以便在调试时能够查看源代码。  
> -c: 这个选项告诉编译器只进行编译，而不进行链接。它将源文件编译成目标对象文件。  
> main.s: 这是输入文件的名称，它是汇编文件，通常是 .s 扩展名。  
> -o main.o: 这是输出文件的名称，它是生成的目标对象文件，通常是 .o 扩展名。  

通过运行这个命令，您将汇编文件 main.s 编译成目标对象文件 main.o。目标对象文件包含了与汇编文件相对应的机器代码表示，它是链接到最终可执行文件的一个组成部分。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)

### 链接实践

```bash
g++ -Wall -g main.o -o a.out
```

这个命令是将目标对象文件 main.o 链接成可执行文件 main 的命令。以下是对这个命令的解释：

> g++: 这是GNU C++编译器的命令。  
> -Wall: 这个选项告诉编译器生成所有警告信息，以提高代码质量。  
> -g: 这个选项告诉编译器生成可执行文件中的调试信息，以便在调试时能够查看源代码。  
> main.o: 这是目标对象文件的名称，它是之前编译生成的。  
> -o a.out: 这是输出文件的名称，它是生成的可执行文件的名称。  

通过运行这个命令，您将目标对象文件 main.o 链接成了一个名为 a.out 的可执行文件。这个可执行文件包含了程序的机器代码，可以在命令行中运行。

这个命令完成了C++程序的最后一步，生成了可执行文件，您可以通过 ./a.out 来运行它。

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)../README.md)

### 过程脚本
为了更方便编译，我们写一个shell脚本吧。  执行了C++编译流程的每个步骤，包括预处理、编译、汇编和链接。

您可以将此脚本保存到文件（例如compile.sh）, 最后，运行`bash compile.sh`来执行编译过程。在每个步骤后，  脚本会输出一条消息，以指示当前所处的编译阶段。完成后，您将在当前目录中得到a.out可执行文件。

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
> 可能对shell不太了解的，不理解`${SOURCE_FILE%.cpp}`是什么意思，这其实是一个Shell参数扩展。它获取$SOURCE_FILE变量的值，使用%运算符删除.cpp文件扩展名

这样我们就可以直接执行`bash compile.sh`去执行我们的处理流程了

至此编译过程的简单分析就到此结束了

---
下一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#理解编译的基本过程)｜[首页](../README.md)