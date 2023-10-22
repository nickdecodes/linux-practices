# 添加自定义命令和生成的文件

- [温故知新](#温故知新)

---
下一篇：[练习9 打包安装程序](../practice-09/)，上一篇：[练习7 添加系统自省](../practice-07/)，[目录](#添加自定义命令和生成的文件)｜[首页](../README.md)

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
- [练习7 添加系统自省](../practice-07/)
    - [`CheckCXXSourceCompiles`](https://cmake.org/cmake/help/latest/module/CheckCXXSourceCompiles.html#module:CheckCXXSourceCompiles)是 CMake 中的一个宏，用于检查给定的 C++源代码片段是否可以成功编译。

假设，出于本教程的目的，我们决定永远不想使用平台`log`和`exp`函数，而是希望生成一个预计算值表以在函数中使用`mysqrt`。在本节中，我们将在构建过程中创建表，然后将该表编译到我们的应用程序中。

首先，让我们删除对`MathFunctions/CMakeLists.txt`中和`exp`函数 的检查。`HAVE_LOG`然后删除和 `HAVE_EXP`from的检查`mysqrt.cxx`。同时，我们可以删除 .`#include <cmath>`

在`MathFunctions`子目录中，已经提供了一个名为 的新源文件 `MakeTable.cxx`来生成表。

查看该文件后，我们可以看到该表是作为有效的 C++ 代码生成的，并且输出文件名作为参数传入。

下一步是创建`MathFunctions/MakeTable.cmake`. 然后，将适当的命令添加到文件中以构建`MakeTable`可执行文件，然后将其作为构建过程的一部分运行。需要一些命令来完成此操作。

首先，我们添加一个可执行文件`MakeTable`。

- MathFunctions/MakeTable.cmake 

```cmake
add_executable(MakeTable MakeTable.cxx)
```

创建可执行文件后，我们`tutorial_compiler_flags`使用以下命令将其添加到可执行文件中[`target_link_libraries()`](https://cmake.org/cmake/help/latest/command/target_link_libraries.html#command:target_link_libraries)。

- MathFunctions/MakeTable.cmake 

```cmake
target_link_libraries(MakeTable PRIVATE tutorial_compiler_flags)
```

然后我们添加一个自定义命令，指定如何`Table.h` 通过运行 MakeTable 来生成。

- MathFunctions/MakeTable.cmake 

```cmake
add_custom_command(
  OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  COMMAND MakeTable ${CMAKE_CURRENT_BINARY_DIR}/Table.h
  DEPENDS MakeTable
  )
```

接下来我们必须让 CMake 知道这`mysqrt.cxx`取决于生成的文件`Table.h`。这是通过将生成的文件添加`Table.h`到库的源列表中来完成的`SqrtLibrary`。

- MathFunctions/CMakeLists.txt 

```cmake
  add_library(SqrtLibrary STATIC
              mysqrt.cxx
              ${CMAKE_CURRENT_BINARY_DIR}/Table.h
              )
```

我们还必须将当前的二进制目录添加到包含目录列表中，`Table.h`以便`mysqrt.cxx`.

- MathFunctions/CMakeLists.txt 

```cmake
  target_include_directories(SqrtLibrary PRIVATE
                             ${CMAKE_CURRENT_BINARY_DIR}
                             )

  # link SqrtLibrary to tutorial_compiler_flags
```

作为最后一步，我们需要 `MakeTable.cmake`在`MathFunctions/CMakeLists.txt`.

- MathFunctions/CMakeLists.txt 

```cmake
  include(MakeTable.cmake)
```

现在让我们使用生成的表。首先，修改`mysqrt.cxx`以包含 `Table.h`. 接下来，我们可以重写该`mysqrt`函数以使用该表：

- MathFunctions/mysqrt.cxx 

```cpp
double mysqrt(double x)
{
  if (x <= 0) {
    return 0;
  }

  // use the table to help find an initial value
  double result = x;
  if (x >= 1 && x < 10) {
    std::cout << "Use the table to help find an initial value " << std::endl;
    result = sqrtTable[static_cast<int>(x)];
  }

  // do ten iterations
  for (int i = 0; i < 10; ++i) {
    if (result <= 0) {
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
    std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
  }

  return result;
}
}
}
```

跑过[`cmake`](https://cmake.org/cmake/help/latest/manual/cmake.1.html#manual:cmake(1))可执行文件或 [`cmake-gui`](https://cmake.org/cmake/help/latest/manual/cmake-gui.1.html#manual:cmake-gui(1))配置项目，然后使用您选择的构建工具构建它。

构建此项目时，它将首先构建`MakeTable`可执行文件。然后它将运行`MakeTable`以生成`Table.h`. 最后，它将编译`mysqrt.cxx`其中包含的内容`Table.h`以生成 `MathFunctions`库。

运行可执行文件并验证它是否正在使用该表。

---
下一篇：[练习9 打包安装程序](../practice-09/)，上一篇：[练习7 添加系统自省](../practice-07/)，[目录](#添加自定义命令和生成的文件)｜[首页](../README.md)