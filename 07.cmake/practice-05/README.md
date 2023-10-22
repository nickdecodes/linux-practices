# 安装和测试

- [安装规则](#安装规则)
    - [install](#install)
- [测试支持](#测试支持)
    - [enable_testing](#enable_testing)
    - [add_test](#add_test)
    - [function](#function)
    - [set_tests_properties](#set_tests_properties)
    - [ctest](#ctest)

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

## 温故知新

经过第一个练习，大家对于基本的使用应该已经掌握了，由于代码过多，在文档中详细介绍太过于啰嗦，大家可以自行下载代码参考

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

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

## 安装规则

通常，仅构建可执行文件是不够的，它还应该是可安装的。使用 CMake，我们可以使用以下命令指定安装规则 [`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)命令。在 CMake 中支持本地安装通常非常简单，只需指定安装位置以及要安装的目标和文件即可。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### install

[`install()`](https://cmake.org/cmake/help/latest/command/install.html#command:install)用于指定在构建完成后如何安装项目的文件和目标（可执行文件、库、头文件等）。通过使用 `install` 命令，你可以配置项目的安装目标目录以及要安装的文件和目标。

`install` 命令的基本语法如下：

```cmake
install(
    [TARGETS target1 target2 ...]
    [EXPORT export-name]
    [[ARCHIVE|LIBRARY|RUNTIME|INCLUDES|FRAMEWORK|BUNDLE|...] [DESTINATION <dir>]
    [PERMISSIONS permissions...]
    [CONFIGURATIONS [Debug|Release|...]]
    [COMPONENT <component>]
    [OPTIONAL]
    [EXCLUDE_FROM_ALL]
)
```

下面是一些常见的 `install` 命令的用法：

1.  **安装目标文件**：通过 `TARGETS` 关键字，你可以指定要安装的目标（可执行文件、库等）。例如：

```cmake
install(TARGETS myapp mylib
    DEST```

这会将 `myapp` 和 `mylib` 安装到 `/usr/local/bin` 目录。

2. **安装文件**：你可以使用 `FILES` 关键字来安装文件，如配置文件或数据文件。例如：

```cmake
install(FILES myconfig.conf
    DESTINATION /etc
)
```

这会将 `myconfig.conf` 安装到 `/etc` 目录。

1.  **安装目录**：使用 `DIRECTORY` 关键字可以将整个目录安装到目标目录中，包括目录下的文件和子目录。例如：

```cmake
install(DIRECTORY mydata
    DESTINATION /opt/myproject
)
```

这会将 `mydata` 目录及其内容安装到 `/opt/myproject` 目录。

1.  **设置文件权限**：你可以使用 `PERMISSIONS` 关键字设置安装的文件或目录的权限。例如：

```cmake
install(FILES myconfig.conf
    DESTINATION /etc
    PERMISSIONS OWNER_READ OWNER_WRITE GROUP_READ WORLD_READ
)
```

这会将 `myconfig.conf` 安装到 `/etc` 并设置相应的文件权限。

1.  **配置安装目录**：通过 `DESTINATION` 关键字，你可以指定安装的目标目录。
2.  **安装组件**：使用 `COMPONENT` 关键字可以将文件安装到不同的组件中。这对于安装具有不同用途的文件非常有用。
3.  **条件安装**：使用 `OPTIONAL` 关键字可以指定文件或目标是可选的，如果文件或目标不存在，则不会导致安装错误。
4.  **排除文件**：使用 `EXCLUDE_FROM_ALL` 关键字可以将文件或目标排除在 `make install` 的默认目标之外。

CMake 的 `install` 命令非常有用，因为它允许你定义项目的安装策略，以便将构建后的文件和目标复制到指定的位置，例如系统目录或自定义目录，以便用户或其他项目可以访问它们。这对于分发应用程序、库和配置文件非常有用。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

## 测试支持

CTest 提供了一种轻松管理项目测试的方法。可以通过以下方式添加测试[`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)命令。尽管本教程中没有明确介绍，但 CTest 和其他测试框架之间有很多兼容性，例如[`GoogleTest`](https://cmake.org/cmake/help/latest/module/GoogleTest.html#module:GoogleTest)。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### enable_testing

[`enable_testing()`](https://cmake.org/cmake/help/latest/command/enable_testing.html#command:enable_testing)用于启用测试支持，允许你在项目中定义和运行测试。测试是用于验证项目的功能和正确性的重要部分，特别是在软件开发过程中。通过启用测试支持，你可以使用CMake的测试框架来定义和运行各种测试。

`enable_testing` 命令没有参数，通常放在 CMakeLists.txt 文件的顶层。要启用测试支持，只需在项目的根目录的 CMakeLists.txt 文件中添加以下行：

```cmake
enable_testing()
```

一旦启用了测试支持，你可以使用以下命令来定义和运行测试：

1.  `add_test` 命令：用于定义一个测试，指定测试的名称和要运行的命令。

    ```cmake
    add_test(NAME mytest COMMAND myapp arg1 arg2)
    ```

    这将创建一个名为 `mytest` 的测试，该测试将运行 `myapp` 可执行文件，并传递 `arg1` 和 `arg2` 作为参数。

2.  `enable_testing` 命令：用于在构建目录中启用测试。通常，你只需要在项目的根 CMakeLists.txt 文件中调用一次 `enable_testing()`。

一旦测试已定义，你可以使用以下 CMake 的测试命令来运行测试：

-   `ctest` 命令：用于运行测试套件，显示测试的结果，并提供详细的测试报告。
-   `ctest --verbose` 命令：用于以详细模式运行测试，显示测试的详细输出。

测试是确保代码的正确性和稳定性的关键部分，特别是在大型项目中。通过启用测试支持并使用 `add_test` 命令，你可以轻松地集成测试流程到你的 CMake 项目中，以确保项目在开发和部署过程中具有一致的质量。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### add_test

[`add_test()`](https://cmake.org/cmake/help/latest/command/add_test.html#command:add_test)用于定义和创建测试。测试是用于验证项目的功能和正确性的重要部分，特别是在软件开发过程中。通过使用 `add_test` 命令，你可以定义不同类型的测试，如单元测试、集成测试等，以确保项目的各个部分都按预期工作。

`add_test` 命令的基本语法如下：

```cmake
add_test(NAME test_name [CONFIGURATIONS [Debug|Release|...]]
         COMMAND command [arg1 [arg2 ...]])
```

-   `NAME test_name`: 指定测试的名称，这是一个用于标识测试的字符串。
-   `CONFIGURATIONS [Debug|Release|...]`（可选）: 用于指定测试在哪些构建配置下运行。这可以根据不同的构建类型（Debug、Release 等）来配置测试。
-   `COMMAND command [arg1 [arg2 ...]]`: 指定要在测试中运行的命令和参数。这通常是你的测试程序、可执行文件或脚本。

以下是一个示例用法：

```cmake
add_test(NAME MyUnitTest COMMAND my_test_program)
```

在这个示例中，我们定义了一个名为 `MyUnitTest` 的测试，该测试将运行名为 `my_test_program` 的测试程序。你可以通过运行 `ctest` 来运行项目中定义的测试。

注意，`add_test` 命令通常在项目的 CMakeLists.txt 文件中使用，以便在构建和测试过程中执行所需的测试。

使用 `add_test` 命令可以确保项目的各个部分都按预期工作，并且有助于捕获潜在的问题和错误。测试是软件开发的一个重要组成部分，可以提高项目的质量和可维护性。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### function

[`function()`](https://cmake.org/cmake/help/latest/command/function.html#command:function)用于定义自定义函数（Custom Function）。自定义函数允许你在 CMakeLists.txt 文件中封装和重用一系列 CMake 命令和操作。这对于简化 CMake 脚本、提高可维护性和避免代码重复非常有用。

`function` 命令的基本语法如下：

```cmake
function(function_name arg1 arg2 ...)
  # CMake 命令和操作
endfunction()
```

-   `function_name`：自定义函数的名称，你可以在脚本中通过这个名称来调用函数。
-   `arg1`, `arg2`, ...：自定义函数的参数列表，可以有零个或多个参数。

以下是一个简单的示例，展示如何定义和使用自定义函数：

```cmake
function(print_hello_world)
  message("Hello, World!")
endfunction()

# 调用自定义函数
print_hello_world()
```

在这个示例中，我们定义了一个名为 `print_hello_world` 的自定义函数，该函数在调用时会打印 "Hello, World!" 消息。然后，我们通过 `print_hello_world()` 调用该函数。

自定义函数可以接受参数，并在函数体内使用这些参数进行操作。这允许你将通用操作封装在函数中，然后在不同的地方调用这些函数，以避免重复编写相同的代码。

自定义函数是 CMake 中组织和模块化脚本的强大工具，它们使你能够更轻松地管理项目的不同部分，并提高 CMake 脚本的可读性和维护性。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### set_tests_properties

[`set_tests_properties()`](https://cmake.org/cmake/help/latest/command/set_tests_properties.html#command:set_tests_properties)用于配置已定义的测试的属性。这可以用于修改测试的各种属性，如测试的标签、超时限制、环境变量、依赖关系等。

`set_tests_properties` 命令的基本语法如下：

```cmake
set_tests_properties(test_name1 test_name2 ...
    PROPERTIES
    property1 value1
    property2 value2
    ...
)
```

-   `test_name1`, `test_name2`, 等等: 要配置属性的测试的名称，可以一次配置多个测试。
-   `PROPERTIES`: 指定要设置的测试属性。
-   `property1`, `property2`, 等等: 要设置的属性的名称，如 `LABELS`、`TIMEOUT` 等。
-   `value1`, `value2`, 等等: 要设置的属性的值。

以下是一些常见的属性，可以通过 `set_tests_properties` 命令进行配置：

-   `LABELS`: 用于为测试指定标签，以便将测试按类别进行组织。例如：

    ```cmake
    set_tests_properties(mytest PROPERTIES LABELS "unit_tests")
    ```

-   `TIMEOUT`: 用于设置测试的超时限制，以确保测试在规定时间内完成。例如：

    ```cmake
    set_tests_properties(mytest PROPERTIES TIMEOUT 10)
    ```

-   `ENVIRONMENT`: 用于设置测试运行时的环境变量。例如：

    ```cmake
    set_tests_properties(mytest PROPERTIES ENVIRONMENT "MY_VARIABLE=my_value")
    ```

-   `DEPENDS`: 用于指定测试之间的依赖关系，以确保在运行测试之前先运行其他测试。例如：

    ```cmake
    set_tests_properties(mytest2 PROPERTIES DEPENDS mytest1)
    ```

通过使用 `set_tests_properties` 命令，你可以自定义测试的行为和属性，以满足项目的需求。这对于管理测试套件、自动化测试和测试结果报告非常有用。在实际项目中，通常会在 CMakeLists.txt 文件中定义测试，然后使用 `set_tests_properties` 命令来配置这些测试的属性。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)

### ctest

[`ctest`](https://cmake.org/cmake/help/latest/manual/ctest.1.html#manual:ctest(1))是 CMake 的测试驱动工具，用于运行和管理项目中定义的测试。它是与CMake一起提供的一个命令行工具，允许你自动运行测试，生成测试报告，以及执行各种测试任务。

下面是一些常见的用法和命令行选项：

1.  **运行所有测试**：

    ```bash
    ctest
    ```

    默认情况下，运行项目中定义的所有测试。

2.  **指定测试目录**：

    ```bash
    ctest --test-dir /path/to/tests
    ```

    指定测试所在的目录。

3.  **运行特定测试**：

    ```bash
    ctest -R test_name
    ```

    只运行名称匹配 `test_name` 的测试。这可以帮助你运行特定的测试套件或单个测试。

4.  **以详细模式运行测试**：

    ```bash
    ctest --verbose
    ```

    以详细模式运行测试，显示每个测试的输出。

5.  **生成测试报告**：

    ```bash
    ctest -T test
    ```

    生成测试报告，通常以 XML 或 JSON 格式。

6.  **运行特定构建配置的测试**：

    ```bash
    ctest -C Debug
    ```

    仅运行指定构建配置（例如，Debug 或 Release）的测试。

7.  **运行测试并在失败时停止**：

    ```bash
    ctest -E "test_pattern" -V
    ```

    使用 `-E` 选项和正则表达式模式来运行测试， `-V` 选项用于在测试失败时停止。

8.  **指定测试并设置超时限制**：

    ```bash
    ctest -R test_name -T Test --timeout 60
    ```

    运行特定测试并设置超时限制为 60 秒。

`ctest` 是一个非常强大的工具，它可以帮助你管理项目中的测试，运行它们，并生成详细的测试报告。通过将测试集成到项目中，你可以确保项目的质量和正确性，并及时发现问题。

---
下一篇：[练习6 添加对测试仪表板的支持](../practice-06/)，上一篇：[练习4 添加生成器表达式](../practice-04/)，[目录](#安装和测试)｜[首页](../README.md)