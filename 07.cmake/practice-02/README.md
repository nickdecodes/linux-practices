# 添加库

- [温故知新](#温故知新)
- [创建库](#创建库)
    - [add_library](#add_library)
    - [add_subdirectory](#add_subdirectory)
    - [target_include_directories](#target_include_directories)
    - [target_link_libraries](#target_link_libraries)
    - [PROJECT_SOURCE_DIR](#project_source_dir)
- [添加选项](#添加选项)
    - [if](#if)
    - [option](#option)
    - [target_compile_definitions](#target_compile_definitions)

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

## 温故知新

**经过第一个练习，大家对于基本的使用应该已经掌握了，由于代码过多，在文档中详细介绍太过于啰嗦，大家可以自行下载代码参考**

- [练习1 构建一个基本项目](../practice-01/)
    - [`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required)是一个用于指定构建特定项目所需的最低CMake版本的函数。
    - [`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)函数用于定义一个项目，并指定项目的名称及相关属性。
    - [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)用于指定生成一个可执行文件的目标。
    - [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)用于指定项目中C++编译器要遵循的C++标准。
    - [`CMAKE_CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD_REQUIRED.html#variable:CMAKE_CXX_STANDARD_REQUIRED)用于指示是否要求编译器强制使用指定的C++标准。
    - [`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)函数用于设置变量的值。
    - [`<PROJECT-NAME>_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MAJOR.html#variable:_VERSION_MAJOR)通常用于访问项目的主要版本号。
    - [`<PROJECT-NAME>_VERSION_MINOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MINOR.html#variable:_VERSION_MINOR)通常用于访问项目的次要版本号。
    - [`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)用于在生成构建系统时复制文件并替换其中的变量值。
    - [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)用于指定一个目标（通常是可执行文件或库）的头文件包含路径。

至此，我们已经了解了如何使用 CMake 创建一个基本项目。在这一步中，我们将学习如何在项目中创建和使用库。我们还将了解如何使我们的库的使用变得可选。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

## 创建库

要在 CMake 中添加库，请使用[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)命令并指定哪些源文件应构成库。

我们可以用一个或多个子目录来组织项目，而不是将所有源文件放在一个目录中。在这种情况下，我们将专门为我们的库创建一个子目录。在这里，我们可以添加一个新 `CMakeLists.txt`文件和一个或多个源文件。在顶层 `CMakeLists.txt`文件中，我们将使用[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)命令将子目录添加到构建中。

创建库后，它将连接到我们的可执行目标 [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)和[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### add_library

[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)用于创建和配置一个库目标。这可以是一个共享库（Shared Library，也称为动态链接库）或一个静态库（Static Library）。`add_library` 命令的基本语法如下：

```cmake
add_library(targetName [SHARED | STATIC | MODULE] source1 [source2 ...])
```

- `targetName`: 要创建的库目标的名称，这是你为库指定的标识符。
- `SHARED`（可选）: 表示创建一个共享库（动态链接库）。
- `STATIC`（可选）: 表示创建一个静态库（静态链接库）。
- `MODULE`（可选）: 表示创建一个模块库。模块库是用于加载运行时插件的库，通常不常用。
- `source1`, `source2`, 等等: 要包含到库中的源代码文件列表。

以下是一些示例用法：

1. 创建一个共享库：

```cmake
add_library(mylib SHARED source1.cpp source2.cpp)
```

2. 创建一个静态库：

```cmake
add_library(mylib STATIC source1.cpp source2.cpp)
```

3. 创建一个库并包含多个源文件：

```cmake
add_library(mylib SHARED source1.cpp source2.cpp source3.cpp)
```

一旦你使用 `add_library` 命令创建了一个库目标，你可以将其链接到可执行文件或其他库目标，以便在构建过程中生成所需的目标文件。你还可以使用 `target_include_directories` 和 `target_link_libraries` 命令来配置库的包含路径和链接的库。

`add_library` 命令是创建库的关键步骤之一，它允许你在CMake项目中定义和配置库，以便在项目中使用。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### add_subdirectory

[`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)是用于将其他源代码目录（通常是子目录）添加到当前 CMake 项目中，并在这些子目录中构建其他 CMake 项目。这通常用于管理复杂项目结构，其中包含多个模块、库或可执行文件。

`add_subdirectory` 命令的基本语法如下：

```cmake
add_subdirectory(path_to_subdirectory [binary_dir])
```

- `path_to_subdirectory`: 子目录的路径，通常是相对于当前 CMakeLists.txt 文件的路径。
- `binary_dir`（可选）: 用于生成二进制文件的目录路径。如果省略 `binary_dir`，则默认为 `${CMAKE_BINARY_DIR}/path_to_subdirectory`。

使用 `add_subdirectory` 命令会导入指定子目录的 CMakeLists.txt 文件，并执行其中的构建逻辑。这将使子目录的内容成为当前项目的一部分，可以通过 `add_executable`、`add_library`、`target_include_directories` 和其他命令来访问和配置。

通常，`add_subdirectory` 用于将子目录中的库或可执行文件构建到当前项目中。这样，你可以在项目的不同部分之间共享代码和构建结果。

以下是一个示例，展示如何使用 `add_subdirectory` 命令：

假设你有以下项目结构：

```
MyProject/
├── CMakeLists.txt
├── main.cpp
├── library/
│   ├── CMakeLists.txt
│   ├── library.cpp
│   ├── library.h
```

在 MyProject 的 CMakeLists.txt 文件中，你可以包括子目录 `library` 并构建 `library`：

```cmake
add_subdirectory(library)
add_executable(myapp main.cpp)
target_link_libraries(myapp library)
```

这将在 `MyProject` 中构建 `myapp` 可执行文件，并链接到 `library`。

在子目录 `library` 的 CMakeLists.txt 文件中，你可以定义 `library`：

```cmake
add_library(library library.cpp library.h)
```

这将构建名为 `library` 的库目标，然后可以被 `myapp` 可执行文件链接到。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### target_include_directories

[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)已经在[练习1 构建一个基本项目](../practice-01/)中介绍过了，不在赘述

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### target_link_libraries

[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)用于为一个目标（通常是可执行文件或库）指定它所依赖的其他库。这命令允许你设置目标与其他库之间的链接关系，以便在构建过程中正确链接和链接库。

`target_link_libraries` 命令的基本语法如下：

```cmake
target_link_libraries(target
    library1 [library2 ...]
)
```

- `target`: 要为其指定链接库的目标，通常是一个可执行文件或库。
- `library1`, `library2`, 等等: 要链接到目标的库的名称，通常是通过 `add_library` 或 `add_executable` 命令创建的库目标。

以下是一些示例用法：

1. 链接一个可执行文件到一个库：

```cmake
add_executable(myapp main.cpp)
add_library(mylib STATIC library.cpp)
target_link_libraries(myapp mylib)
```

在这个示例中，`myapp` 可执行文件将被链接到 `mylib` 静态库。

2. 链接一个库到另一个库：

```cmake
add_library(mylib1 STATIC library1.cpp)
add_library(mylib2 STATIC library2.cpp)
target_link_libraries(mylib2 mylib1)
```

在这个示例中，`mylib2` 链接到 `mylib1` 静态库，这意味着在构建 `mylib2` 时，会将 `mylib1` 的代码和符号包含在其中。

`target_link_libraries` 命令允许你指定目标的依赖关系，确保在构建过程中正确地链接所需的库。这对于构建复杂项目，包括多个库和可执行文件，以及确保链接库的正确顺序非常重要。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### PROJECT_SOURCE_DIR

[`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR)它包含了当前 CMake 项目的根源代码目录的路径。这个变量存储了 CMakeLists.txt 文件所在的目录，也就是项目的起始目录。

通常，你可以在 CMake 项目中使用 `PROJECT_SOURCE_DIR` 变量来引用根源代码目录，以便指定源代码文件和其他资源的路径。这对于配置构建过程、包含源文件和头文件非常有用。

以下是一个示例，展示如何在 CMake 项目中使用 `PROJECT_SOURCE_DIR` 变量：

```cmake
# 设置源文件的路径，相对于 PROJECT_SOURCE_DIR
set(SOURCE_FILES
    ${PROJECT_SOURCE_DIR}/src/main.cpp
    ${PROJECT_SOURCE_DIR}/src/utils.cpp
)

# 包含头文件的路径，相对于 PROJECT_SOURCE_DIR
include_directories(${PROJECT_SOURCE_DIR}/include)

# 生成可执行文件
add_executable(myapp ${SOURCE_FILES})
```

在这个示例中，`PROJECT_SOURCE_DIR` 用于构建源文件的路径和包含头文件的路径。它提供了一个相对于项目根目录的路径，这使得项目的配置更具可移植性，因为它不依赖于特定的绝对路径。这种方式可以确保项目的可移植性，因为无论在哪个计算机上构建项目，都可以正确地引用源代码和头文件的路径。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

## 添加选项

现在让我们在 MathFunctions 库中添加一个选项，以允许开发人员选择自定义平方根实现或内置标准实现。虽然对于教程来说确实没有必要这样做，但对于较大的项目来说这是很常见的情况。

CMake 可以使用以下命令来完成此操作[`option()`](https://cmake.org/cmake/help/latest/command/option.html#command:option)命令。这为用户提供了一个变量，他们可以在配置 cmake 构建时更改该变量。此设置将存储在缓存中，以便用户每次在构建目录上运行 CMake 时无需设置该值。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### if

在 CMake 中，[`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)用于根据条件的真假来执行不同的 CMake 代码块。你可以使用 `if` 命令来根据不同的条件来配置项目，设置变量，或执行不同的命令。

`if` 命令的基本语法如下：

```cmake
if(condition)
    # 如果条件为真，执行这些命令
else()
    # 如果条件为假，执行这些命令
endif()
```

- `condition`: 用于判断真假的条件表达式。条件表达式可以包括比较、逻辑运算、变量的值等等。

以下是一些示例用法：

1. 使用 `if` 判断变量是否为真：

```cmake
set(my_var TRUE)

if(my_var)
    message("my_var is true")
else()
    message("my_var is false")
endif()
```

2. 使用 `if` 判断变量的值：

```cmake
set(my_number 42)

if(my_number EQUAL 42)
    message("my_number is equal to 42")
else()
    message("my_number is not equal to 42")
endif()
```

3. 使用 `if` 判断是否定义了变量：

```cmake
if(DEFINED my_var)
    message("my_var is defined")
else()
    message("my_var is not defined")
endif()
```

4. 使用 `if` 条件块来根据不同的操作系统进行配置：

```cmake
if(WIN32)
    # 针对 Windows 操作系统执行的命令
    message("This is a Windows system.")
elseif(UNIX)
    # 针对 Unix 操作系统（包括 Linux 和 macOS）执行的命令
    message("This is a Unix-like system.")
else()
    # 如果不在上述两者之间，执行的命令
    message("This is an unknown system.")
endif()
```

`if` 命令是 CMake 配置文件中的重要控制结构，允许你根据条件执行不同的操作，这在配置复杂项目和处理不同情况非常有用。根据项目的需求，你可以根据条件配置编译选项、变量值、。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### option

在 CMake 中，[`option()`](https://cmake.org/cmake/help/latest/command/option.html#command:option)命令用于定义用户可配置的选项。这些选项可以在 CMake 配置期间启用或禁用，并允许用户自定义项目的行为。通常，`option` 命令用于为项目提供一些开关，以决定是否启用或禁用特定的功能或行为。

`option` 命令的基本语法如下：

```cmake
option(option_name "option_description" [initial_value])
```

- `option_name`: 选项的名称，它是一个字符串，通常以大写字母命名，例如 "ENABLE_FEATURE_X"。
- `option_description`: 选项的描述，用于帮助用户理解该选项的用途。
- `initial_value`（可选）: 选项的初始值，通常是 `ON` 或 `OFF`，表示选项的默认状态。如果省略 `initial_value`，选项的默认状态为 `OFF`。

以下是一个示例用法：

```cmake
option(ENABLE_FEATURE_X "Enable Feature X" ON)
```

在这个示例中，`ENABLE_FEATURE_X` 是选项的名称，"Enable Feature X" 是选项的描述，`ON` 是初始值，表示默认情况下该选项处于启用状态。

在 CMakeLists.txt 文件中，你可以根据选项的状态来配置项目的行为。例如，你可以使用 `if` 命令来根据选项的状态执行不同的操作：

```cmake
if(ENABLE_FEATURE_X)
    # 如果选项 ENABLE_FEATURE_X 处于启用状态，执行这些操作
    message("Feature X is enabled.")
    # 其他配置选项和操作
else()
    # 如果选项未启用，执行这些操作
    message("Feature X is disabled.")
    # 其他配置选项和操作
endif()
```

用户可以在 CMake 配置期间使用 `-D` 选项来设置选项的值。例如，要禁用上述示例中的 "ENABLE_FEATURE_X" 选项，用户可以运行以下命令：

```sh
cmake -DENABLE_FEATURE_X:BOOL=OFF ..
```

这将在 CMake 配置期间将选项的值设置为 `OFF`，从而禁用 "Feature X"。

`option` 命令是配置 CMake 项目的一种方便方式，因为它允许用户自定义项目的行为，而不需要直接编辑 CMakeLists.txt 文件。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)

### target_compile_definitions

[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)用于为特定目标（通常是可执行文件或库）设置编译时宏定义（preprocessor definitions）。这命令允许你为目标指定编译时宏，这些宏会在代码编译时被传递给编译器，影响代码的编译行为。

`target_compile_definitions` 命令的基本语法如下：

```cmake
target_compile_definitions(target
    [PRIVATE | PUBLIC | INTERFACE] definition1 [definition2 ...]
)
```

- `target`: 要为其设置宏定义的目标，通常是一个可执行文件或库。
- `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定宏定义的可见性级别。`PRIVATE` 表示仅对当前目标可见，`PUBLIC` 表示对依赖当前目标的目标可见，`INTERFACE` 表示只对依赖当前目标的目标可见。
- `definition1`, `definition2`, 等等: 要设置的编译时宏定义，通常是字符串，如 `"DEBUG"` 或 `"ENABLE_FEATURE_X"`。

以下是一些示例用法：

1. 为一个目标设置单个宏定义：

```cmake
target_compile_definitions(myapp PRIVATE DEBUG)
```

在这个示例中，`PRIVATE` 表示 `DEBUG` 宏定义仅对 `myapp` 目标本身可见。

2. 为一个库目标设置多个宏定义：

```cmake
target_compile_definitions(mylib PUBLIC ENABLE_FEATURE_X PRIVATE NDEBUG)
```

在这个示例中，`PUBLIC` 表示 `ENABLE_FEATURE_X` 宏定义对 `mylib` 目标及依赖于它的目标可见，而 `PRIVATE` 表示 `NDEBUG` 宏定义仅对 `mylib` 本身可见。

`target_compile_definitions` 命令非常有用，因为它允许你在项目中设置编译时宏定义，以根据项目的不同配置或需求进行条件编译。这对于控制编译的行为、开启或关闭特定功能以及确保代码在不同的编译环境中正确工作非常有用。

---
下一篇：[练习3 添加库的使用要求](../practice-03/)，上一篇：[练习1 构建一个基本项目](../practice-01/)，[目录](#添加库)｜[首页](../README.md)