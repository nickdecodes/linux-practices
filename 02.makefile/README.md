# 介绍
[官网](https://make.mad-scientist.net/) | [官方文档](https://www.gnu.org/software/make/manual/make.html)  

什么是Makefile？或许很多Winodws的程序员都不知道这个东西，因为那些Windows的IDE都为你做了这个工作，但我觉得要做一个好的和professional的程序员，Makefile还是要懂。这就好像现在有这么多的HTML的编辑器，但如果你想成为一个专业人士，你还是要了解HTML的标识的含义。特别在Unix下的软件编译，你就不能不自己写Makefile了，会不会写Makefile，从一个侧面说明了一个人是否具备完成大型工程的能力。

因为，Makefile关系到了整个工程的编译规则。一个工程中的源文件不计数，其按类型、功能、模块分别放在若干个目录中，Makefile定义了一系列的规则来指定，哪些文件需要先编译，哪些文件需要后编译，哪些文件需要重新编译，甚至于进行更复杂的功能操作，因为Makefile就像一个Shell脚本一样，其中也可以执行操作系统的命令。

Makefile是一种用于自动化构建和编译软件项目的工具，它定义了一个项目中的源文件、目标文件、依赖关系和构建规则。通常，Makefile用于在Unix和类Unix系统中进行编译，但它也可以在Windows环境中使用，尤其是在跨平台开发中。

Makefile的主要目的是确保代码的正确编译和链接，以及在代码更改后只编译必要的部分，从而提高开发效率。下面是关于Makefile的一些重要概念：

1.  **目标（Target）**：在Makefile中，目标是要构建的文件或任务的名称。这可以是可执行文件、库文件、中间文件等。
2.  **依赖关系（Dependencies）**：每个目标通常依赖于一个或多个源文件或其他目标。依赖关系定义了构建目标所需的输入文件。
3.  **规则（Rules）**：规则定义了如何构建目标以及如何满足依赖关系。它包括命令和变量，用于执行编译、链接和其他构建任务。
4.  **变量（Variables）**：Makefile中可以定义变量，以便在多个规则和命令中共享值。这可以用于存储编译器选项、源文件列表等信息。
5.  **命令（Commands）**：在规则中，您可以指定执行构建任务的命令。这通常包括编译器命令、链接器命令和其他Shell命令。
6.  **默认目标（Default Target）**：Makefile可以指定一个默认目标，当您运行`make`命令而不指定目标时，它将构建默认目标。

编写一个良好的Makefile可以帮助开发者管理复杂的项目，确保只重新构建必要的文件，从而提高编译效率。Makefile还有助于跨平台开发，因为它提供了一种通用的构建方法，无论您是在Unix/Linux、macOS还是Windows上进行开发，都可以使用相同的Makefile进行构建。

虽然现代集成开发环境（IDE）通常会自动生成和处理Makefile，但了解Makefile的工作原理和编写它们的能力仍然对于程序员来说是有价值的，特别是在需要定制构建流程或处理复杂项目时。 Makefile是一个强大的工具，可以帮助您更好地管理和自动化软件项目的构建过程。

Makefile带来的好处就是——“自动化编译”，一旦写好，只需要一个make命令，整个工程完全自动编译，极大的提高了软件开发的效率。make是一个命令工具，是一个解释Makefile中指令的命令工具，一般来说，大多数的IDE都有这个命令，比如：Delphi的make，Visual C++的nmake，Linux下GNU的make。可见，Makefile都成为了一种在工程方面的编译方法。

现在详细讲述如何写Makefile的文章比较少，这是我想创建这个库以及相关文章的原因。当然，不同产商的make各不相同，也有不同的语法，但其本质都是在“文件依赖性”上做文章，这里，我仅对GNU的make进行讲述

在以下文档中，将以C/C++的源码作为我们基础，所以必然涉及一些关于C/C++的编译的知识，相关于这方面的内容，还请各位查看相关的编译器的文档。这里所默认的编译器是UNIX下的g++和gcc。

# 前期准备

1.  一台电脑 + 操作系统(linux[ubuntu | centos], mac), 个人常用的就是这些系统，如果你是windows的话，一些东西是通用的，出现异常情况请自行查找资料

2.  安装基础环境(vim, gcc, g++, make等)

    -    ubuntu

    
    ```bash
    # 安装Vim：
    sudo apt update
    sudo apt install vim
    # 安装GCC和g++：
    sudo apt install gcc g++
    # 安装Make工具：
    sudo apt install make
    ```
    
    -    centos
    
    
    ```bash
    # 安装Vim：
    sudo yum install vim
    # 安装GCC和g++：
    sudo yum install gcc gcc-c++
    # 安装Make工具：
    sudo yum install make
    ```

    -    mac
    
    
    ```bash
    # macOS通常已经预装了Vim，但你也可以通过Homebrew来安装：
    # 安装Homebrew（如果尚未安装）：
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    # 安装Vim：
    brew install vim
    # 安装Xcode Command Line Tools（这会包括GCC、g++和Make工具）：
    xcode-select --install
    ```

# 使用说明

1.  如果你在这方面已经是大佬了，我建议您可以简单看一下，查缺补漏，也可以给出您宝贵的意见
2.  如果你是一个小白，那么我们就通过下面的练习一起来研究一下Makefile吧  
- [练习1 理解编译的基本过程](./practice-01/)
- [练习2 创建基本的Makefile](./practice-02/)
- [练习3 Makefile之简单介绍](./practice-03/)
- [练习4 Makefile之显式规则](./practice-04/)
- [练习5 Makefile之配方规则](./practice-05/)
- [练习6 Makefile之使用变量](./practice-06/)
- [练习7 Makefile之条件部分](./practice-07/)
- [练习8 Makefile之使用函数](./practice-08/)
- [练习9 Makefile之运行参数](./practice-09/)
- [练习10 Makefile之隐式规则](./practice-10/)
- [练习11 Makefile之更新存档](./practice-11/)

# 参与贡献

-    nickdecodes@163.com
