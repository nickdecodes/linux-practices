# Makefile之条件部分

- [温故知新](#温故知新)
- [条件示例](#条件示例)
- [条件句的语法](#条件句的语法)
- [测试标志的条件](#测试标志的条件)

---

下一篇：[练习8 Makefile之使用函数](../practice-08/)，上一篇：[练习6 Makefile之使用变量](../practice-06/)，[目录](#makefile之条件部分)｜[首页](../README.md)

## 温故知新

-   [练习1 理解编译的基本过程](../practice-01/)  
-   [练习2 创建基本的Makefile](../practice-02/)
-   [练习3 Makefile之简单介绍](../practice-03/)
-   [练习4 Makefile之显式规则](../practice-04/)
-   [练习5 Makefile之配方规则](../practice-05/)
-   [练习6 Makefile之使用变量](../practice-06/)

条件指令在Makefile中根据变量的值决定是否执行或忽略部分内容。条件可以比较一个变量的值与另一个变量的值，或将一个变量的值与一个常量字符串进行比较。条件指令控制make实际上在Makefile中看到的内容，因此不能用于控制执行时的操作步骤。

以下是一个简单的Makefile示例，演示了如何使用条件指令：

```makefile
# 定义变量
DEBUG = yes

# 使用条件指令
ifeq ($(DEBUG),yes)
    CFLAGS = -g
else
    CFLAGS = -O2
endif

# 默认目标
all: program

# 编译程序
program: main.c
    gcc $(CFLAGS) -o program main.c

# 清理生成的文件
clean:
    rm -f program
```

在上面的例子中，根据变量`DEBUG`的值，选择不同的编译选项`CFLAGS`。如果`DEBUG`的值是"yes"，则设置`CFLAGS`为"-g"，否则设置为"-O2"。这种条件判断发生在makefile 解析时，而不是在实际执行编译步骤时。

在命令行中执行`make`命令时，make会根据条件选择适当的编译选项来构建程序。

---

下一篇：[练习8 Makefile之使用函数](../practice-08/)，上一篇：[练习6 Makefile之使用变量](../practice-06/)，[目录](#makefile之条件部分)｜[首页](../README.md)

## 条件示例
这个条件示例告诉make在CC变量为'gcc'时使用一组库，否则使用另一组库。它通过控制规则中将使用哪一行配方来实现。结果是，将'CC=gcc'作为make的参数传递不仅会改变使用的编译器，还会改变链接的库。

```makefile
libs_for_gcc = -lgnu
normal_libs =

foo: $(objects)
ifeq ($(CC),gcc)
    $(CC) -o foo $(objects) $(libs_for_gcc)
else
    $(CC) -o foo $(objects) $(normal_libs)
endif
```

这个条件使用了三个指令：一个ifeq，一个else和一个endif。

ifeq指令开始条件，并指定条件。它包含两个由逗号分隔并用括号括起的参数。对两个参数执行变量替换，然后它们进行比较。ifeq之后的Makefile行将在两个参数匹配时执行，否则将被忽略。

else指令导致以下行在前面的条件失败时执行。在上面的例子中，这意味着只有在第一个备用链接命令不被使用时才会使用第二个备用链接命令。在条件中有else是可选的。

endif指令结束条件。每个条件必须以endif结束。无条件的Makefile文本随后出现。

正如这个例子所示，条件在文本级别起作用：条件的行被视为Makefile的一部分，或者根据条件被忽略。这就是为什么Makefile的更大的语法单元，比如规则，可能跨越条件的开始或结束的原因。

当变量CC的值为'gcc'时，上述示例的效果如下：

```makefile
foo: $(objects)
    $(CC) -o foo $(objects) $(libs_for_gcc)
```

当变量CC具有任何其他值时，效果如下：

```makefile
foo: $(objects)
    $(CC) -o foo $(objects) $(normal_libs)
```

也可以通过对变量赋值进行条件化，然后无条件地使用变量来获得等效的结果：

```makefile
libs_for_gcc = -lgnu
normal_libs =

ifeq ($(CC),gcc)
    libs=$(libs_for_gcc)
else
    libs=$(normal_libs)
endif

foo: $(objects)
    $(CC) -o foo $(objects) $(libs)
```

---

下一篇：[练习8 Makefile之使用函数](../practice-08/)，上一篇：[练习6 Makefile之使用变量](../practice-06/)，[目录](#makefile之条件部分)｜[首页](../README.md)

## 条件句的语法
这段文本描述了Makefile中条件指令的语法和用法。以下是对其中涉及的重要概念的简要总结：

1. **简单条件语法：**
   ```makefile
   conditional-directive
   text-if-true
   endif
   ```
   如果条件为真，则执行 `text-if-true` 部分；否则，忽略该部分。

2. **复杂条件语法：**
   ```makefile
   conditional-directive
   text-if-true
   else
   text-if-false
   endif
   ```
   或者多个 `else` 子句：
   ```makefile
   conditional-directive-one
   text-if-one-is-true
   else conditional-directive-two
   text-if-two-is-true
   else
   text-if-one-and-two-are-false
   endif
   ```
   当条件为真时执行 `text-if-true`，否则执行 `text-if-false`，或者执行其他 `else` 子句中的内容。

3. **条件指令的种类：**
   - `ifeq (arg1, arg2)`
   - `ifneq (arg1, arg2)`
   - `ifdef variable-name`
   - `ifndef variable-name`
   
   这些指令测试不同的条件。条件可以包含变量引用，会在比较前被展开。

4. **条件变量的测试：**
   - `ifeq` 和 `ifneq` 用于比较两个参数是否相等或不相等。
   - `ifdef` 测试一个变量是否已定义且非空。
   - `ifndef` 测试一个变量是否未定义或为空。

5. **条件中的变量展开：**
   - 变量引用在条件中会被展开。例如：`$(strip $(foo))` 用于测试变量 `foo` 是否为空。

6. **条件的影响：**
   - 条件影响make使用Makefile中的哪些行。如果条件为真，make读取 `text-if-true` 部分；如果条件为假，则完全忽略这些行。

7. **条件的评估时机：**
   - 条件在读取Makefile时被评估，因此不能在条件测试中使用自动变量，因为它们在执行规则时才被定义。

8. **条件的嵌套和include：**
   - 条件可以嵌套。`include` 可以在条件中使用，但是不允许在一个Makefile中开始条件然后在另一个Makefile中结束条件。

以上总结希望能帮助理解Makefile中条件指令的基本用法和语法。

---

下一篇：[练习8 Makefile之使用函数](../practice-08/)，上一篇：[练习6 Makefile之使用变量](../practice-06/)，[目录](#makefile之条件部分)｜[首页](../README.md)

## 测试标志的条件
这段文本介绍了如何使用条件指令以及`MAKEFLAGS` 变量和 `findstring` 函数来测试 `make` 命令标志，例如 `-t` 标志。这在 `touch` 不足以使文件看起来是最新的情况下非常有用。

`MAKEFLAGS` 将所有单字母选项（例如 `-t`）放入第一个单词，如果没有提供单字母选项，那么该单词将为空。为了更方便地处理这个情况，在开头添加一个值，以确保有一个单词，例如 ‘-$(MAKEFLAGS)’。

`findstring` 函数用于确定一个字符串是否出现在另一个字符串中。如果要测试 `-t` 标志，可以将 't' 作为第一个字符串，将 `MAKEFLAGS` 的第一个单词作为另一个字符串。

例如，下面的示例展示了如何设置使用 'ranlib -t' 来完成标记存档文件为最新的过程：

```makefile
archive.a: ...
ifneq (,$(findstring t,$(firstword -$(MAKEFLAGS))))
    +touch archive.a
    +ranlib -t archive.a
else
    ranlib archive.a
endif
```

在这个例子中，如果 `-t` 标志在 `MAKEFLAGS` 中，则执行 `touch archive.a` 和 `ranlib -t archive.a`，否则执行 `ranlib archive.a`。`+` 前缀标记这些配方行为“递归”，以便它们将被执行，即使使用了 `-t` 标志。

---

下一篇：[练习8 Makefile之使用函数](../practice-08/)，上一篇：[练习6 Makefile之使用变量](../practice-06/)，[目录](#makefile之条件部分)｜[首页](../README.md)