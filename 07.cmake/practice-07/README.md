# 添加系统自省

- [温故知新](#温故知新)
- [评估依赖项可用性](#评估依赖项可用性)
    - [CheckCXXSourceCompiles](#checkcxxsourcecompiles)
    - [target_compile_definitions](#target_compile_definitions)

---
下一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，上一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，[目录](#添加系统自省)｜[首页](../README.md)

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
- [练习4 添加生成器表达式](../practice-04/)
    - [`cmake-generator-expressions()`](https://cmake.org/cmake/help/latest/manual/cmake-generator-expressions.7.html#manual:cmake-generator-expressions(7))（CMake 生成器表达式）是一种在 CMake 构建系统中用于生成构建文件的特殊表达式。
- [练习5 安装和测试](../practice-05/)
    - [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用于指定在构建完成后如何安装项目的文件和目标（可执行文件、库、头文件等）。
    - [`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html#command:enable_testing)用于启用测试支持，允许你在项目中定义和运行测试。
    - [`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)用于定义和创建测试。
    - [`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)用于定义自定义函数（Custom Function）。
    - [`set_tests_properties()`](https://cmake.org/cmake/help/latest/command/set_tests_properties.html#command:set_tests_properties)用于配置已定义的测试的属性。
    - [`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))是 CMake 的测试驱动工具，用于运行和管理项目中定义的测试。
- [练习6 添加对测试仪表板的支持](../practice-06/)
    - [`include()`](https://cmake.org/cmake/help/latest/command/include.html#command:include)用于包含其他 CMake 文件中的内容，以便在当前 CMake 文件中重用和扩展配置。
    - [`CTest`](https://cmake.org/cmake/help/latest/module/CTest.html#module:CTest)是 CMake 的测试工具，用于管理和运行项目中定义的测试套件。

让我们考虑向我们的项目添加一些代码，这些代码取决于目标平台可能没有的功能。对于这个例子，我们将添加一些代码，具体取决于目标平台是否具有`log`和`exp` 功能。当然，几乎每个平台都有这些功能，但在本教程中假设它们并不常见。

---
下一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，上一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，[目录](#添加系统自省)｜[首页](../README.md)

## 评估依赖项可用性

---
下一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，上一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，[目录](#添加系统自省)｜[首页](../README.md)

### CheckCXXSourceCompiles

[`CheckCXXSourceCompiles`](https://cmake.org/cmake/help/latest/module/CheckCXXSourceCompiles.html#module:CheckCXXSourceCompiles)是 CMake 中的一个宏，用于检查给定的 C++源代码片段是否可以成功编译。这个宏通常用于测试编译器是否支持某些特定的C++特性或语法。

`CheckCXXSourceCompiles` 宏的基本语法如下：

```cmake
CheckCXXSourceCompiles(code result_var)
```

-   `code`: 要检查的C++源代码片段。
-   `result_var`: 一个CMake变量，用于存储检查的结果。如果源代码能够成功编译，`result_var` 将被设置为 `1`，否则将被设置为 `0`。

下面是一个示例用法：

```cmake
include(CheckCXXSourceCompiles)

set(test_code "#include <iostream>\nint main() { std::cout << \"Hello, World!\"; return 0; }")
CheckCXXSourceCompiles("${test_code}" CAN_COMPILE)

if (CAN_COMPILE)
    message("C++ code compiles successfully.")
else()
    message("C++ code compilation failed.")
endif()
```

在这个示例中，我们使用 `CheckCXXSourceCompiles` 宏来测试一个简单的C++代码片段，用于输出 "Hello, World!"。如果这段代码可以成功编译，`CAN_COMPILE` 变量将被设置为 `1`，否则将被设置为 `0`。

通常，`CheckCXXSourceCompiles` 宏用于检查编译器是否支持特定的C++语法或功能，以便在CMake配置中进行条件化处理。例如，你可以使用它来检查是否支持C++11或更高版本的标准，或者是否支持某些C++库或功能。

这个宏是CMake中的一个有用工具，可以在配置过程中检查编译器的功能，以确保项目的C++源代码可以正确编译。

---
下一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，上一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，[目录](#添加系统自省)｜[首页](../README.md)

### target_compile_definitions

[`target_compile_definitions()`](https://cmake.org/cmake/help/latest/command/target_compile_definitions.html#command:target_compile_definitions)已经在[练习2 添加库](../practice-02/)介绍过，不再赘述。

---
下一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，上一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，[目录](#添加系统自省)｜[首页](../README.md)