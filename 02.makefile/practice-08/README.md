# Makefile之使用函数

- [温故知新](#温故知新)
- [函数调用语法](#函数调用语法)
- [字符串替换和分析函数](#字符串替换和分析函数)
- [文件名函数](#文件名函数)
- [条件函数](#条件函数)
- [let函数](#let函数)
- [foreach函数](#foreach函数)
- [file函数](#file函数)
- [call函数](#call函数)
- [value函数](#value函数)
- [eval函数](#eval函数)
- [origin函数](#origin函数)
- [flavor函数](#flavor函数)
- [控制Make的函数](#控制Make的函数)
- [shell函数](#shell函数)
- [guile函数](#guile函数)

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 温故知新

-   [练习1 理解编译的基本过程](../practice-01/)  
-   [练习2 创建基本的Makefile](../practice-02/)
-   [练习3 Makefile之简单介绍](../practice-03/)
-   [练习4 Makefile之显式规则](../practice-04/)
-   [练习5 Makefile之配方规则](../practice-05/)
-   [练习6 Makefile之使用变量](../practice-06/)
-   [练习7 Makefile之条件部分](../practice-07/)

函数允许你在Makefile中进行文本处理，以计算要操作的文件或在规则中使用的命令。你可以在函数调用中使用函数，其中你提供函数的名称和一些文本（即参数），以供函数进行操作。函数处理的结果会在调用点被替换到Makefile中，就像变量可能被替换一样。

在Makefile中，函数的调用形式为：

```makefile
$(function-name arguments)
```

其中 `function-name` 是函数的名称，而 `arguments` 是传递给函数的参数。函数的处理结果将替换整个函数调用的位置。

以下是一些常用的Makefile函数的示例：

1. **`$(wildcard pattern)`：** 扩展为匹配指定模式的文件列表。

    ```makefile
    # 查找所有.c文件
    sources := $(wildcard *.c)
    ```

2. **`$(patsubst pattern,replacement,text)`：** 对文本中的单词进行模式替换。

    ```makefile
    # 将所有.c文件替换为.o文件
    objects := $(patsubst %.c,%.o,$(sources))
    ```

3. **`$(foreach var, list, text)`：** 将变量绑定到列表的每个元素，然后将文本作为扩展的结果。

    ```makefile
    # 为每个源文件生成编译规则
    $(foreach src,$(sources),$(info Compiling $(src)))
    ```

4. **`$(shell command)`：** 执行shell命令并返回结果。

    ```makefile
    # 获取当前目录
    current_dir := $(shell pwd)
    ```

5. **`$(if condition, then-part, else-part)`：** 根据条件选择执行其中一部分。

    ```makefile
    # 根据DEBUG变量选择编译选项
    CFLAGS := $(if $(DEBUG),-g,-O2)
    ```

这些是一些基本的函数，还有许多其他函数可用于处理字符串、文件列表等。函数在Makefile中提供了强大的文本处理工具，使你能够更动态地定义规则和命令。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 函数调用语法
这段文本解释了在Makefile中如何使用函数调用，并提供了一些关于函数调用的基本规则和特殊字符的说明。以下是其中的关键点：

1. **函数调用的形式：**
   函数调用与变量引用类似，可以出现在变量引用可以出现的任何地方，并且使用与变量引用相同的规则进行展开。函数调用的形式如下：
   ```makefile
   $(function arguments)
   ```
   或者：
   ```makefile
   ${function arguments}
   ```
   其中 `function` 是函数的名称，`arguments` 是函数的参数。

2. **自定义函数：**
   你还可以通过使用内建的 `call` 函数来创建自己的函数。
   
3. **参数的分隔：**
   参数与函数名称之间用一个或多个空格或制表符分隔，如果有多个参数，则它们由逗号分隔。这些空格和逗号不是参数值的一部分。

4. **特殊字符：**
   当使用对于make而言是特殊字符的字符作为函数参数时，可能需要隐藏它们。GNU make不支持使用反斜杠或其他转义序列转义字符；但是，由于在展开之前将参数拆分，因此可以通过将它们放入变量中来隐藏它们。

   一些可能需要隐藏的字符包括逗号、第一个参数中的初始空格、不匹配的开括号或大括号以及如果不希望它开始匹配对的开括号或大括号。

5. **示例：**
   ```makefile
   comma := ,
   empty :=
   space := $(empty) $(empty)
   foo := a b c
   bar := $(subst $(space),$(comma),$(foo))
   # bar is now ‘a,b,c’.
   ```
   在这个例子中，`subst` 函数通过 `foo` 的值将每个空格替换为逗号，并替换结果。

总的来说，这些规则和示例提供了在Makefile中使用函数调用的基本指南，包括如何自定义函数、参数的分隔方式以及如何处理特殊字符。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 字符串替换和分析函数

这段文本介绍了一些在Makefile中用于字符串操作的函数。以下是其中提到的几个函数及其用法：

1. **`$(subst from,to,text)`：**
   对文本 `text` 进行文本替换，将所有的 `from` 替换为 `to`。例如：
   ```makefile
   $(subst ee,EE,feet on the street)
   ```
   产生值 'fEEt on the strEEt'。

2. **`$(patsubst pattern,replacement,text)`：**
   在文本 `text` 中找到匹配模式 `pattern` 的单词并用 `replacement` 替换。模式可以包含 `%` 作为通配符，匹配单词中的任意字符。例如：
   ```makefile
   $(patsubst %.c,%.o,x.c.c bar.c)
   ```
   产生值 'x.c.o bar.o'。

3. **`$(strip string)`：**
   去除字符串 `string` 前后的空白并将内部的多个空白字符替换为一个空格。例如：
   ```makefile
   $(strip a b c )
   ```
   产生值 'a b c'。

4. **`$(findstring find,in)`：**
   在字符串 `in` 中搜索子字符串 `find`。如果找到，则值为 `find`，否则为空。例如：
   ```makefile
   $(findstring a,a b c)
   $(findstring a,b c)
   ```
   分别产生值 'a' 和 ''。

5. **`$(filter pattern…,text)`：**
   返回文本 `text` 中匹配任何模式单词的所有单词，去除不匹配的单词。模式使用 `%`，类似于上述 `patsubst` 函数。例如：
   ```makefile
   sources := foo.c bar.c baz.s ugh.h
   foo: $(sources)
        cc $(filter %.c %.s,$(sources)) -o foo
   ```
   表示 `foo` 依赖于 `foo.c`, `bar.c`, `baz.s` 和 `ugh.h`，但在编译器命令中只应该包含 `foo.c`, `bar.c` 和 `baz.s`。

6. **`$(filter-out pattern…,text)`：**
   与 `filter` 函数相反，返回文本 `text` 中不匹配任何模式单词的所有单词，去除匹配的单词。

7. **`$(sort list)`：**
   对列表 `list` 中的单词按字典顺序排序，去除重复的单词。例如：
   ```makefile
   $(sort foo bar lose)
   ```
   产生值 'bar foo lose'。

8. **`$(word n,text)`：**
   返回文本 `text` 中的第 `n` 个单词。例如：
   ```makefile
   $(word 2, foo bar baz)
   ```
   产生值 'bar'。

9. **`$(wordlist s,e,text)`：**
   返回文本 `text` 中从第 `s` 个单词到第 `e` 个单词的列表。例如：
   ```makefile
   $(wordlist 2, 3, foo bar baz)
   ```
   产生值 'bar baz'。

10. **`$(words text)`：**
    返回文本 `text` 中的单词数。

11. **`$(firstword names…)`：**
    将参数 `names` 视为由空格分隔的名称序列，返回该系列中的第一个名称。

12. **`$(lastword names…)`：**
    将参数 `names` 视为由空格分隔的名称序列，返回该系列中的最后一个名称。

这些函数提供了在Makefile中对字符串进行操作的强大工具，用于进行替换、搜索、过滤、排序等操作。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 文件名函数
这段文本介绍了一些与文件名或文件名列表相关的内建扩展函数，这些函数在Makefile中用于处理文件名。以下是这些函数的简要说明：

1. **`$(dir names…)`：**
   提取参数 `names` 中每个文件名的目录部分。目录部分是文件名中最后一个斜杠（包括斜杠本身）之前的所有内容。如果文件名中不包含斜杠，则目录部分为字符串 ‘./’。

2. **`$(notdir names…)`：**
   提取参数 `names` 中每个文件名的非目录部分。如果文件名中不包含斜杠，则保持不变。否则，将删除从最后一个斜杠开始的所有内容。

3. **`$(suffix names…)`：**
   提取参数 `names` 中每个文件名的后缀。如果文件名包含句点，则后缀是从最后一个句点开始的所有内容。否则，后缀为空字符串。

4. **`$(basename names…)`：**
   提取参数 `names` 中每个文件名的非后缀部分。如果文件名包含句点，则基本名称是从起始位置到（但不包括）最后一个句点的所有内容。目录部分中的句点将被忽略。如果没有句点，则基本名称是整个文件名。

5. **`$(addsuffix suffix,names…)`：**
   将参数 `names` 视为以空格分隔的名称序列；`suffix` 作为一个单元。将 `suffix` 的值追加到每个单独的名称的末尾，并将结果的较大名称用单个空格连接起来。

6. **`$(addprefix prefix,names…)`：**
   将参数 `names` 视为以空格分隔的名称序列；`prefix` 作为一个单元。将 `prefix` 的值添加到每个单独的名称的前面，并将结果的较大名称用单个空格连接起来。

7. **`$(join list1,list2)`：**
   逐字合并两个参数：第一个参数的第一个单词与第二个参数的第一个单词合并形成结果的第一个单词，依此类推。如果一个参数比另一个参数有更多的单词，额外的单词将未更改地复制到结果中。

8. **`$(wildcard pattern)`：**
   参数 `pattern` 是文件名模式，通常包含通配符字符（如shell文件名模式）。`wildcard` 的结果是与模式匹配的现有文件的名称列表，用空格分隔。

9. **`$(realpath names…)`：**
   对于参数 `names` 中的每个文件名，返回规范的绝对名称。规范名称不包含任何 . 或 .. 组件，也不包含任何重复的路径分隔符（/）或符号链接。如果操作失败，返回空字符串。

10. **`$(abspath names…)`：**
    对于参数 `names` 中的每个文件名，返回不包含任何 . 或 .. 组件，也不包含任何重复的路径分隔符（/）的绝对名称。与 `realpath` 函数不同，`abspath` 不解析符号链接，也不要求文件名引用现有文件或目录。使用 `wildcard` 函数测试存在性。

这些函数为在Makefile中处理文件名提供了强大的工具，包括目录提取、后缀提取、名称添加前缀或后缀等操作。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 条件函数
这段文本介绍了四个提供条件扩展的函数，这些函数用于在Makefile中进行条件性的求值。这些函数的关键方面是，并非所有的参数在一开始都会被扩展。只有那些需要被扩展的参数才会被扩展。

1. **`$(if condition,then-part[,else-part])`：**
   if函数在函数上下文中提供对条件扩展的支持。第一个参数condition首先去除所有前导和尾随空格，然后被扩展。如果它扩展为任何非空字符串，则条件被视为真。如果它扩展为空字符串，则条件被视为假。

   如果条件为真，则第二个参数then-part被求值，并且这将用作整个if函数求值的结果。如果条件为假，则第三个参数else-part被求值，这将是if函数的结果。如果没有第三个参数，if函数求值为空（空字符串）。

   注意，只有then-part或else-part中的一个将被求值，而不是两者都被求值。因此，两者都可以包含副作用（例如shell函数调用等）。

2. **`$(or condition1[,condition2[,condition3…]])`：**
   or函数提供了一个“短路”OR操作。每个参数依次被扩展。如果一个参数扩展为非空字符串，则处理停止，扩展的结果是该字符串。如果在扩展所有参数之后，它们全部为假（空），则扩展的结果是空字符串。

3. **`$(and condition1[,condition2[,condition3…]])`：**
   and函数提供了一个“短路”AND操作。每个参数依次被扩展。如果一个参数扩展为空字符串，则处理停止，扩展的结果是空字符串。如果所有参数都扩展为非空字符串，则扩展的结果是最后一个参数的扩展。

4. **`$(intcmp lhs,rhs[,lt-part[,eq-part[,gt-part]]])`：**
   intcmp函数提供了对整数的数值比较的支持。这个函数在GNU make的Makefile条件中没有对应项。

   左手边lhs和右手边rhs被扩展并解析为十进制整数。剩余参数的扩展取决于数字左手边如何与数字右手边比较。

   如果没有进一步的参数，那么如果左手边和右手边不相等，该函数扩展为空，或者如果它们相等，则扩展为它们的数值。

   否则，如果左手边严格小于右手边，则intcmp函数将求值为第三个参数lt-part的扩展。如果两边相等，则intcmp函数将求值为第四个参数eq-part的扩展。如果左手边严格大于右手边，则intcmp函数将求值为第五个参数gt-part的扩展。

   如果gt-part缺失，则默认为eq-part。如果eq-part缺失，则默认为空字符串。因此，'$(intcmp 9,7,hello)'和'$(intcmp 9,7,hello,world,)'都求值为空字符串，而'$(intcmp 9,7,hello,world)'（注意world后面没有逗号）求值为'world'。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## let函数
`let` 函数提供了一种限制变量作用域的方法。在 `let` 表达式提供的文本中，对命名变量的赋值仅在该文本中有效，并且这种赋值不会影响任何外部作用域中的该命名变量。

此外，`let` 函数通过将所有未分配的值赋给最后一个命名变量来实现列表拆包。

`let` 函数的语法是：

```makefile
$(let var [var ...],[list],text)
```

首两个参数，`var` 和 `list`，在执行其他任何操作之前被扩展；请注意，最后一个参数 `text` 在此时不会被扩展。接下来，将 `list` 的扩展值的每个单词依次绑定到每个变量名 `var`，最终的变量名将被绑定到扩展列表的其余部分。换句话说，`list` 的第一个单词绑定到第一个变量 `var`，第二个单词绑定到第二个变量 `var`，依此类推。

如果 `var` 中的变量名比 `list` 中的单词数更多，那么剩余的 `var` 变量名将被设置为空字符串。如果 `var` 中的变量名比 `list` 中的单词数更少，则最后一个 `var` 将被设置为 `list` 中的所有剩余单词。

在 `let` 执行期间，`var` 中的变量是简单展开变量。

在所有变量都这样绑定之后，`text` 被扩展以提供 `let` 函数的结果。

例如，以下宏颠倒了作为其第一个参数给出的列表中单词的顺序：

```makefile
reverse = $(let first rest,$1,\
            $(if $(rest),$(call reverse,$(rest)) )$(first))

all: ; @echo $(call reverse,d c b a)
```

这将打印出 a b c d。当第一次调用时，`let` 将 `$1` 扩展为 `d c b a`。然后，它将 `first` 赋值为 `d` 并将 `rest` 赋值为 `c b a`。然后，它将展开 `if` 语句，其中 `$(rest)` 不为空，因此我们递归调用具有 `rest` 的 `reverse` 函数，该值现在为 `c b a`。递归调用 `let` 将 `first` 赋值为 `c`，将 `rest` 赋值为 `b a`。递归继续，直到 `let` 以单个值 `a` 被调用。在这里，`first` 是 `a`，`rest` 为空，因此我们不进行递归，而是简单地展开 `$(first)` 为 `a` 并返回，这样就添加了 `b`，等等。

在 `reverse` 调用完成后，`first` 和 `rest` 变量将不再设置。如果在此之前存在具有这些名称的变量，则它们不会受到 `reverse` 宏的扩展的影响。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## foreach函数
在GNU Make中，`foreach` 函数是一个强大的函数，用于对列表中的每个元素执行一些操作。它类似于编程语言中的循环结构。让我们来详细解释一下其语法和工作原理：

```makefile
$(foreach var, list, text)
```

- `var`：要在每次迭代中设置的变量的名称。
- `list`：`foreach` 函数将在其上迭代的项目列表。
- `text`：每次迭代时要扩展的文本，其中包含对变量 `var` 的引用。

工作原理如下：

1. `var` 逐一设置为扩展后的 `list` 中的每个单词。
2. 对 `text` 进行扩展，每次扩展时，将 `var` 的出现替换为 `var` 的当前值。
3. 将每次扩展的结果连接起来，用空格分隔，以生成最终的结果。

在你的例子中：

```makefile
dirs := a b c d
files := $(foreach dir,$(dirs),$(wildcard $(dir)/*))
```

- `var` 是 `dir`。
- `list` 是 `$(dirs)`，它扩展为 `a b c d`。
- `text` 是 `$(wildcard $(dir)/*)`。

对于每次迭代，`$(dir)` 取目录的值（`a`、`b`、`c`、`d`），而 `$(wildcard $(dir)/*)` 扩展为该目录中的文件列表。将这些结果连接到变量 `files` 中。

关于 `text` 复杂性，你确实可以通过给它一个额外的变量名来提高可读性，就像你在例子中使用 `find_files` 一样。

`foreach` 函数和 `let` 函数一样，对变量 `var` 没有永久影响；在 `foreach` 函数调用之后，其值和特性与之前一样。从 `list` 中取出的其他值在 `foreach` 执行期间仅在临时生效。在 `foreach` 执行期间，变量 `var` 是一个简单扩展的变量。如果在 `foreach` 函数调用之前未定义 `var`，则调用后它仍然是未定义的。

在使用导致变量名的复杂变量表达式时，必须小心，因为许多奇怪的东西都是有效的变量名，但可能不是你想要的。例如，

```makefile
files := $(foreach Esta-escrito-en-espanol!,b c ch,$(find_files))
```

可能会在 `find_files` 的值引用变量名为 ‘Esta-escrito-en-espanol!’ 的情况下有用，但更有可能是一个错误。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## file函数

`file` 函数允许 Makefile 读取或写入文件。支持两种写入模式：覆盖模式，其中文本写入文件的开头，任何现有内容都将丢失；以及追加模式，其中文本写入文件的末尾，保留现有内容。在这两种情况下，如果文件不存在，则会创建该文件。如果文件无法打开进行写入，或者写入操作失败，这将是致命错误。`file` 函数在写入文件时展开为空字符串。

在从文件读取时，`file` 函数展开为文件的内容，除了最后的换行符（如果存在）将被去除。尝试从不存在的文件读取将展开为空字符串。

`file` 函数的语法是：

```makefile
$(file op filename[,text])
```

在评估 `file` 函数时，首先展开所有参数，然后将按照 `op` 描述的模式打开由 `filename` 指示的文件。

操作符 `op` 可以是 >，表示文件将被覆盖为新内容；>>，表示文件的当前内容将被追加；或 <，表示将读取文件的内容。`filename` 指定要写入或读取的文件。操作符和文件名之间可以选择包含空格。

在读取文件时，如果提供了文本值，将是一个错误。

在写入文件时，文本将写入文件。如果文本尚未以换行符结束，则将写入最后的换行符（即使文本为空字符串）。如果根本没有给出文本参数，则什么都不会写入。

例如，`file` 函数在以下情况下可能很有用：如果您的构建系统具有有限的命令行大小，并且您的规则运行一个可以从文件中接受参数的命令。许多命令使用以下约定：以 @ 为前缀的参数指定包含更多参数的文件。然后，您可以以以下方式编写规则：

```makefile
program: $(OBJECTS)
        $(file >$@.in,$^)
        $(CMD) $(CMDFLAGS) @$@.in
        @rm $@.in
```

如果命令要求每个参数在输入文件的单独行上，您可能会这样编写规则：

```makefile
program: $(OBJECTS)
        $(file >$@.in) $(foreach O,$^,$(file >>$@.in,$O))
        $(CMD) $(CMDFLAGS) @$@.in
        @rm $@.in
```

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## call函数
`call` 函数在于它可以用于创建新的参数化函数。您可以将一个复杂的表达式写为变量的值，然后使用 `call` 函数以不同的值进行展开。

`call` 函数的语法是：

```makefile
$(call variable,param,param,…)
```

当 make 展开此函数时，它将每个 `param` 分配给临时变量 `$(1)`，`$(2)` 等。变量 `$(0)` 将包含 `variable`。参数的数量没有最大限制。也没有最小限制，但是没有参数使用 `call` 是没有意义的。

然后，`variable` 作为 make 变量在这些临时赋值的上下文中进行展开。因此，在 `variable` 的值中对 `$(1)` 的任何引用都将解析为 `call` 调用中的第一个参数。

请注意，`variable` 是变量的名称，而不是对该变量的引用。因此，通常在写它时不会使用 '$' 或括号。（但是，如果要使名称不是常量，可以在名称中使用变量引用。）

如果 `variable` 是内置函数的名称，则始终调用内置函数（即使同名的 make 变量也存在）。

`call` 函数在将参数分配给临时变量之前展开这些参数。这意味着包含对具有特殊扩展规则的内置函数的引用的变量值，例如 `foreach` 或 `if`，可能不会按您的预期工作。

以下是一些示例，这可能使事情更加清晰。

这个宏简单地颠倒了它的参数：

```makefile
reverse = $(2) $(1)

foo = $(call reverse,a,b)
```

在这里，`foo` 将包含 'b a'。

这个稍微有趣一点：它定义了一个在 PATH 中搜索程序第一次出现的宏：

```makefile
pathsearch = $(firstword $(wildcard $(addsuffix /$(1),$(subst :, ,$(PATH)))))

LS := $(call pathsearch,ls)
```

现在，变量 `LS` 包含 `/bin/ls` 或类似的值。

`call` 函数可以嵌套。每个递归调用都会获得其自己的本地值 `$(1)` 等，屏蔽了更高级别 `call` 的值。例如，这是一个 map 函数的实现：

```makefile
map = $(foreach a,$(2),$(call $(1),$(a)))
```

现在，您可以将通常只接受一个参数的函数（例如 `origin`）映射到一步中的多个值：

```makefile
o = $(call map,origin,o map MAKE)
```

最终，`o` 包含类似 'file file default' 的内容。

最后注意一下：在向 `call` 提供参数时，小心添加空格。与其他函数一样，包含在第二个及以后的参数中的任何空格都将被保留；这可能导致奇怪的效果。通常最安全的做法是在向 `call` 提供参数时删除所有不必要的空格。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## value函数

`value` 函数提供了一种在不展开变量的情况下使用变量值的方式。请注意，这并不会撤销已经发生的扩展；例如，如果您创建了一个简单扩展变量，那么其值在定义期间会被扩展；在这种情况下，`value` 函数将返回与直接使用变量相同的结果。

`value` 函数的语法是：

```makefile
$(value variable)
```

请注意，`variable` 是变量的名称，而不是对该变量的引用。因此，在编写它时通常不会使用 '$' 或括号。（但是，如果要使名称不是常量，可以在名称中使用变量引用。）

该函数的结果是一个包含变量值的字符串，而没有发生任何扩展。例如，在以下 makefile 中：

```makefile
FOO = $PATH

all:
        @echo $(FOO)
        @echo $(value FOO)
```

第一行输出将是 `ATH`，因为"$P"将被扩展为一个 make 变量，而第二行输出将是您的 `$PATH` 环境变量的当前值，因为 `value` 函数避免了扩展。

`value` 函数最常与 `eval` 函数一起使用（参见 `eval` 函数）。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## eval函数
`eval` 函数非常特殊：它允许您定义新的 Makefile 结构，这些结构不是常量，而是由评估其他变量和函数的结果构成。`eval` 函数的参数会先进行扩展，然后将该扩展的结果解析为 Makefile 语法。扩展的结果可以定义新的 make 变量、目标、隐含或显式规则等。

`eval` 函数的结果始终是空字符串；因此，它几乎可以放在 Makefile 的任何地方而不会导致语法错误。

重要的是要意识到 `eval` 参数被扩展两次；首先由 `eval` 函数，然后在解析为 Makefile 语法时再次扩展这些结果。这意味着在使用 `eval` 时，您可能需要为 "$" 字符提供额外级别的转义。`value` 函数（参见 `value` 函数）在这些情况下有时可能会很有用，以规避不希望的扩展。

以下是 `eval` 如何使用的示例；此示例结合了许多概念和其他函数。尽管在此示例中使用 `eval` 可能显得过于复杂，而不是仅编写规则，但请考虑两件事：首先，模板定义（在 `PROGRAM_template` 中）可能需要比这里更复杂；其次，您可以将此示例的复杂、“通用”部分放入另一个 Makefile，然后在所有个别的 Makefile 中进行包含。现在，您的个别 Makefile 就变得非常简单。

```makefile
PROGRAMS    = server client

server_OBJS = server.o server_priv.o server_access.o
server_LIBS = priv protocol

client_OBJS = client.o client_api.o client_mem.o
client_LIBS = protocol

# Everything after this is generic

.PHONY: all
all: $(PROGRAMS)

define PROGRAM_template =
 $(1): $$($(1)_OBJS) $$($(1)_LIBS:%=-l%)
 ALL_OBJS   += $$($(1)_OBJS)
endef

$(foreach prog,$(PROGRAMS),$(eval $(call PROGRAM_template,$(prog))))

$(PROGRAMS):
        $(LINK.o) $^ $(LDLIBS) -o $@

clean:
        rm -f $(ALL_OBJS) $(PROGRAMS)
```

在这个例子中，`eval` 函数用于通过模板生成多个程序的规则，以及将所有对象文件收集到 `ALL_OBJS` 中。这允许您在 Makefile 中重用通用规则，同时为每个程序定义特定的规则和依赖项。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## origin函数

`origin` 函数与大多数其他函数不同，它不操作变量的值；它告诉您关于变量的一些信息。具体而言，它告诉您变量的来源。

`origin` 函数的语法是：

```makefile
$(origin variable)
```

请注意，`variable` 是要查询的变量的名称，而不是对该变量的引用。因此，在编写它时，通常不会使用‘$’或括号。（但是，如果希望名称不是常量，可以在名称中使用变量引用。）

该函数的结果是一个字符串，告诉您变量 `variable` 是如何定义的：

- ‘undefined’：如果变量从未定义过。
- ‘default’：如果变量具有默认定义，通常与 `CC` 等一起使用。请注意，如果重新定义了默认变量，则 `origin` 函数将返回后续定义的源。
- ‘environment’：如果变量是从提供给 make 的环境中继承的。
- ‘environment override’：如果变量是从提供给 make 的环境中继承的，并且由于 ‘-e’ 选项而覆盖了 Makefile 中对变量的设置。
- ‘file’：如果变量是在 Makefile 中定义的。
- ‘command line’：如果变量是在命令行上定义的。
- ‘override’：如果变量是在 Makefile 中使用 `override` 指令定义的。
- ‘automatic’：如果变量是为每个规则的执行而定义的自动变量

这些信息主要用于确定是否要相信变量的值（除非你好奇）。例如，假设您有一个名为 `foo` 的 Makefile，其中包含另一个名为 `bar` 的 Makefile。如果运行命令 ‘make -f bar’，则希望变量 `bletch` 在 `bar` 中定义，即使环境中包含对 `bletch` 的定义。但是，如果在包含 `bar` 之前 `foo` 定义了 `bletch`，则不希望覆盖该定义。这可以通过在 `foo` 中使用 `override` 指令来完成，使该定义优先于 `bar` 中的后续定义；不幸的是，`override` 指令也会覆盖任何命令行定义。因此，`bar` 可以包含以下内容：

```makefile
ifdef bletch
ifeq "$(origin bletch)" "environment"
bletch = barf, gag, etc.
endif
endif
```

如果 `bletch` 已从环境中定义，这将对其进行重新定义。

如果要覆盖以前的 `bletch` 定义，即使它来自环境，在 ‘-e’ 下，您可以这样编写：

```makefile
ifneq "$(findstring environment,$(origin bletch))" ""
bletch = barf, gag, etc.
endif
```

在这里，如果 ‘$(origin bletch)’ 返回 ‘environment’ 或 ‘environment override’，则进行重新定义。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## flavor函数

`flavor` 函数，与 `origin` 函数一样，不对变量的值进行操作，而是提供有关变量的一些信息。具体而言，它告诉您变量的性质

`flavor` 函数的语法是：

```makefile
$(flavor variable)
```

请注意，`variable` 是要查询的变量的名称，而不是对该变量的引用。因此，在编写它时，通常不会使用‘$’或括号。（但是，如果希望名称不是常量，可以在名称中使用变量引用。）

该函数的结果是一个字符串，用于标识变量 `variable` 的性质：

- ‘undefined’：如果变量从未定义过。
- ‘recursive’：如果变量是递归展开的变量。
- ‘simple’：如果变量是简单展开的变量。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## 控制Make的函数

这些函数用于控制 make 的运行方式。通常，它们用于向 Makefile 的使用者提供信息，或者在检测到某种环境错误时导致 make 停止运行。

### $(error text…)

生成一个致命错误，其中消息是 `text`。请注意，无论何时评估此函数，都会生成错误。因此，如果将其放在一个规则内部或递归变量赋值的右侧，它不会立即评估。文本将在生成错误之前扩展。

例如，

```makefile
ifdef ERROR1
$(error error is $(ERROR1))
endif
```

如果 make 变量 `ERROR1` 被定义，将在读取 Makefile 时生成致命错误。或者，

```makefile
ERR = $(error found an error!)

.PHONY: err
err: ; $(ERR)
```

如果调用 `err` 目标，将在运行 make 时生成致命错误。

### $(warning text…)

此函数与上述的 `error` 函数类似，但 make 不会退出。相反，`text` 被扩展，并显示生成的消息，但继续处理 Makefile。

此函数扩展的结果是空字符串。

### $(info text…)

此函数仅将其（扩展后的）参数打印到标准输出。不会添加 Makefile 的名称或行号。此函数扩展的结果是空字符串。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## shell函数

`shell` 函数是与 make 中的其他函数（除了 `wildcard` 函数）不同的一种函数，因为它与 make 之外的世界进行通信。

`shell` 函数为 make 提供了与大多数 shell 中的反引号（‘`’）相似的功能：它执行命令扩展。这意味着它的参数是一个 shell 命令，并展开为该命令的输出。make 对结果进行的唯一处理是将每个换行符（或回车/换行对）转换为单个空格。如果有尾随的（回车和）换行，则将其简单地删除。

通过调用 `shell` 函数运行的命令会在扩展函数调用时运行。由于此函数涉及生成一个新的 shell，因此在递归展开的变量与简单展开的变量中使用 `shell` 函数的性能影响应仔细考虑。

`shell` 函数的一种替代方法是 ‘!=’ 赋值运算符；它提供类似的行为，但有细微的差异。‘!=’ 赋值运算符包含在较新的 POSIX 标准中。

使用 `shell` 函数或 ‘!=’ 赋值运算符后，其退出状态将放置在 `.SHELLSTATUS` 变量中。

以下是使用 `shell` 函数的一些示例：

```makefile
contents := $(shell cat foo)
```

将 `contents` 设置为文件 `foo` 的内容，每行之间用空格（而不是换行符）分隔。

```makefile
files := $(shell echo *.c)
```

将 `files` 设置为 ‘*.c’ 的扩展。除非 make 使用非常奇怪的 shell，否则这与 ‘$(wildcard *.c)’ 的结果相同（只要至少存在一个 ‘.c’ 文件）。

所有标记为导出的变量也将传递给由 `shell` 函数启动的 shell。可能会创建一个变量扩展循环的情况：考虑下面这个 Makefile：

```makefile
export HI = $(shell echo hi)
all: ; @echo $$HI
```

当 make 希望运行 recipe 时，它必须将变量 `HI` 添加到环境中；为了这样做，必须将其扩展。此变量的值需要调用 `shell` 函数，为了调用它，我们必须创建其环境。由于 `HI` 被导出，我们需要扩展它以创建其环境。依此类推。在这种晦涩的情况下，make 将使用从提供给 make 的环境中的变量值，否则如果没有，则使用空字符串，而不是循环或发出错误。这通常是你想要的；例如：

```makefile
export PATH = $(shell echo /usr/local/bin:$$PATH)
```

但是，在这里一开始就使用简单展开的变量（‘:=’）会更简单、更高效。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)

## guile函数
`guile` 函数在 GNU make 构建时启用了对 GNU Guile 作为嵌入式扩展语言的支持。`guile` 函数接受一个参数，首先由 make 正常扩展，然后传递给 GNU Guile 评估器。评估器的结果被转换为字符串，并用作 `guile` 函数在 Makefile 中的扩展。

你可以通过检查 `.FEATURES` 变量中是否包含单词 `guile` 来确定 GNU Guile 支持是否可用。

---

下一篇：[练习9 Makefile之运行参数](../practice-09/)，上一篇：[练习7 Makefile之条件部分](../practice-07/)，[目录](#makefile之使用函数)｜[首页](../README.md)