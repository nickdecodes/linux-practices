# Makefile之简单介绍

- [温故知新](#温故知新)
- [组成部分](#组成部分)
- [基本结构](#基本结构)
- [简单示例](#简单示例)
- [包含其它](#包含其它)
- [运行机制](#运行机制)
- [使用变量](#使用变量)
- [自动推导](#自动推导)
- [简约风格](#简约风格)
- [目录清理](#目录清理)

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 温故知新

-   [练习1 理解编译的基本过程](../practice-01/)  
-   [练习2 创建基本的Makefile](../practice-02/)

在`练习2`中我们看见了一个基本的`Makefile`，当然它还不是完善的，并且或多或少有一些不理解的地方，在本文中将会做一个简单的介绍，算是一个综述吧，介绍一下`Makefile`的整体面貌，以及有哪些我们常见的功能，具体的分析我们会再之后的练习中再详细练习

首先我们需要一个名为`Makefile`的文件来告诉`make`要做什么。大多数情况下，`Makefile`告诉`make`如何编译和链接程序。

make重新编译时，每个更改的源文件都必须重新编译。如果头文件已更改，则必须重新编译包含该头文件的每个源文件才能安全。每次编译都会生成一个与源文件相对应的目标文件。最后，如果重新编译了任何源文件，则所有目标文件（无论是新创建的还是从先前编译中保存的）都必须链接在一起以生成新的可执行对象。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 组成部分

`Makefile`包含五种内容：显式规则、 隐式规则、变量定义、指令和注释。

- 显示规则：规则的目标说明何时以及如何重新处理一个或多个文件。目标的先决条件列出了目标所依赖的其他文件，并且还可能提供用于创建或更新目标的指令。  

- 隐式规则：规定了何时以及如何根据文件名重新创建一类文件。它描述了目标如何依赖于名称与目标相似的文件，并给出了创建或更新此类目标的方法。  

- 变量定义：是一行指定变量的文本字符串值，该变量可以稍后替换到文本中。

- 指令：是在读取`Makefile`时执行一些特殊操作的操作。这些包括：读取另一个`Makefile`、决定（基于变量的值）是否使用或忽略`Makefile`的一部分、从包含多行的字符串定义变量

- 注释：'#' 在`Makefile`一行中的开始。它和该行的其余部分将被忽略，除了尾部反斜杠未被另一个反斜杠转义将在多行中继续注释。仅包含注释的行（前面可能有空格）实际上是空白的，并且会被忽略。如果您想要一个文字 #，使用反斜杠对其进行转义（例如，\#）。注释可以出现在 Makefile 中的任何行上，尽管在某些情况下会进行特殊处理。

    > 您不能在变量引用或函数调用中使用注释：变量引用或函数调用中的任何实例都#将按字面意思处理（而不是作为注释的开头）。  
    > 配方中的注释会传递到 shell，就像任何其他配方文本一样。shell 决定如何解释它：这是否是注释取决于 shell。 
    > 在define指令中，在定义变量期间不会忽略注释，而是在变量值中保持完整。当变量展开时，它们将被视为make注释或配方文本，具体取决于评估变量的上下文。  

以上5种内容会在之后的练习中逐个练习

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 基本结构

一个简单的 Makefile 由以下形式的格式构成，Makefile称之为`规则`：它由一系列规则组成，每个规则定义了一个或多个目标、先决条件和配方

```makefile
target ... : prerequisites ...
    recipe
    ...
    ...
```

其中

- target - 目标文件, 可以是 Object File, 或者是可执行文件, 也可以是要执行的操作的名称，
- prerequisites - 生成 target 所需要的文件或者目标， 通常取决于多个文件。我们称之为先决条件，或者依赖关系
- recipe - make需要执行的命令 (任意的shell命令), Makefile中的命令必须以 [tab] 开头，可以用`.RECIPEPREFIX`代替 [tab] 

那么，规则解释了如何以及何时重新制作作为特定规则的目标的某些文件。 make根据创建或更新`target`的`prerequisites`执行配方。规则还可以解释如何以及何时执行操作。

一个 Makefile 可以包含除规则之外的其他文本，但一个简单的 Makefile 只需包含规则。规则可能看起来比此模板中显示的要复杂一些，但或多或​​少都符合模式。

`Makefile`使用**基于行**的语法，其中换行符是特殊的，标记语句的结束。make对语句行的长度没有限制，最多可达计算机的内存量。在`Makefile`中，可以使用反斜杠 \ 来将长命令行分割成多行，以提高可读性。例如：

```makefile
target:
    command_part1 \
    command_part2 \
    command_part3
```

在这个例子中，command_part1、command_part2 和 command_part3 是一个长命令的不同部分，它们通过反斜杠 \ 分隔成多行。

>   请注意：反斜杠 \ 必须放在命令的末尾，表示该行命令在下一行继续。命令部分可以使用缩进（通常是 Tab 键）。换行后的命令行必须以与第一行相同的缩进开始。这样做可以帮助保持 Makefile 的可读性，尤其是在涉及复杂的命令行时。

举个例子，如果你有一个需要在编译时执行的长命令，你可以将其分割成多行，使其更易于阅读：

```makefile
all:
    gcc -o my_program \
        file1.cpp \
        file2.cpp \
        file3.cpp
```

`Makefile`中的一个小技巧，当你需要分割一行但又不想添加额外的空格时可以使用。你可以用一种特殊的字符序列代替通常的反斜杠\：

```makefile
var := one$\
    word
```

在 make 处理后，它会移除反斜杠\换行，并将接下来的一行合并成一个空格，得到：`var := one$word` 接着，make 执行变量扩展。在这个例子中，变量引用 $ 指的是一个名字为" "（空格）的单字符变量，但实际上这个变量并不存在。因此，它会扩展为空字符串，最终得到相当于：`var := oneword` 这种技巧让你能够在保持可读性的同时分割长行，而不会引入额外的空格到最终的变量值中。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 简单示例
在本文中，我们将讨论一个简单的`Makefile`，它在`练习2`的基础上加了一个`hello.cpp`和`hello.h`。

-   `main.cpp`

    ```cpp
    /**
    @Author  : nickdecodes
    @Email   : 
    @Usage   : 
    @Filename: hello.cpp
    @DateTime: 2023/10/07 20:02
    @Software: vscode
    **/
    
    #include <iostream>
    #include "hello.h"
    using namespace std;
    
    Hello::Hello() {
        cout << "hello" << endl;
        return ;
    }
    
    Hello::~Hello() {
        cout << "bye bye" << endl;
        return ;
    }
    ```

-   `hello.cpp`

    ```cpp
    /**
    @Author  : nickdecodes
    @Email   : 
    @Usage   : 
    @Filename: hello.cpp
    @DateTime: 2023/10/07 20:02
    @Software: vscode
    **/
    
    #include <iostream>
    #include "hello.h"
    using namespace std;
    
    Hello::Hello() {
        cout << "hello" << endl;
        return ;
    }
    
    Hello::~Hello() {
        cout << "bye bye" << endl;
        return ;
    }
    ```

-   `hello.h`

    ```cpp
    /**
    @Author  : nickdecodes
    @Email   : 
    @Usage   : 
    @Filename: hello.h
    @DateTime: 2023/10/07 20:02
    @Software: vscode
    **/
    
    #ifndef _HELLO_H
    #define _HELLO_H
    
    class Hello {
    public:
        Hello();
        ~Hello();
    };
    
    #endif
    ```

通常，你应该将你的 Makefile 命名为 makefile 或者 Makefile。（官网推荐使用 Makefile，因为它在目录列表的开头显眼地出现，紧邻其他重要的文件如 README。）第一个被检查的名字 GNUmakefile，在大多数情况下并不建议使用。  只有当你有一个特定于 GNU make 的 Makefile，并且其他版本的 make 无法理解时，你才应该使用这个名字。其他的 make 程序会寻找 makefile 和 Makefile，但不会找 GNUmakefile。

如果 make 找不到这些名字中的任何一个，它就不会使用任何 Makefile。这时你必须指定一个目标并附带相应的命令参数，make 将尝试使用它内建的隐式规则来重新构建目标。

如果你想使用一个非标准的名字来命名你的 Makefile，你可以使用 -f 或 --file 选项指定 Makefile 的名字。参数 -f name 或 --file=name 告诉 make 读取文件名作为 Makefile。  

```bash
make -f Makefile
```

如果你使用了多个 -f 或 --file 选项，你可以指定多个 Makefiles。所有的 Makefiles 实际上会按照指定的顺序拼接在一起。默认的 Makefile 名字 GNUmakefile、makefile 和 Makefile 在你明确指定 -f 或 --file 时不会被自动检查。

在此示例`Makefile`中，hello源文件包括头文件

```makefile
main : main.o hello.o
	g++ main.o hello.o -o main

main.o : main.cpp
	g++ -c main.cpp

hello.o : hello.cpp hello.h
	g++ -c hello.cpp

clean:
	rm -rf *.o main
```

>   `prerequisites`也就是依赖过多时，我们可以使用反斜杠`\`将长行分成两行，执行时就像是使用一长行，但更容易阅读

接下来你可以通过执行`make`来执行`Makefile`内容，最后生成可执行的文件对象

```bash
make
```

如果想要重新编译，并要清理之前编译的多余文件，可以在终端目录下执行如下命令行

```bash
make clean
```

在示例 Makefile 中，target包括可执行文件`main`和`*.o`文件。每个`target`都有相应的依赖文件。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 包含其它

include 指令告诉 make 在继续之前暂停读取当前的 Makefile 并读取一个或多个其他的 Makefile。这个指令是在 Makefile 中的一行，看起来像这样：`include 文件名…`  

文件名可以包含 shell 文件名模式。如果文件名是空的，那么将不会包含任何内容，并且不会打印错误信息。

在这一行的开始，允许存在额外的空格并会被忽略，但第一个字符不能是制表符（或者 .RECIPEPREFIX 的值）——如果一行以制表符开始，它会被认为是一个配方行（recipe line）。  

在 include 和文件名之间，以及文件名之间需要有空白；额外的空白会在这里和指令的末尾被忽略。在行的末尾允许以 # 开头的注释。如果文件名中包含任何变量或函数引用，它们会被展开。

例如，我们有2个 .cpp 文件，分别是 main.cpp 和 hello.cpp，并且 $(bar) 展开为 bash，那么以下表达式：

```makefile
include main *.cpp $(bar)
# 等同于：
include main main.cpp hello.cpp bash
```

当 make 处理一个 include 指令时，它会暂停读取当前的 Makefile，并依次从列出的每个文件中读取内容。完成后，make 会继续读取当前的 Makefile。

在使用 include 指令的一个场合是当需要多个程序在各自的目录中使用相同的变量定义时。另一个使用场合是当你想要自动生成源文件的先决条件时；这些先决条件可以放在一个被主 Makefile 包含的文件中。这个做法通常比传统的在主 Makefile 末尾追加先决条件的做法更清晰。

如果环境变量 `MAKEFILES` 被定义了，那么 make 将把它的值视为一个由空格分隔的 Makefile 名称列表，这些 Makefile 将在其它 Makefile 之前被读取。这与 include 指令的工作方式很相似：各个目录会被搜索以找到这些文件。此外，从这些 Makefile 中（或者被它们所包含的 Makefile 中）不会取得默认目标，而且如果在 MAKEFILES 中列出的文件找不到也不会产生错误。

`MAKEFILES` 的主要用途是在递归调用 make 之间进行通信。通常情况下，在顶层调用 make 之前设置环境变量是不可取的，因为最好不要从外部修改 Makefile。然而，如果你在没有特定 Makefile 的情况下运行 make，那么 `MAKEFILES` 中的一个 Makefile 可以做一些有用的事情，以帮助内建的隐式规则更好地工作，比如定义搜索路径。

一些用户可能会诱惑地在登录时自动在环境中设置 `MAKEFILES`，并编写程序使得 Makefile 预期会执行这个操作。这是一个非常糟糕的想法，因为这样的 Makefile 在被其他人运行时将无法正常工作。最好的做法是在 Makefile 中显式地使用 include 指令。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 运行机制

make 解析 Makefiles 的过程是逐行进行的，并且分为`读入阶段`和`目标更新阶段`，它按照以下步骤进行解析：

1.  读取一个完整的逻辑行，包括反斜杠转义行。
2.  移除注释。
3.  如果该行以规则前缀字符开始且我们处于规则上下文中，将该行添加到当前规则中，并读取下一行。
4.  展开出现在立即展开上下文中的行中的元素。
5.  扫描该行以查找分隔符字符，比如 ‘:’ 或 ‘=’，以确定该行是宏赋值还是规则。
6.  内部化生成的操作并读取下一行。

这个过程的一个重要结果是，如果宏只有一行，它可以展开为完整的规则。这将有效：

```makefile
myrule = target : ; echo built

$(myrule)
```

然而，以下代码将不起作用，因为 make 在展开后不会重新拆分行：

```makefile
define myrule
target:
        echo built
endef

$(myrule)
```

上述 Makefile 的结果是定义一个目标 'target'，其前提条件是 'echo' 和 'built'，就好像 Makefile 包含了 'target: echo built'，而不是一个带有规则和配方的规则。展开后仍然存在于行中的换行符将被视为正常的空白字符。要正确展开多行宏，您必须使用 eval 函数：这将导致 make 解析器在展开的宏结果上运行。之后我们再详细介绍

当`target`是文件时，如果其任何依赖文件发生更改，则需要重新编译或重新链接。此外，应首先更新自动生成的任何依赖条件。

包含`target`和`依赖文件`的每一行后面可能有一个`command`。这些`command`说明了如何更新目标文件。制表符（或变量指定的任何字符 .RECIPEPREFIX；）必须出现在`command`中每一行的开头，以将`command`与`Makefile`中的其他行区分开来。 

目标`clean`不是一个文件，而只是一个操作的名称, 我们称之为`伪目标`，`clean` 不是任何其他规则的先决条件。  
> `伪目标`其实就是没有依赖关系，它也不需要依赖关系，并且在你执行`make`时不会主动执行该规则，只有当你指定它时，才会处理该规则，例如`make clean`。

默认情况下，`make`从第一个`target`开始（不是名称以`.`开头的目标，因为`.`开头的有一些特殊变量会使用），在上面的示例中，默认`target`是更新可执行程序`main`， 因此，我们把这条规则放在第一位。因此，当我们执行命令`make`时，`make`读取当前目录中的`Makefile`并开始处理第一条规则。在示例中，此规则用于重新链接`main`。

但在`make`完全处理此规则之前，main`依赖于`main.o, hello.o`，因此它会先去处理生成依赖的规则，也就是

```makefile
main.o : main.cpp
	g++ -c main.cpp

hello.o : hello.cpp hello.h
	g++ -c hello.cpp
```

>   `main.o: main.cpp`：这一行指定了 `main.o` 依赖于 `main.cpp`。如果 `main.cpp` 发生了修改，或者 `main.o` 不存在，将执行`g++ -c main.cpp`这是构建 `main.o` 的规则。`-c` 标志告诉编译器生成目标文件（`main.o`）而不进行链接。首先将源文件编译成目标文件，然后再进行链接是一种常见的做法。
>
>   `hello.o: hello.cpp hello.h`：类似于前面的规则，`hello.o` 依赖于 `hello.cpp` 和 `hello.h`。如果它们中的任何一个发生变化，或者 `hello.o` 不存在，将执行`g++ -c hello.cpp` 这是构建 `hello.o` 的规则。它将 `hello.cpp` 编译成目标文件 `hello.o`。

也就是说当我们执行`make`时，它会递归的检测是否有文件更新，如果没有更新就什么都不做，如果有就执行对应的规则重新生成`target`

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 使用变量
在上面示例中，我们必须在规则中列出所有目标文件（这里重复）这种重复很容易出错；如果一个新的目标文件被添加到系统中，我们可能会将其添加到一个列表中而忘记另一个列表。可以通过使用变量来消除风险并简化 Makefile。 变量允许定义成文本字符串，然后在多个位置进行替换（`$(变量名)`）

标准做法是每个`Makefile`都有一个名为`OBJS`的变量，或者`OBJS`是所有目标文件名的列表, 例如

```makefile
# OBJS 是根据源文件生成的目标文件列表。
OBJS = main.o hello.o

main : $(OBJS)
	g++ $(OBJS) -o main

main.o : main.cpp
	g++ -c main.cpp

hello.o : hello.cpp hello.h
	g++ -c hello.cpp

clean:
	rm -rf *.o main
```

此外`g++` 和 还有一些其他的编译器参数也是可以通过变量进行整理的，再次优化

```makefile
# CXX 定义了编译器。
CXX = g++
# CXXFLAGS 包含了编译选项，例如 -Wall 开启所有警告，-std=c++11 使用 C++11 标准。
CXXFLAGS = -Wall -std=c++11

# OBJS 是根据源文件生成的目标文件列表。
OBJS = main.o hello.o
# TARGET 是最终生成的可执行文件。
TARGET = main

$(TARGET) : $(OBJS)
	g++ $(OBJS) -o main

main.o : main.cpp
	g++ -c main.cpp

hello.o : hello.cpp hello.h
	g++ -c hello.cpp

clean:
	rm -rf *.o $(TARGET)
```

这样代码就更加易于维护了，最后，`clean` 目标中也使用了变量，这使得清理操作更一致且易于维护。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 自动推导
在上面的示例中，我们还是保留着各种依赖关系的显示规则，当文件较多的时候，没有必要详细说明编译各个源文件的方法，因为make可以弄清楚它们，它有一个用于更新 `.o`来自相应名称的文件。因此，我们可以从目标文件的规则中省略多个规则。这也称之为隐式规则。

下面结合之前的示例进行优化

```makefile
# CXX 定义了编译器。
CXX = g++
# CXXFLAGS 包含了编译选项，例如 -Wall 开启所有警告，-std=c++11 使用 C++11 标准。
CXXFLAGS = -Wall -std=c++11

# OBJS 是根据源文件生成的目标文件列表。
SRCS = main.cpp hello.cpp
# $(SRCS:.cpp=.o) 是一个对 SRCS 列表中每个元素进行操作的模式替换。在这里，它用.o替换了 SRCS 中每个元素的 .cpp 扩展名。
OBJS = $(SRCS:.cpp=.o)

# TARGET 是最终生成的可执行文件。
TARGET = main

$(TARGET) : $(OBJS)
    $(CXX) $(OBJS) -o $@
    
%.o : %.cpp
    $(CXX) -c $< -o $@

clean:
    rm -rf $(OBJS) $(TARGET)
```

>   在这里，`$<` 表示依赖项（源文件），`$@` 表示目标（目标文件或可执行文件）

这就是我们在实际实践中编写 Makefile 的方式。

因为隐式规则非常方便，所以它们很重要。并且经常被使用。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 简约风格
当 Makefile 的对象仅通过隐式规则创建时，可以使用替代样式的 Makefile。在这种风格的 Makefile 中，您可以根据先决条件而不是目标对条目进行分组。下面是一个示例

```makefile
# CXX 定义了编译器。
CXX = g++
# CXXFLAGS 包含了编译选项，例如 -Wall 开启所有警告，-std=c++11 使用 C++11 标准。
CXXFLAGS = -Wall -std=c++11

# OBJS 是根据源文件生成的目标文件列表。
SRCS = main.cpp hello.cpp
# 使用简化的方式生成目标文件列表
OBJS = $(SRCS:.cpp=.o)

# TARGET 是最终生成的可执行文件。
TARGET = main

# 默认目标是最终可执行文件
all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $@

# 通用的规则，用于生成目标文件
%.o: %.cpp
    $(CXX) -c $(CXXFLAGS) $< -o $@

# 清理操作
clean:
    rm -rf $(OBJS) $(TARGET)
```

>   1.  添加了 `all` 默认目标，它依赖于 `$(TARGET)`，这是一个常见的惯例，方便用户直接运行 `make` 而不必指定目标。
>   2.  在生成目标文件的规则中，添加了 `$(CXXFLAGS)` 以包含编译选项。

它更紧凑，但有些人不喜欢它，因为将每个目标的所有信息放在一个地方不是很清晰。

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

## 目录清理

我们之前添加的清理编译后的文件，写的比较潦草，其实可以更加优雅，

```makefile
# CXX 定义了编译器。
CXX = g++
# CXXFLAGS 包含了编译选项，例如 -Wall 开启所有警告，-std=c++11 使用 C++11 标准。
CXXFLAGS = -Wall -std=c++11

# OBJS 是根据源文件生成的目标文件列表。
SRCS = main.cpp hello.cpp
# 使用简化的方式生成目标文件列表
OBJS = $(SRCS:.cpp=.o)

# TARGET 是最终生成的可执行文件。
TARGET = main

# 默认目标是最终可执行文件
all: $(TARGET)

$(TARGET): $(OBJS)
    $(CXX) $(OBJS) -o $@

# 通用的规则，用于生成目标文件
%.o: %.cpp
    $(CXX) -c $(CXXFLAGS) $< -o $@

# 清理操作
clean:
    rm -rf $(OBJS) $(TARGET)

.PHONY: all clean
```

>   1.  将 `PHONY` 目标添加到 `all` 和 `clean`，这有助于确保 Makefile 在这两个目标被调用时能够正常工作，而不受同名文件的影响。
>   2.  执行`make clean`你将会看到一个整洁的目录

---

下一篇：[练习4 Makefile之显式规则](../practice-04/)，上一篇：[练习2 创建基本的Makefile](../practice-02/)，[目录](#makefile之简单介绍)｜[首页](../README.md)

