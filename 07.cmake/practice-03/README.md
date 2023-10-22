# 添加库的使用要求

- [温故知新](#温故知新)
- [添加库的使用要求](#添加库的使用要求)
    - [CMAKE_CURRENT_SOURCE_DIR](#cmake_current_source_dir)
    - [target_compile_definitions](#target_compile_definitions)
    - [target_compile_options](#target_compile_options)
    - [target_include_directories](#target_include_directories)
    - [target_link_directories](#target_link_directories)
    - [target_link_options](#target_link_options)
    - [target_precompile_headers](#target_precompile_headers)
    - [target_sources](#target_sources)
- [使用接口库设置C++标准](#使用接口库设置c标准)
    - [add_library](#add_library)
    - [target_compile_features](#target_compile_features)
    - [target_link_libraries](#target_link_libraries)

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

## 温故知新

经过第一个练习，大家对于基本的使用应该已经掌握了，由于代码过多，在文档中详细介绍太过于啰嗦，大家可以自行下载代码参考

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
- [练习2 添加库](../practice-02/)
    - [`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)用于创建和配置一个库目标。
    - [`add_subdirectory()`](https://cmake.org/cmake/help/latest/command/add_subdirectory.html#command:add_subdirectory)是用于将其他源代码目录（通常是子目录）添加到当前 CMake 项目中，并在这些子目录中构建其他 CMake 项目。
    - [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)用于为一个目标（通常是可执行文件或库）指定它所依赖的其他库。
    - [`PROJECT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/PROJECT_SOURCE_DIR.html#variable:PROJECT_SOURCE_DIR)它包含了当前 CMake 项目的根源代码目录的路径。
    - [`if()`](https://cmake.org/cmake/help/latest/command/if.html#command:if)用于根据条件的真假来执行不同的 CMake 代码块。
    - [`option()`](https://cmake.org/cmake/help/latest/command/option.html#command:option)命令用于定义用户可配置的选项。
    - [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)用于为特定目标（通常是可执行文件或库）设置编译时宏定义（preprocessor definitions）。

至此，我们已经了解了在项目中创建和使用库。我们还将了解如何添加一些库的使用明细。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

## 添加库的使用要求

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### CMAKE_CURRENT_SOURCE_DIR

[`CMAKE_CURRENT_SOURCE_DIR`](https://cmake.org/cmake/help/latest/variable/CMAKE_CURRENT_SOURCE_DIR.html#variable:CMAKE_CURRENT_SOURCE_DIR)它存储了当前处理的 CMakeLists.txt 文件所在的目录的路径。这个变量可以用于引用当前处理文件的目录，通常用于构建项目中的源代码路径。

例如，假设你有以下的项目结构：

```
MyProject/
├── CMakeLists.txt
├── src/
│   ├── main.cpp
└── include/
    ├── myheader.h
```

在 `CMakeLists.txt` 中，你可以使用 `CMAKE_CURRENT_SOURCE_DIR` 来引用项目根目录下的源代码和头文件目录，如下所示：

```cmake
# 指定源文件路径
set(SOURCE_FILES
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp
)

# 指定头文件包含路径
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

# 生成可执行文件
add_executable(myapp ${SOURCE_FILES})
```

通过使用 `CMAKE_CURRENT_SOURCE_DIR`，你可以确保项目在不同的计算机上和不同的构建目录中都可以正确地找到源文件和头文件的路径，从而提高项目的可移植性。

注意，`CMAKE_CURRENT_SOURCE_DIR` 只引用当前处理的 CMakeLists.txt 文件所在的目录，如果你在子目录的 CMakeLists.txt 文件中使用它，它将指向子目录的路径。这使得在不同的 CMakeLists.txt 文件中引用不同的路径变得更加方便。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_compile_definitions

[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)已经在[练习2 添加库](../practice-02/)中介绍过，不在赘述

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_compile_options

[`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)用于为特定目标（通常是可执行文件或库）设置编译选项（compiler options）。这命令允许你指定目标的编译选项，例如编译器标志、警告选项等。

`target_compile_options` 命令的基本语法如下：

```cmake
target_compile_options(target
    [PRIVATE | PUBLIC | INTERFACE] option1 [option2 ...]
)
```

-   `target`: 要为其设置编译选项的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定编译选项的可见性级别。`PRIVATE` 表示编译选项仅对当前目标可见，`PUBLIC` 表示对依赖当前目标的目标可见，`INTERFACE` 表示只对依赖当前目标的目标可见。
-   `option1`, `option2`, 等等: 要设置的编译选项，通常是字符串，如 `-Wall` 或 `-O2`。

以下是一些示例用法：

1.  为一个目标设置单个编译选项：

```cmake
target_compile_options(myapp PRIVATE -Wall)
```

在这个示例中，`PRIVATE` 表示 `-Wall` 编译选项仅对 `myapp` 目标本身可见。

1.  为一个库目标设置多个编译选项：

```cmake
target_compile_options(mylib PUBLIC -O2 INTERFACE -fvisibility=hidden)
```

在这个示例中，`PUBLIC` 表示 `-O2` 编译选项对 `mylib` 目标及依赖于它的目标可见，而 `INTERFACE` 表示 `-fvisibility=hidden` 编译选项仅对依赖 `mylib` 的目标可见。

`target_compile_options` 命令非常有用，因为它允许你为不同的目标设置不同的编译选项，以根据项目的需求和目标的不同进行配置。这对于优化编译、开启或关闭特定功能以及确保代码在不同的编译环境中正确编译非常有用。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_include_directories

[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)已经在[练习1 构建一个基本项目](../practice-01/)介绍过，不在赘述。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_link_directories

[`target_link_directories()`](https://cmake.org/cmake/help/latest/command/target_link_directories.html#command:target_link_directories)命令用于为特定目标（通常是可执行文件或库）指定链接目录，以帮助构建系统在链接目标时查找共享库或库文件的位置。这在某些情况下可能会用到，但通常更推荐使用 `find_library` 或 `find_package` 来查找库，以避免硬编码链接目录。

`target_link_directories` 命令的基本语法如下：

```cmake
target_link_directories(target
    [PRIVATE | PUBLIC | INTERFACE] directory1 [directory2 ...]
)
```

-   `target`: 要为其指定链接目录的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定链接目录的可见性级别，控制哪些目录对依赖于此目标的目标可见。`PRIVATE` 表示链接目录仅对此目标本身可见，`PUBLIC` 表示对依赖此目标的目标和此目标本身可见，`INTERFACE` 表示只对依赖此目标的目标可见。
-   `directory1`, `directory2`, 等等: 要添加到链接目录的目录路径。

然而，在现代 CMake 中，推荐的做法是使用 `find_library` 命令或 `find_package` 命令来查找库，并使用 `target_link_libraries` 命令将库与目标关联。这种方法更加灵活，并可以确保构建系统可以在不同平台上正确地查找和链接库。

以下是一个示例，展示如何使用 `target_link_libraries` 命令来链接库，而不是使用 `target_link_directories`：

```cmake
find_library(LIBRARY_NAME NAMES mylibrary PATHS /path/to/library)
if (LIBRARY_NAME)
    target_link_libraries(myapp PRIVATE ${LIBRARY_NAME})
else()
    message(FATAL_ERROR "Library 'mylibrary' not found.")
endif()
```

在这个示例中，`find_library` 命令用于查找名为 `mylibrary` 的库文件，如果找到，它将通过 `target_link_libraries` 命令将库链接到 `myapp` 目标中。这种方法更加灵活，因为它不需要硬编码链接目录，而是依赖于构建系统的查找路径。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_link_options

[`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options)是 CMake 中的一个命令，用于为特定目标（通常是可执行文件或库）设置链接器选项。这命令允许你指定目标的链接器选项，如链接器标志、库搜索路径等。

`target_link_options` 命令的基本语法如下：

```cmake
target_link_options(target
    [PRIVATE | PUBLIC | INTERFACE] option1 [option2 ...]
)
```

-   `target`: 要为其设置链接器选项的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定链接器选项的可见性级别，控制哪些选项对依赖于此目标的目标可见。`PRIVATE` 表示链接器选项仅对当前目标可见，`PUBLIC` 表示对依赖当前目标的目标和当前目标本身可见，`INTERFACE` 表示只对依赖当前目标的目标可见。
-   `option1`, `option2`, 等等: 要设置的链接器选项，通常是字符串，如 `-L/path/to/lib` 或 `-lmylib`。

以下是一个示例用法：

```cmake
target_link_options(myapp PRIVATE -L/path/to/library -lmylib)
```

在这个示例中，`PRIVATE` 表示链接器选项 `-L/path/to/library -lmylib` 仅对 `myapp` 目标本身可见。

`target_link_options` 命令非常有用，因为它允许你为不同的目标设置不同的链接器选项，以根据项目的需求和目标的不同进行配置。这对于控制链接行为、指定库的搜索路径以及确保代码在不同的链接环境中正确工作非常有用。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_precompile_headers

[`target_precompile_headers()`](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html#command:target_precompile_headers)是 CMake 3.16 版本引入的一项功能，它用于为目标（通常是可执行文件或库）预编译头文件（precompiled headers）以提高构建性能。预编译头文件是一种机制，允许编译器在编译源文件之前预先编译一些常用的头文件，以加快构建速度。

`target_precompile_headers` 命令的基本语法如下：

```cmake
target_precompile_headers(target
    [PRIVATE | PUBLIC | INTERFACE]
    (REUSE <header_file> | DELETE)
)
```

-   `target`: 要为其设置预编译头文件的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定预编译头文件的可见性级别，控制哪些选项对依赖于此目标的目标可见。`PRIVATE` 表示预编译头文件仅对当前目标可见，`PUBLIC` 表示对依赖当前目标的目标和当前目标本身可见，`INTERFACE` 表示只对依赖当前目标的目标可见。
-   `(REUSE <header_file>)`: 指定要重用的预编译头文件的路径。这可以提高构建性能，因为它避免了不必要的重新编译。
-   `DELETE`: 用于删除之前设置的预编译头文件。

以下是一个示例用法：

```cmake
# 设置预编译头文件
target_precompile_headers(myapp PRIVATE REUSE "myheader.h")
```

在这个示例中，`PRIVATE` 表示 `myheader.h` 预编译头文件仅对 `myapp` 目标本身可见，而且会在构建中被重用。

使用 `target_precompile_headers` 命令可以提高项目的构建性能，特别是对于大型项目，因为它允许编译器在编译过程中节省时间。然而，支持这个功能的 CMake 版本可能有限，需要确保你的项目使用的 CMake 版本支持这个功能。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_sources

[`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)用于向特定目标（通常是可执行文件或库）添加源文件，以便将这些源文件编译并链接到目标中。这允许你为不同的目标指定不同的源文件，以根据项目的需求进行配置。

`target_sources` 命令的基本语法如下：

```cmake
target_sources(target
    [PRIVATE | PUBLIC | INTERFACE]
    source1 [source2 ...]
)
```

-   `target`: 要为其添加源文件的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`（可选）: 指定源文件的可见性级别，控制哪些源文件对依赖于此目标的目标可见。`PRIVATE` 表示源文件仅对当前目标可见，`PUBLIC` 表示对依赖当前目标的目标和当前目标本身可见，`INTERFACE` 表示只对依赖当前目标的目标可见。
-   `source1`, `source2`, 等等: 要添加到目标的源文件列表。

以下是一个示例用法：

```cmake
# 向可执行文件添加源文件
target_sources(myapp PRIVATE main.cpp utils.cpp)

# 向库目标添加源文件
target_sources(mylib PUBLIC library.cpp)
```

在这个示例中，`PRIVATE` 表示 `main.cpp` 和 `utils.cpp` 源文件仅对 `myapp` 目标本身可见，而 `PUBLIC` 表示 `library.cpp` 源文件对 `mylib` 目标及依赖于它的目标可见。

`target_sources` 命令非常有用，因为它允许你为不同的目标配置不同的源文件，以根据项目的需求和目标的不同进行定制。这对于组织大型项目、管理源文件和确保代码正确编译非常有用。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

## 使用接口库设置C++标准

现在我们已经将代码切换为更现代的方法，让我们演示一种为多个目标设置属性的现代技术。

让我们重构现有代码以使用`INTERFACE`库。我们将在下一步中使用该库来演示 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### add_library

[`add_library()`](https://cmake.org/cmake/help/latest/command/add_library.html#command:add_library)已经在[练习2 添加库](../practice-02/)介绍过，不在赘述。

`add_library` 命令的基本语法如下：

```cmake
add_library(target_name [SHARED | STATIC | MODULE]
    source1 [source2 ...]
)
```

-   `target_name`: 库的名称，你可以在后续的 `target_link_libraries` 命令中使用它来指定目标需要链接到这个库。
-   `SHARED | STATIC | MODULE`（可选）: 指定库的类型。可以是 `SHARED`（共享库/动态链接库，默认），`STATIC`（静态库），或 `MODULE`（CMake 在某些平台上的特定用途）。你可以选择其中一种类型或根据需要省略这个参数。
-   `source1`, `source2`, 等等: 源文件的列表，用于构建这个库。

以下是一些示例用法：

1.  创建一个共享库：

```cmake
add_library(mylib SHARED
    library.cpp
    utils.cpp
)
```

在这个示例中，`mylib` 是库的名称，`SHARED` 表示创建一个共享库，`library.cpp` 和 `utils.cpp` 是库的源文件。

1.  创建一个静态库：

```cmake
add_library(mylib STATIC
    library.cpp
    utils.cpp
)
```

在这个示例中，`mylib` 是库的名称，`STATIC` 表示创建一个静态库。

一旦使用 `add_library` 命令定义了一个库目标，你可以使用 `target_link_libraries` 命令将其他目标链接到该库。这使得你可以构建复杂的项目，包括可执行文件和库之间的链接关系。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_compile_features

[`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features)是 CMake 中的一个命令，用于为特定目标（通常是可执行文件或库）设置编译器支持的 C++ 特性（C++ features）。这个命令允许你明确地指定编译器应支持的 C++ 标准和特性，以确保代码能够在特定的编译环境中正确编译。

`target_compile_features` 命令的基本语法如下：

```cmake
target_compile_features(target
    PRIVATE | PUBLIC | INTERFACE
    feature1 [feature2 ...]
)
```

-   `target`: 要为其设置编译器特性的目标，通常是一个可执行文件或库。
-   `PRIVATE | PUBLIC | INTERFACE`: 指定特性的可见性级别，控制哪些特性对依赖于此目标的目标可见。`PRIVATE` 表示特性仅对当前目标可见，`PUBLIC` 表示对依赖此目标的目标和当前目标本身可见，`INTERFACE` 表示只对依赖此目标的目标可见。
-   `feature1`, `feature2`, 等等: 要为目标指定的 C++ 特性，例如 `cxx_std_11`、`cxx_auto_type`、`cxx_lambda` 等。

以下是一个示例用法：

```cmake
# 为可执行文件设置编译器特性
target_compile_features(myapp PRIVATE cxx_std_17 cxx_auto_type cxx_lambda)

# 为库目标设置编译器特性
target_compile_features(mylib PUBLIC cxx_std_11)
```

在这个示例中，`PRIVATE` 表示特性仅对 `myapp` 目标本身可见，而 `PUBLIC` 表示特性对 `mylib` 目标及依赖于它的目标可见。

使用 `target_compile_features` 命令有助于确保你的代码在编译时使用了正确的 C++ 标准和特性。这对于确保代码的兼容性和正确性非常重要，特别是当你的项目需要在不同的编译环境中构建时。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)

### target_link_libraries

[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)已经在[练习2 添加库](../practice-02/)介绍过，不在赘述。

---
下一篇：[练习4 添加生成器表达式](../practice-04/)，上一篇：[练习2 添加库](../practice-02/)，[目录](#添加库的使用要求)｜[首页](../README.md)