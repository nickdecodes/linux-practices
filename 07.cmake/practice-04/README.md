# 添加生成器表达式

- [温故知新](#温故知新)
- [使用生成器表达式添加编译器警告标志](#使用生成器表达式添加编译器警告标志)
    - [cmake-generator-expressions](#cmake-generator-expressions)
    - [cmake_minimum_required](#cmake_minimum_required)
    - [set函数](#set函数)
    - [target_compile_options](#target_compile_options)

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

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
- [练习3 添加库的使用要求](../practice-03/)
    - [`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)用于为特定目标（通常是可执行文件或库）设置编译选项（compiler options）
    - [`target_link_directories()`](https://cmake.org/cmake/help/latest/command/target_link_directories.html#command:target_link_directories)命令用于为特定目标（通常是可执行文件或库）指定链接目录，以帮助构建系统在链接目标时查找共享库或库文件的位置。
    - [`target_link_options()`](https://cmake.org/cmake/help/latest/command/target_link_options.html#command:target_link_options)是 CMake 中的一个命令，用于为特定目标（通常是可执行文件或库）设置链接器选项。
    - [`target_precompile_headers()`](https://cmake.org/cmake/help/latest/command/target_precompile_headers.html#command:target_precompile_headers)是 CMake 3.16 版本引入的一项功能，它用于为目标（通常是可执行文件或库）预编译头文件（precompiled headers）以提高构建性能。
    - [`target_sources()`](https://cmake.org/cmake/help/latest/command/target_sources.html#command:target_sources)用于向特定目标（通常是可执行文件或库）添加源文件，以便将这些源文件编译并链接到目标中。
    - [`target_compile_features()`](https://cmake.org/cmake/help/latest/command/target_compile_features.html#command:target_compile_features)是 CMake 中的一个命令，用于为特定目标（通常是可执行文件或库）设置编译器支持的 C++ 特性（C++ features）。


[`Generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))在构建系统生成期间进行评估，以生成特定于每个构建配置的信息。

[`Generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))在许多目标属性的上下文中允许，例如[`LINK_LIBRARIES`](https://cmake.org/cmake/help/latest/prop_tgt/LINK_LIBRARIES.html#prop_tgt:LINK_LIBRARIES), [`INCLUDE_DIRECTORIES`](https://cmake.org/cmake/help/latest/prop_tgt/INCLUDE_DIRECTORIES.html#prop_tgt:INCLUDE_DIRECTORIES),[`COMPILE_DEFINITIONS`](https://cmake.org/cmake/help/latest/prop_tgt/COMPILE_DEFINITIONS.html#prop_tgt:COMPILE_DEFINITIONS)和别的。当使用命令填充这些属性时也可以使用它们，例如 [`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries),[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories), [`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)和别的。

[`Generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7)) 可用于启用条件链接、编译时使用的条件定义、条件包含目录等。这些条件可以基于构建配置、目标属性、平台信息或任何其他可查询信息。

有不同类型的 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))包括逻辑、信息和输出表达式。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

## 使用生成器表达式添加编译器警告标志

一个常见的用法是 [`generator expressions`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))是有条件地添加编译器标志，例如语言级别或警告的标志。`INTERFACE` 一个很好的模式是将此信息与允许此信息传播的目标相关联。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

### cmake-generator-expressions

[`cmake-generator-expressions()`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))（CMake 生成器表达式）是一种在 CMake 构建系统中用于生成构建文件的特殊表达式。它们允许你在构建时根据不同的生成器和目标属性来生成不同的编译和链接选项。

Generator Expressions 可以在 CMake 的不同命令中使用，以便更精细地控制构建过程。这些表达式通常包含在 `$< >` 标记中，以区分它们与普通 CMake 变量和属性。

以下是一些常见的 Generator Expressions 的用法：

1.  **条件编译**：你可以使用 `if` 表达式来根据不同的构建配置或目标属性条件编译部分代码。例如：

    ```cmake
    target_compile_definitions(mytarget PRIVATE $<$<CONFIG:Debug>:DEBUG_MODE>)
    ```

    这将在 Debug 构建配置下添加 `DEBUG_MODE` 宏定义。

2.  **条件链接库**：你可以使用 `target_link_libraries` 命令中的 Generator Expressions 来根据不同的条件链接不同的库。例如：

    ```cmake
    target_link_libraries(mytarget PRIVATE $<$<CONFIG:Release>:optimized some_lib>)
    ```

    这将在 Release 构建配置下链接 `some_lib` 库。

3.  **选择源文件**：你可以使用 Generator Expressions 来根据不同条件选择要编译的源文件。例如：

    ```cmake
    set(sources
        source1.cpp
        $<$<CONFIG:Debug>:debug_source.cpp>
    )
    add_executable(mytarget ${sources})
    ```

    这将在 Debug 构建配置下编译 `debug_source.cpp`。

4.  **目标属性**：你可以使用 Generator Expressions 访问目标的属性，以便在不同情况下配置目标。例如：

    ```cmake
    target_compile_options(mytarget PRIVATE $<TARGET_PROPERTY:mylib,INTERFACE_COMPILE_OPTIONS>)
    ```

    这将为 `mytarget` 设置与 `mylib` 相同的接口编译选项。

Generator Expressions 在 CMake 中提供了灵活的方式来根据不同条件自定义构建过程，使构建系统适应不同的需求和平台。它们通常在条件编译、不同的构建配置和目标属性之间提供了精细的控制。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

### cmake_minimum_required

[`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required)已经在[练习1 构建一个基本项目](../practice-01/)介绍过，不在赘述。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

### set函数

在CMake中，[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)已经在[练习1 构建一个基本项目](../practice-01/)介绍过，不在赘述。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)

### target_compile_options

[`target_compile_options()`](https://cmake.org/cmake/help/latest/command/target_compile_options.html#command:target_compile_options)已经在[练习3 添加库的使用要求](../practice-03/)介绍过，不在赘述。

---
下一篇：[练习5 安装和测试](../practice-05/)，上一篇：[练习3 添加库的使用要求](../practice-03/)，[目录](#添加生成器表达式)｜[首页](../README.md)