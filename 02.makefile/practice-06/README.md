# Makefile之使用变量

- [温故知新](#温故知新)
- [变量引用的基础知识](#变量引用的基础知识)
- [变量的多种风格](#变量的多种风格)
    - [递归展开变量赋值](#递归展开变量赋值)
    - [简单扩展变量赋值](#简单扩展变量赋值)
    - [立即扩展变量赋值](#立即扩展变量赋值)
    - [条件变量赋值](#条件变量赋值)
- [引用变量的高级功能](#引用变量的高级功能)
    - [替换参考](#替换参考)
    - [计算变量名](#计算变量名)
- [变量如何获取它们的值](#变量如何获取它们的值)
- [设置变量](#设置变量)
- [向变量添加更多文本](#向变量添加更多文本)
- [override指令](#override指令)
- [定义多行变量](#定义多行变量)
- [取消定义变量](#取消定义变量)
- [来自环境的变量](#来自环境的变量)
- [特定于目标的变量值](#特定于目标的变量值)
- [模式特定的变量值](#模式特定的变量值)
- [抑制继承](#抑制继承)
- [其他特殊变量](#其他特殊变量)

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 温故知新

-   [练习1 理解编译的基本过程](../practice-01/)  
-   [练习2 创建基本的Makefile](../practice-02/)
-   [练习3 Makefile之简单介绍](../practice-03/)
-   [练习4 Makefile之显式规则](../practice-04/)
-   [练习5 Makefile之配方规则](../practice-05/)

变量是在Makefile中定义的名称，用于表示文本字符串，称为变量的值。这些值可以根据显式请求替换到目标、前提条件、命令和Makefile的其他部分中。

在Makefile的所有部分中，变量和函数在读取时都会被展开，除了在命令中、使用‘=’定义的变量定义的右侧，以及使用define指令定义的变量定义的主体。变量展开时的值是在展开时的最新定义的值。换句话说，变量是动态作用域的。

变量可以表示文件名列表、传递给编译器的选项、要运行的程序、要查找源文件的目录、要写入输出的目录，或任何您可以想象的东西。

变量名可以是任何不包含`:`、`#`、`=`或空格的字符序列。但是，包含除字母、数字和下划线之外的字符的变量名应谨慎考虑，因为在某些shell中，它们可能无法通过环境传递给子make。以`.`和大写字母开头的变量名可能在将来的make版本中被赋予特殊含义。

变量名区分大小写。名称`foo`、`FOO`和`Foo`都引用不同的变量。

传统上，变量名使用大写字母，但我们建议在Makefile中用于内部目的的变量名使用小写字母，并将大写字母保留用于控制隐式规则的参数或用户应该使用命令选项覆盖的参数。

有一些变量具有单个标点字符或仅几个字符的名称。这些是自动变量，它们具有特定的专用用途。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 变量引用的基础知识

要替换变量的值，请在变量名称之前写一个美元符号，括在括号或大括号中：`$(foo)`或`${foo}`都是对变量foo的有效引用。这是为什么必须写`$$`以在文件名或命令中具有单个美元符号的效果。

变量引用可以在任何上下文中使用：目标、前提条件、命令、大多数指令和新变量值。以下是一个常见情况的示例，其中一个变量保存了程序中所有对象文件的名称：

```makefile
objects = program.o foo.o utils.o
program : $(objects)
    g++ -o program $(objects)

$(objects) : defs.h
```

变量引用通过严格的文本替换工作。因此，规则

```makefile
foo = c
prog.o : prog.$(foo)
    $(foo)$(foo) -$(foo) prog.$(foo)
```

可以用来编译一个C程序prog.c。由于在变量赋值中忽略变量值前面的空格，所以foo的值正好是‘c’。（实际上不要这样编写你的Makefile！）

一个美元符号后面跟着一个字符，而不是美元符号、开括号或大括号，将该字符视为变量名称。因此，你可以使用`$x`引用变量x。然而，这种做法可能会引起混淆（例如，`$foo`引用的是变量f后面的字符串oo），因此我们建议在所有变量周围都使用括号或大括号，即使是单个字母的变量，除非省略它们会显著提高可读性。一个通常提高可读性的地方是自动变量。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 变量的多种风格

在GNU make中，变量可以有不同的取值方式，我们将它们称为变量的"flavor"。这些"flavor"在分配变量值和在以后使用和扩展变量时如何处理这些值方面有所不同。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 递归展开变量赋值

递归展开变量是一种变量类型，可以通过使用`=`或使用define指令的语句来定义。您指定的值将按原样安装；如果它包含对其他变量的引用，那么这些引用将在这个变量被替代时（在展开其他某个字符串时）扩展。当发生这种情况时，它被称为递归展开。

例如：

```makefile
foo = $(bar)
bar = $(ugh)
ugh = Huh?

all: ; echo $(foo)
```

将输出`Huh?`：`$(foo)`展开为`$(bar)`，然后展开为`$(ugh)`，最终展开为`Huh?`。

这种类型的变量是大多数其他make版本支持的唯一类型。它有它的优点和缺点。一个优点（大多数人会这么说）是：

```makefile
CFLAGS = $(include_dirs) -O
include_dirs = -Ifoo -Ibar
```

将实现预期的效果：当在规则中展开`CFLAGS`时，它将展开为`-Ifoo -Ibar -O`。一个主要的缺点是你无法在变量的末尾添加内容，如：

```makefile
CFLAGS = $(CFLAGS) -O
```

因为这将在变量展开中引发无限循环。（实际上，make检测到无限循环并报告错误。）

另一个缺点是在定义中引用的任何函数在展开变量时都将被执行。这会使make运行变慢；更糟糕的是，它会导致通配符和shell函数给出不可预测的结果，因为您无法轻松控制它们何时被调用，甚至调用多少次。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 简单扩展变量赋值

为了避免递归展开变量的问题和不便，还有另一种类型：简单展开变量。

简单展开变量是通过使用`:=`或`::=`的行来定义的。在make中，这两种形式是等价的；但只有`::=`形式在POSIX标准中描述（对于POSIX Issue 8，`::=`形式已添加到POSIX标准中）。

简单展开变量的值在定义变量时扫描一次，展开对其他变量和函数的引用，扫描完成后变量的值将不再被展开：当使用变量时，值将逐字复制作为展开的内容。如果该值包含变量引用，那么展开的结果将包含它们在定义此变量时的值。因此，

```makefile
x := foo
y := $(x) bar
x := later
```

等同于

```makefile
y := foo bar
x := later
```

这里有一个更复杂的例子，演示了`:=`与shell函数一起使用。此示例还显示了变量MAKELEVEL的使用，该变量在从级别传递到级别时会更改。例示了使用‘:=’的一个优点是，典型的“进入目录”的规则看起来像这样：

```makefile
${subdirs}:
    ${MAKE} -C $@ all
```

简单展开变量通常使复杂的Makefile编程更加可预测，因为它们的工作方式类似于大多数编程语言中的变量。它们允许您重新定义一个变量，使用其自身的值（或由扩展函数之一处理的值），并更高效地使用扩展函数。

您还可以使用它们在变量值中引入受控制的前导空格。在替换变量引用和函数调用之前，会从输入中删除前导空格字符；这意味着您可以通过使用变量引用来保护它们，将前导空格包含在变量值中，如下所示：

```makefile
nullstring :=
space := $(nullstring) # 行末
```

这里变量space的值确切为一个空格。注释`# 行末`在这里只是为了清晰起见。由于变量值不会删除尾随空格字符，因此在变量值末尾放置一个空格会产生相同的效果（但很难阅读）。如果在变量值的末尾放置空格，建议在行尾放置此类注释以明确您的意图。相反，如果不希望在变量值的末尾有任何空格字符，必须记住不要在某些空格之后在行末放置随机注释，例如：

```makefile
dir := /foo/bar    # 用于放置frobs的目录
```

这里变量dir的值是‘/foo/bar    ’（带有四个尾随空格），这可能不是预期的结果。 （想象一下使用这个定义的类似‘$(dir)/file’的东西！）

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 立即扩展变量赋值

另一种分配方式允许立即展开，但不同于简单分配，生成的变量是递归的：它将在每次使用时再次展开。为了避免意外结果，在值立即展开后，它将自动带引号：值中的所有$实例在展开后将被转换为$$。这种分配类型使用`:::=`运算符。例如，

```makefile
var = first
OUT :::= $(var)
var = second
```

导致OUT变量包含文本‘first’，而在这里：

```makefile
var = one$$two
OUT :::= $(var)
var = three$$four
```

导致OUT变量包含文本`one$$two`。值在分配变量时进行展开，因此var的第一个值的展开结果是`one$two`；然后在完成分配之前，值将重新转义，最终结果是`one$$two`。

此后，变量OUT被视为递归变量，因此在使用时将重新展开。

这在功能上似乎与`:=` / `::=`运算符等效，但有一些区别：

首先，分配后，变量是普通的递归变量；当使用`+=`附加到它时，右侧的值不会立即展开。如果希望`+=`运算符立即展开右侧的值，应该使用`:=` / `::=`分配。

其次，这些变量略微不如简单展开变量高效，因为它们在使用时需要重新展开，而不仅仅是复制。但由于所有变量引用都会转义，这种展开只是对值进行取消转义，不会展开任何变量或运行任何函数。

以下是另一个示例：

```makefile
var = one$$two
OUT :::= $(var)
OUT += $(var)
var = three$$four
```

在此之后，OUT的值是文本`one$$two $(var)`。当使用此变量时，它将被展开，结果将是`one$two three$four`。

这种分配样式等效于传统的BSD make的`:=`运算符；正如您所看到的，它与make的`:=`运算符略有不同。`:::=`运算符已添加到POSIX规范中，Issue 8中以提供可移植性。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 条件变量赋值

还有另一种变量的赋值运算符，`?=`。这被称为条件变量赋值运算符，因为它仅在变量尚未定义时才生效。这个语句：

```makefile
FOO ?= bar
```

与以下语句完全等效：

```makefile
ifeq ($(origin FOO), undefined)
  FOO = bar
endif
```

请注意，设置为空值的变量仍然被定义，因此`?=`不会设置该变量。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 引用变量的高级功能

这一节将介绍一些高级功能，以帮助你以更灵活的方式引用变量。如果你有特定的问题或需要更详细的信息，请随时提出，我会根据你的需求提供相关的信息和解释。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 替换参考

替代引用允许你在变量值中进行指定的替换操作。它的形式为 `$(var:a=b)` 或 `${var:a=b}`，它的作用是获取变量 `var` 的值，将该值中的每个以单词结尾的 `a` 替换为 `b`，然后将生成的字符串进行替代。

当我们说“以单词结尾”时，意味着 `a` 必须出现在值的末尾，要么后面是空格，要么直接出现在值的末尾，才会被替换；值中的其他出现的 `a` 不会被改变。例如：

```makefile
foo := a.o b.o l.a c.o
bar := $(foo:.o=.c)
```

上面的代码将 `bar` 设置为 `a.c b.c l.a c.c`。

替代引用是 `patsubst` 扩展函数的简写形式，`$(var:a=b)` 等效于 `$(patsubst %a,%b,var)`。我们提供替代引用以及 `patsubst`，以便与其他版本的 make 兼容。

另一种替代引用允许你使用 `patsubst` 函数的全部功能。它的形式也是 `$(var:a=b)`，但这次 `a` 必须包含单个 `%` 字符。这个形式等效于 `$(patsubst a,b,$(var))`。例如：

```makefile
foo := a.o b.o l.a c.o
bar := $(foo:%.o=%.c)
```

上面的代码将 `bar` 设置为 `a.c b.c l.a c.c`。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### 计算变量名

计算变量名是一种高级概念，在更复杂的 Makefile 编程中非常有用。在简单情况下，你不需要考虑它们，但它们可以极其有用。

变量可以在变量的名称中进行引用。这被称为计算变量名称或嵌套变量引用。例如，

```makefile
x = y
y = z
a := $($(x))
```

将 `a` 定义为 'z'：`$($(x))` 中的 `$(x)` 展开为 'y'，因此 `$($(x))` 展开为 `$(y)`，最终展开为 'z'。在这里，要引用的变量的名称没有明确指定；它是通过 `$(x)` 的展开计算的。此引用中的 `$(x)` 是嵌套在外部变量引用中的。

前面的示例展示了两个级别的嵌套，但可以有任意数量的级别。例如，下面是三个级别的示例：

```makefile
x = y
y = z
z = u
a := $($($(x)))
```

在这里，最内层的 `$(x)` 展开为 'y'，因此 `$($(x))` 展开为 `$(y)`，然后展开为 'z'；现在我们有 `$(z)`，它变成 'u'。

在变量名称内部引用的递归展开变量引用将按通常的方式重新展开。例如：

```makefile
x = $(y)
y = z
z = Hello
a := $($(x))
```

将 `a` 定义为 'Hello'：`$($(x))` 变成 `$($(y))`，然后变成 `$(z)`，最终变成 'Hello'。

嵌套变量引用还可以包含修改后的引用和函数调用，就像其他引用一样。例如，使用 `subst` 函数：

```makefile
x = variable1
variable2 := Hello
y = $(subst 1,2,$(x))
z = y
a := $($($(z)))
```

最终将 `a` 定义为 'Hello'。虽然很少有人会编写如此复杂的嵌套引用，但它可以工作：`$($($(z)))` 展开为 `$($(y))`，它变成 `$($(subst 1,2,$(x)))`。这从 `x` 中获取了值 'variable1'，并通过替换变为 'variable2'，因此整个字符串变成 '$(variable2)'，这是一个值为 'Hello' 的简单变量引用。

计算变量名不一定要完全由单个变量引用组成。它可以包含多个变量引用，以及一些不变的文本。例如，

```makefile
a_dirs := dira dirb
1_dirs := dir1 dir2

a_files := filea fileb
1_files := file1 file2

ifeq "$(use_a)" "yes"
a1 := a
else
a1 := 1
endif

ifeq "$(use_dirs)" "yes"
df := dirs
else
df := files
endif

dirs := $($(a1)_$(df))
```

将根据 `use_a` 和 `use_dirs` 的设置，为 `dirs` 提供与 `a_dirs`、`1_dirs`、`a_files` 或 `1_files` 相同的值。

计算变量名还可以在替代引用中使用：

```makefile
a_objects := a.o b.o c.o
1_objects := 1.o 2.o 3.o

sources := $($(a1)_objects:.o=.c)
```

将 `sources` 定义为 'a.c b.c c.c' 或 '1.c 2.c 3.c'，这取决于 `a1` 的值。

对于嵌套变量引用的使用，唯一的限制是它们不能指定函数名称的一部分。这是因为在展开嵌套引用之前，已经对识别的函数名称进行了测试。例如，

```makefile
ifdef do_sort
func := sort
else
func := strip
endif

bar := a d b g q c

foo := $($(func) $(bar))
```

尝试为 'foo' 赋予变量 'sort a d b gc' 或 'strip a d b g q c' 的值，而不是将 'a d b g q c' 作为 sort 或 strip 函数的参数。这个限制可能会在未来被移除，如果显示这个更改是一个好主意的话。

你还可以在变量赋值的左侧或 define 指令中使用计算变量名称，如下所示：

```makefile
dir = foo
$(dir)_sources := $(wildcard $(dir)/*.c)
define $(dir)_print =
lpr $($(dir)_sources)
endef
```

这个示例定义了变量 'dir'、'foo_sources' 和 'foo_print'。

请注意，嵌套变量引用与递归展开变量完全不同，尽管在进行 Makefile 编程时，它们会一起以复杂的方式使用。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 变量如何获取它们的值

变量可以通过多种方式获取值：

1. 当运行 make 时，你可以指定一个覆盖值。
2. 你可以在 Makefile 中使用赋值或直接定义来指定一个值。
3. 你可以使用 let 函数或 foreach 函数指定一个临时值。
4. 环境中的变量会成为 make 变量。
5. 每个规则都会为若干个自动变量赋予新的值，每个自动变量有一个常规用途。
6. 有几个变量具有常量初始值。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 设置变量

要在 Makefile 中设置变量，可以编写一行，以变量名开头，后面跟一个赋值操作符，包括`=`、`:=`、`::=` 或 `:::=` 中的一个。赋值操作符后面的内容以及行首的任何空格都将成为该变量的值。例如：

```makefile
objects = main.o foo.o bar.o utils.o
```

上述代码定义了一个名为 `objects` 的变量，它的值为 `main.o foo.o bar.o utils.o`。变量名周围和 `=` 后面的空格将被忽略。

使用 `=` 定义的变量是递归扩展变量。使用 `:=` 或 `::=` 定义的变量是简单扩展变量；这些定义可以包含变量引用，这些引用在进行定义之前将被扩展。使用 `:::=` 定义的变量是立即扩展变量。不同的赋值操作符在《变量的两种风格》中有描述。

变量名可以包含函数和变量引用，在读取行以查找要使用的实际变量名时会被扩展。变量的值长度没有限制，除了计算机内存的大小。为了提高可读性，可以将变量的值分成多个物理行。

如果您希望一个变量只在尚未设置时才被赋值，那么可以使用快捷操作符 `?=` 而不是 `=`。这两种设置变量`'FOO` 的方式是相同的：

```makefile
FOO ?= bar
```

和

```makefile
ifeq ($(origin FOO), undefined)
FOO = bar
endif
```

shell 赋值操作符 `!=` 用于执行一个 shell 脚本并将变量设置为其输出。此操作符首先评估右侧，然后将结果传递给 shell 执行。如果执行的结果以换行符结束，将去掉一个换行符；所有其他换行符将被替换为空格。然后，生成的字符串将放入命名的递归扩展变量中。例如：

```makefile
hash != printf '\043'
file_list != find . -name '*.c'
```

如果执行的结果可能产生一个 `$`，而且你不希望其后的内容被解释为 make 变量或函数引用，那么你必须在执行时将每个 `$` 替换为 `$$`。另外，可以使用 shell 函数 call 将一个简单扩展变量设置为使用 shell 函数运行程序的结果。例如：

```makefile
hash := $(shell printf '\043')
var := $(shell find . -name "*.c")
```

与 shell 函数一样，刚刚调用的 shell 脚本的退出状态代码将存储在 .SHELLSTATUS 变量中。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 向变量添加更多文本

通常情况下，向已定义的变量添加更多文本是很有用的。可以使用包含`+=`的行来实现这一点，如下所示：

```makefile
objects += another.o
```

这将取出变量 objects 的值，并将文本 ‘another.o’ 添加到它的末尾（如果它已经有值的话，前面会有一个空格）。因此：

```makefile
objects = main.o foo.o bar.o utils.o
objects += another.o
```

将 objects 设置为 'main.o foo.o bar.o utils.o another.o'。

使用 ‘+=’ 类似于：

```makefile
objects = main.o foo.o bar.o utils.o
objects := $(objects) another.o
```

但在使用更复杂的值时，有一些重要的区别。

当涉及的变量以前没有被定义时，‘+=’ 的作用与普通的 ‘=’ 一样：它定义了一个递归扩展的变量。然而，当存在先前的定义时，‘+=’ 的行为取决于你最初定义变量的风格。

当你使用 ‘+=’ 向变量的值添加内容时，make 的操作基本上就好像你在变量的初始定义中包含了额外的文本。如果你首先使用 ‘:=’ 或 ‘::=’ 定义它，使其成为简单扩展的变量，‘+=’ 将添加到该简单扩展的定义，并在追加到旧值之前扩展新文本，就像 ‘:=’ 一样。

实际上，

```makefile
variable := value
variable += more
```

与以下代码完全等效：

```makefile
variable := value
variable := $(variable) more
```

另一方面，当你首先使用普通 ‘=’ 或 ‘:::=’ 定义为递归扩展的变量，然后使用 ‘+=’ 时，make 会将未扩展的文本附加到现有值中，无论其是什么。这意味着

```makefile
variable = value
variable += more
```

大致等效于：

```makefile
temp = value
variable = $(temp) more
```

当然，它从来没有定义一个叫 temp 的变量。这一点的重要性在于，如果变量的旧值包含变量引用。考虑这个常见的例子：

```makefile
CFLAGS = $(includes) -O
…
CFLAGS += -pg # 启用性能分析
```

第一行使用对另一个变量 includes 的引用定义了 CFLAGS 变量。 使用 ‘=’ 对定义进行了设置，使 CFLAGS 成为一个递归扩展变量，这意味着 make 处理 CFLAGS 的定义时不会扩展 ‘$(includes) -O’。因此，includes 不必在其值生效之前就被定义。它只需要在任何引用 CFLAGS 之前定义。如果我们尝试在不使用 ‘+=’ 的情况下添加到 CFLAGS 的值，我们可能会这样做：

```makefile
CFLAGS := $(CFLAGS) -pg # 启用性能分析
```

这很接近，但不完全符合我们的要求。使用 ‘:=’ 重新定义了 CFLAGS 为简单扩展的变量；这意味着在设置变量之前，make 会扩展文本 ‘$(CFLAGS) -pg’。如果 includes 尚未定义，我们得到 ‘-O -pg’，并且稍后对 includes 的任何定义都不会产生影响。相反，通过使用 ‘+=’，我们将 CFLAGS 设置为未扩展的值 ‘$(includes) -O -pg’。因此，我们保留了对 includes 的引用，因此如果该变量在以后的任何时候被定义，像 ‘$(CFLAGS)’ 这样的引用仍然使用它的值。

简单来说，使用 ‘+=’ 可以确保在添加文本到已定义的变量值时，保留对其他变量的引用，这些其他变量可能在以后的时间点被定义。这种行为对于确保变量的引用不会因为后续的定义而失效非常重要。

需要注意的是，只有当你向已定义的变量添加内容时才使用 ‘+=’。如果你尝试使用 ‘+=’ 向一个尚未定义的变量添加内容，它将起到与 ‘=’ 相同的作用，即定义一个递归扩展的变量。

如果你想要删除变量的值，你可以使用 ‘=’ 操作符将其设置为空。例如：

```makefile
my_var = some_value
my_var = 
```

这将删除 my_var 的值。

总结一下，使用 ‘+=’ 操作符可用于将文本附加到已定义的变量的值，同时保留对其他变量的引用。这在确保变量的引用不会因为后续的定义而失效时非常有用。如果你不需要保留引用，或者要向尚未定义的变量添加内容，可以使用 ‘=’ 操作符。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

### override指令

`override` 指令用于在 Makefile 中设置一个已经在命令行参数中设置的变量，从而覆盖其值。通常情况下，如果变量已经在命令行参数中设置了，Makefile 中的普通赋值操作会被忽略。使用 `override` 指令，你可以强制设置 Makefile 中的变量，即使它已经在命令行参数中设置。

`override` 指令的格式如下：

```makefile
override variable = value
```

或者

```makefile
override variable := value
```

如果你想要向在命令行参数中已经设置的变量附加更多文本，可以使用以下方式：

```makefile
override variable += more text
```

`override` 标记的变量赋值具有高于所有其他赋值的优先级，除非另一个变量也使用了 `override` 标记。对未使用 `override` 标记的变量的后续赋值或附加将被忽略。

`override` 指令的主要用途是允许你更改和添加用户通过命令行参数指定的值。举个例子，假设你总是希望在运行 C 编译器时使用 `-g` 选项，但允许用户像往常一样使用命令行参数指定其他选项。你可以使用以下 `override` 指令来实现：

```makefile
override CFLAGS += -g
```

你还可以在 `define` 指令中使用 `override` 指令。使用方法如下：

```makefile
override define foo =
bar
endef
```

`override` 指令的主要目的是允许你在 Makefile 中更改和扩展用户通过命令行参数传递的值。这对于自定义构建流程非常有用。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 定义多行变量

`define` 指令用于设置变量的值，其语法特殊，允许在值中包含换行符，这对于定义一系列命令和用于 `eval` 函数的 Makefile 语法段非常方便。

`define` 指令与其他变量定义的工作方式基本相同，只是其语法略有不同。`define` 指令的格式如下：

```makefile
define variable
value
endef
```

在同一行上，`define` 指令后面跟着被定义的变量名称和（可选的）赋值运算符，然后是换行。变量的值出现在接下来的行中。变量值的结束由一行仅包含单词 "endef" 标志。

除了语法上的不同之外，`define` 的工作原理与其他变量定义方式相同。变量名称可以包含函数和变量引用，在读取 `define` 指令以查找要使用的实际变量名称时会进行展开。

在 `endef` 前的最后一个换行符不包括在值中；如果你希望值包含一个尾随换行符，你必须包含一个空行。例如，如果要定义一个包含换行符的变量，你必须使用两个空行，而不是一个：

```makefile
define newline

endef
```

你可以省略变量赋值运算符，如果省略，make 将假定它为 `=` 并创建一个递归展开的变量。使用 `+=` 运算符时，新值将附加到以前的值上，与其他附加操作一样，使用一个空格分隔旧值和新值。

你可以嵌套 `define` 指令：make 将跟踪嵌套的指令，并在没有使用 `endef` 正确关闭时报告错误。请注意，以配方前缀字符开头的行被视为配方的一部分，因此在此类行上出现的 `define` 或 `endef` 字符串将不被视为 make 指令。

```makefile
define two-lines
echo foo
echo $(bar)
endef
```

在配方中使用前面的示例在功能上等同于：

```makefile
two-lines = echo foo; echo $(bar)
```

因为用分号分隔的两个命令行为两个独立的 shell 命令。然而，请注意，使用两个独立的行意味着 make 将两次调用 shell，为每一行运行一个独立的子 shell。

如果你希望使用 `define` 定义的变量值优先于命令行变量定义，你可以在 `define` 中结合使用 `override` 指令：

```makefile
override define two-lines =
foo
$(bar)
endef
```


---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 取消定义变量

如果你想清除一个变量，将其值设置为空通常足够了。展开这样的变量将产生相同的结果（空字符串），无论它是否被设置。然而，如果你正在使用 `flavor`和 `origin`函数，那么从未设置的变量和具有空值的变量之间存在差异。在这种情况下，你可能希望使用 `undefine` 指令使变量看起来就像从未设置过一样。例如：

```makefile
foo := foo
bar = bar

undefine foo
undefine bar

$(info $(origin foo))
$(info $(flavor bar))
```

此示例将分别对两个变量打印“undefined”。

如果你想取消定义命令行变量定义，你可以像取消定义变量定义一样，结合使用 `override` 指令和 `undefine`，例如：

```makefile
override undefine CFLAGS
```

这将取消定义名为 `CFLAGS` 的命令行变量。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 来自环境的变量

make 可以从运行 make 的环境中获取变量。每个 make 启动时看到的环境变量都会被转换为一个同名和同值的 make 变量。然而，在 Makefile 中进行的显式赋值或使用命令参数会覆盖环境中的变量。（如果指定了 '-e' 标志，那么环境中的值会覆盖 Makefile 中的赋值。但这并不是推荐的做法。）

因此，通过在环境中设置变量 `CFLAGS`，你可以让大多数 Makefile 中的 C 编译操作使用你喜欢的编译器选项。这对于具有标准或常规含义的变量是安全的，因为你知道没有 Makefile 会将它们用于其他用途。（请注意，这并不是完全可靠的；一些 Makefile 显式设置了 `CFLAGS`，因此不会受到环境中的值的影响。）

当 make 运行一个规则时，一些在 Makefile 中定义的变量会放入每个 make 调用的命令的环境中。默认情况下，只有来自 make 的环境或命令行的变量会放入命令的环境中。你可以使用 `export` 指令来传递其他变量。

不推荐使用环境中的变量进行其他用途。不明智的做法是让 Makefile 的功能依赖于其控制之外的环境变量，因为这会导致不同用户从同一 Makefile 获取不同的结果。这与大多数 Makefile 的整体目标背道而驰。

这种问题特别容易出现在 SHELL 变量上，SHELL 变量通常存在于环境中以指定用户选择的交互式 shell。这样的选择影响 make 是不可取的，因此，make 以特殊方式处理 SHELL 环境变量。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 特定于目标的变量值

在 make 中，变量值通常是全局的，即无论在何处评估它们，它们的值都是相同的（除非它们被重置）。这一规则的例外包括使用 `let` 函数或 `foreach` 函数定义的变量，以及自动变量。

另一个例外是目标特定的变量值。这个功能允许你根据 make 当前正在构建的目标定义相同变量的不同值。与自动变量一样，这些值仅在目标的规则上下文中（以及其他目标特定的赋值中）可用。

像这样设置目标特定的变量值：

```makefile
target ... : variable-assignment
```

目标特定的变量分配可以以任何或所有特殊关键字 `export`、`unexport`、`override` 或 `private` 为前缀；这些关键字只适用于该变量实例。

多个目标值将为目标列表的每个成员分别创建目标特定的变量值。

`variable-assignment` 可以是任何有效的赋值形式：递归（`=`）、简单（`:=` 或 `::=`）、立即（`::=`）、追加（`+=`）或条件（`?=`）。在 `variable-assignment` 中出现的所有变量都在目标的上下文中计算：因此，任何先前定义的目标特定变量值将生效。注意，这个变量实际上与任何“全局”值是不同的：这两个变量不必具有相同的类型（递归 vs. 简单）。

目标特定变量具有与任何其他 Makefile 变量相同的优先级。命令行（如果启用了 `-e` 选项，还有环境变量）提供的变量将具有更高的优先级。通过指定 `override` 指令可以让目标特定变量值优先。

目标特定变量的另一个特殊功能是，当你定义一个目标特定变量时，该变量值也会对该目标的所有前提条件以及它们的前提条件等生效（除非这些前提条件使用自己的目标特定变量值覆盖该变量）。因此，例如，如下所示的语句：

```makefile
prog : CFLAGS = -g
prog : prog.o foo.o bar.o
```

将在 `prog` 的规则中将 `CFLAGS` 设置为 `-g`，但也会在创建 `prog.o`、`foo.o` 和 `bar.o` 的规则以及创建它们的前提条件的规则中设置 `CFLAGS` 为 `-g`。

请注意，每次调用 make 时，给定的前提条件最多只会构建一次。如果同一个文件是多个目标的前提条件，且每个目标对相同的目标特定变量具有不同的值，那么首先构建的目标将导致前提条件被构建，并且前提条件将继承来自第一个目标的目标特定值。它将忽略来自其他目标的目标特定值。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 模式特定的变量值

除了目标特定变量值，GNU make 还支持模式特定变量值。在这种形式中，变量被定义为匹配指定模式的任何目标。

像这样设置模式特定变量值：

```makefile
pattern … : variable-assignment
```

其中 `pattern` 是一个 `%` 模式。与目标特定变量值一样，多个模式值会为每个模式分别创建模式特定变量值。`variable-assignment` 可以是任何有效的赋值形式。任何命令行变量设置都会优先，除非指定了 `override`。

例如：

```makefile
%.o : CFLAGS = -O
```

将为匹配模式 `%.o` 的所有目标分配 `CFLAGS` 值为 `-O`。

如果一个目标匹配多个模式，那么以更长茎的匹配模式特定变量将首先被解释。这会导致更具体的变量优先于更通用的变量，例如：

```makefile
%.o: %.c
        $(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@

lib/%.o: CFLAGS := -fPIC -g
%.o: CFLAGS := -g

all: foo.o lib/bar.o
```

在这个示例中，CFLAGS 变量的第一个定义将用于更新 lib/bar.o，即使第二个定义也适用于这个目标。结果具有相同茎长度的模式特定变量按照它们在 Makefile 中的定义顺序考虑。

模式特定变量在目标特定变量之后搜索，该目标特定变量为该目标明确定义，并在父目标的目标特定变量之前搜索。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 抑制继承

如前所述，make 变量会被前提继承。这种能力允许您根据引起其重新构建的目标来修改前提的行为。例如，您可能会在调试目标上设置目标特定变量，然后运行 'make debug' 将导致该变量被 'debug' 的所有前提继承，而仅运行 'make all'（例如）将不具有该赋值。

然而，有时您可能不希望变量被继承。对于这些情况，make 提供了 private 修饰符。虽然该修饰符可以与任何变量赋值一起使用，但它在目标和模式特定变量中使用时最有意义。任何标记为 private 的变量将对其本地目标可见，但不会被该目标的前提继承。标记为 private 的全局变量将在全局范围内可见，但不会被任何目标继承，因此不会在任何配方中可见。

举个例子，考虑以下 Makefile：

```makefile
EXTRA_CFLAGS =

prog: private EXTRA_CFLAGS = -L/usr/local/lib
prog: a.o b.o
```

由于 private 修饰符，a.o 和 b.o 将不会从 prog 目标继承 EXTRA_CFLAGS 变量的赋值。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)

## 其他特殊变量

Make 中一些具有特殊属性的变量：

1. **MAKEFILE_LIST**
   - 包含 make 解析的每个 Makefile 的名称，按照解析的顺序排列。名称是在 make 开始解析 Makefile 之前附加的。因此，如果一个 Makefile 的第一件事是检查此变量的最后一个单词，它将是当前 Makefile 的名称。但是，一旦当前 Makefile 使用了 include，最后一个单词将是刚刚包含的 Makefile 的名称。

   ```makefile
   name1 := $(lastword $(MAKEFILE_LIST))
   
   include inc.mk
   
   name2 := $(lastword $(MAKEFILE_LIST))
   
   all:
       @echo name1 = $(name1)
       @echo name2 = $(name2)
   ```

   执行上述示例将输出：

   ```makefile
   name1 = Makefile
   name2 = inc.mk
   ```

2. **.DEFAULT_GOAL**
   - 设置默认目标，用于在命令行未指定目标时执行。您可以使用 .DEFAULT_GOAL 变量来查找当前默认目标、清除其值以重新选择默认目标，或显式设置默认目标。

   ```makefile
   # 查询默认目标
   ifeq ($(.DEFAULT_GOAL),)
     $(warning no default goal is set)
   endif
   
   .PHONY: foo
   foo: ; @echo $@
   
   $(warning default goal is $(.DEFAULT_GOAL))
   
   # 重置默认目标
   .DEFAULT_GOAL :=
   
   .PHONY: bar
   bar: ; @echo $@
   
   $(warning default goal is $(.DEFAULT_GOAL))
   
   # 设置自己的默认目标
   .DEFAULT_GOAL := foo
   ```

   这个 Makefile 输出：

   ```makefile
   no default goal is set
   default goal is foo
   default goal is bar
   foo
   ```

   请注意，分配多个目标名称给 .DEFAULT_GOAL 是无效的，会导致错误。

3. **MAKE_RESTARTS**
   - 仅当此 make 实例重新启动时才设置此变量。它将包含此实例已重新启动的次数。请勿设置、修改或导出此变量。

4. **MAKE_TERMOUT 和 MAKE_TERMERR**
   - 当 make 启动时，它会检查 stdout 和 stderr 是否会显示在终端上。如果是，它将分别将 MAKE_TERMOUT 和 MAKE_TERMERR 设置为终端设备的名称（或如果无法确定，则设置为 true）。如果设置了这些变量，它们将被标记为导出。这些变量不会被 make 更改，并且如果已经设置，则不会被修改。

   这些值可以用于判断 make 是否正在写入终端，可用于决定是否强制配方命令生成彩色输出等。

   如果调用子 make 并重定向其 stdout 或 stderr，您需要负责重置或取消导出这些变量，如果您的 Makefile 依赖于它们。

5. **.RECIPEPREFIX**
   - 此变量的值的第一个字符用作 make 假定引入配方行的字符。如果该变量为空（默认情况），该字符是标准制表符字符。例如，这是一个有效的 Makefile：

   ```makefile
   .RECIPEPREFIX = >
   all:
   > @echo Hello, world
   ```

   .RECIPEPREFIX 的值可以多次更改；一旦设置，它在解析的所有规则中保持生效，直到修改。

6. **.VARIABLES**
   - 展开为到目前为止已定义的所有全局变量的名称列表。这包括具有空值的变量，以及内置变量，但不包括仅在特定于目标的上下文中定义的变量。请注意，您分配给此变量的任何值都将被忽略；它将始终返回其特殊值。

7. **.FEATURES**
   - 展开为此 make 版本支持的一系列特殊功能的列表。可能的值包括但不限于：
   - 'archives': 支持使用特殊文件名语法的 ar（归档）文件。
   - 'check-symlink': 支持 -L（--check-symlink-times）标志。
   - 'else-if': 支持“else if”非嵌套条件。
   - 'extra-prereqs': 支持 .EXTRA_PREREQS 特殊目标。
   - 'grouped-target': 支持显式规则中的分组目标语法。
   - 'guile': 可用 GNU Guile 作为嵌入扩展语言。
   - 'jobserver': 支持“作业服务器”增强的并行构建。
   - 'jobserver-fifo': 支持使用命名管道的“作业服务器”增强的并行构建。
   - 'load': 支持创建自定义扩展的动态可加载对象。
   - 'notintermediate': 支持 .NOTINTERMEDIATE 特殊目标。
   - 'oneshell': 支持 .ONESHELL 特殊目标。
   - 'order-only': 支持顺序限定的先决条件。
   - 'output-sync': 支持 --output-sync 命令行选项。
   - 'second-expansion': 支持对先决条件列表进行二次扩展。
   - 'shell-export': 支持将 make 变量导出到 shell 函数。
   - 'shortest-stem': 使用“最短 stem”方法来选择多个适用选项中将使用的模式。
   - 'target-specific': 支持特定于目标和特定于模式的变量分配。
   - 'undefine': 支持 undefine 指令。

8. **.INCLUDE_DIRS**

   -   展开为 make 用于搜索包含的 Makefile 的目录列表。请注意，修改此变量的值不会更改搜索的目录列表。

9. **.EXTRA_PREREQS**

    -   此变量中的每个单词是添加到设置了该值的目标的新先决条件。这些先决条件与正常先决条件不同，因为它们不会出现在任何自动变量中。这允许定义不影响配方的先决条件。

    考虑一个链接程序的规则：

    ```makefile
    myprog: myprog.o file1.o file2.o
           $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
    ```

    现在假设您想要增强此 Makefile，以确保更新编译器会导致程序重新链接。您可以将编译器添加为一个先决条件，但必须确保它不会作为参数传递给链接命令。您需要类似以下的东西：

    ```makefile
    myprog: myprog.o file1.o file2.o $(CC)
           $(CC) $(CFLAGS) $(LDFLAGS) -o $@ \
               $(filter-out $(CC),$^) $(LDLIBS)
    ```

    推荐使用 .EXTRA_PREREQS 和特定于目标的变量提供了一个更简单的解决方案：

    ```makefile
    myprog: myprog.o file1.o file2.o
           $(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LDLIBS)
    myprog: .EXTRA_PREREQS = $(CC)
    ```

    设置 .EXTRA_PREREQS 全局会导致这些先决条件添加到所有目标中（除非它们自己使用特定于目标的值覆盖它）。请注意，make 足够聪明，不会将列在 .EXTRA_PREREQS 中的先决条件添加为其自己的先决条件。

---

下一篇：[练习7 Makefile之条件部分](../practice-07/)，上一篇：[练习5 Makefile之配方规则](../practice-05/)，[目录](#makefile之使用变量)｜[首页](../README.md)