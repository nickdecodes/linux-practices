# 添加对测试仪表板的支持

- [温故知新](#温故知新)
- [将结果发送到测试仪表板](#将结果发送到测试仪表板)
    - [ctest](#ctest)
    - [include](#include)
    - [CTest工具](#ctest工具)

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)

## 温故知新

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
- [练习4 添加生成器表达式](../practice-04/)
    - [`cmake-generator-expressions()`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))（CMake 生成器表达式）是一种在 CMake 构建系统中用于生成构建文件的特殊表达式。
- [练习5 安装和测试](../practice-05/)
    - [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用于指定在构建完成后如何安装项目的文件和目标（可执行文件、库、头文件等）。
    - [`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html#command:enable_testing)用于启用测试支持，允许你在项目中定义和运行测试。
    - [`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)用于定义和创建测试。
    - [`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)用于定义自定义函数（Custom Function）。
    - [`set_tests_properties()`](https://cmake.org/cmake/help/latest/command/set_tests_properties.html#command:set_tests_properties)用于配置已定义的测试的属性。
    - [`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))是 CMake 的测试驱动工具，用于运行和管理项目中定义的测试。


添加对将测试结果提交到仪表板的支持很简单。[我们已经在测试支持](https://cmake.org/cmake/help/latest/guide/tutorial/Installing and Testing.html#tutorial-testing-support)中为我们的项目定义了许多测试 。现在我们只需运行这些测试并将它们提交到 CDash 即可。

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)

## 将结果发送到测试仪表板

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)

### ctest

[`ctest()`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))已经在[练习5 安装和测试](../practice-05/)介绍过，不再赘述。

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)

### include

[`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)用于包含其他 CMake 文件中的内容，以便在当前 CMake 文件中重用和扩展配置。这有助于组织和模块化 CMakeLists.txt 文件，以提高可维护性和减少重复的配置。

`include` 命令的基本语法如下：

```cmake
include(filename)
```

-   `filename`：要包含的 CMake 文件的名称，通常是相对于当前 CMakeLists.txt 文件的路径或绝对路径。

包含的 CMake 文件可以包含各种 CMake 命令、变量定义、函数和宏等配置信息。一旦包含了文件，它的内容将被合并到包含它的 CMake 文件中，并在构建过程中执行。

以下是一些示例用法：

1.  **包含相对路径的文件**：

    ```cmake
    include(subdir/myfile.cmake)
    ```

    这将包含当前 CMakeLists.txt 文件所在目录下的 "subdir/myfile.cmake" 文件。

2.  **包含绝对路径的文件**：

    ```cmake
    include(/path/to/myfile.cmake)
    ```

    这将包含指定路径上的 "myfile.cmake" 文件。

3.  **包含项目中的通用配置文件**：

    ```cmake
    include(ConfigCommon.cmake)
    ```

    这可以用于包含项目中的通用配置文件，以确保多个 CMakeLists.txt 文件可以共享相同的配置。

`include` 命令通常用于将重复的配置提取到单独的 CMake 文件中，以便在不同的项目部分或不同的子项目中重复使用。这有助于减少代码重复，提高可维护性，并使项目的配置更具模块化。通常，包含的文件可以定义变量、函数、宏，或者执行各种配置操作，以便项目的构建和安装得以正确执行。

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)

### CTest工具

[`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)是 CMake 的测试工具，用于管理和运行项目中定义的测试套件。CTest 通常与 CMake 一起使用，它允许你自动运行各种类型的测试，生成详细的测试报告，以及进行测试相关的任务。CTest 是非常有用的工具，特别是在大型项目中，用于确保项目的各个部分都按预期工作。

以下是一些 CTest 的常见用法和功能：

1.  **运行测试套件**：CTest 可以运行项目中定义的测试套件，包括单元测试、集成测试和功能测试。
2.  **测试结果报告**：CTest 生成详细的测试报告，包括测试的结果、执行时间、错误消息和警告。这有助于识别和解决问题。
3.  **并行测试**：CTest 允许同时运行多个测试，以加快测试的执行速度。你可以配置并行测试的数量。
4.  **超时处理**：CTest 允许你为测试设置超时限制，以确保测试在规定时间内完成。如果测试超时，CTest 将标记它为失败。
5.  **测试标签**：你可以为测试定义标签，以便将测试按类别进行组织和筛选。这对于管理大量测试非常有用。
6.  **测试数据驱动**：CTest 支持数据驱动测试，允许你为测试提供不同的输入数据，并重复运行测试。
7.  **持续集成**：CTest 可以与持续集成系统（如Jenkins、Travis CI、CircleCI等）集成，以在每次代码提交或构建时运行测试并生成报告。
8.  **自定义测试**：你可以定义自己的测试，包括在CMakeLists.txt文件中使用`add_test`命令定义测试，并在CTest中运行。

运行CTest通常包括以下步骤：

1.  构建项目：使用CMake配置和生成项目的构建系统。
2.  运行CTest：使用CTest工具来运行测试套件。
3.  生成报告：CTest生成详细的测试报告，显示每个测试的结果。
4.  查看和分析报告：你可以查看报告，识别失败的测试，并分析错误消息以修复问题。

CTest是一个强大的工具，对于确保项目的质量和稳定性非常有用。通过集成测试到项目中，你可以自动化测试过程，快速发现问题，减少手动测试的工作，并确保代码的正确性。

---
下一篇：[练习7 添加系统自省](../practice-07/)，上一篇：[练习5 安装和测试](../practice-05/)，[目录](#添加对测试仪表板的支持)｜[首页](../README.md)