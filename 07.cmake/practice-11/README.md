# 添加导出配置

- [温故知新](#温故知新)

---
下一篇：[练习12 打包调试和发布](../practice-12/)，上一篇：[练习10 选择静态或共享库](../practice-10/)，[目录](#添加导出配置)｜[首页](../README.md)

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
- [练习8 添加自定义命令和生成的文件](../practice-08/)
- [练习9 打包安装程序](../practice-09/)
- [练习10 选择静态或共享库](../practice-10/)

在本教程中，我们添加了 CMake 安装项目库和标头的功能。在此期间， 我们添加了打包这些信息的功能，以便将其分发给其他人。[`Installing and Testing`](https://cmake.org/cmake/help/latest/guide/tutorial/Installing and Testing.html#guide:tutorial/Installing and Testing)[`Packaging an Installer`](https://cmake.org/cmake/help/latest/guide/tutorial/Packaging an Installer.html#guide:tutorial/Packaging an Installer)

下一步是添加必要的信息，以便其他 CMake 项目可以使用我们的项目，无论是来自构建目录、本地安装还是打包时。

第一步是更新我们的[`install(TARGETS)`](https://cmake.org/cmake/help/latest/command/install.html#targets)命令不仅可以指定 a `DESTINATION`，还可以指定`EXPORT`. 该`EXPORT`关键字生成一个 CMake 文件，其中包含用于从安装树导入安装命令中列出的所有目标的代码。因此，让我们继续通过 将命令更新为如下所示来显式地显示`EXPORT`库：`MathFunctions``install``MathFunctions/CMakeLists.txt`

- MathFunctions/CMakeLists.txt 

```cmake
set(installable_libs MathFunctions tutorial_compiler_flags)
if(TARGET SqrtLibrary)
  list(APPEND installable_libs SqrtLibrary)
endif()
install(TARGETS ${installable_libs}
        EXPORT MathFunctionsTargets
        DESTINATION lib)
# install include headers
install(FILES MathFunctions.h DESTINATION include)
```

现在我们已经`MathFunctions`导出了，我们还需要显式安装生成的`MathFunctionsTargets.cmake`文件。这是通过将以下内容添加到顶层的底部来完成的`CMakeLists.txt`：

- CMakeLists.txt 

```cmake
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)
```

此时您应该尝试运行 CMake。如果一切设置正确，您将看到 CMake 将生成如下错误：

```cmake
Target "MathFunctions" INTERFACE_INCLUDE_DIRECTORIES property contains
path:

  "/Users/robert/Documents/CMakeClass/Tutorial/Step11/MathFunctions"

which is prefixed in the source directory.
```

CMake 想说的是，在生成导出信息的过程中，它将导出一条与当前机器本质上相关的路径，并且在其他机器上无效。解决这个问题的方法是更新 `MathFunctions` [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)了解`INTERFACE`在构建目录和安装/包中使用它时需要不同的位置。这意味着转换 [`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)要求`MathFunctions`看起来像：

- MathFunctions/CMakeLists.txt 

```
target_include_directories(MathFunctions
                           INTERFACE
                            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
                            $<INSTALL_INTERFACE:include>
                           )
```

更新后，我们可以重新运行 CMake 并验证它是否不再发出警告。

此时，我们已经 CMake 正确打包了所需的目标信息，但我们仍然需要生成`MathFunctionsConfig.cmake`一个[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)命令可以找到我们的项目。因此，让我们继续将一个新文件添加到名为的项目的顶层， `Config.cmake.in`其中包含以下内容：

- 配置.cmake.in 

```cmake
@PACKAGE_INIT@

include ( "${CMAKE_CURRENT_LIST_DIR}/MathFunctionsTargets.cmake" )
```

然后，要正确配置和安装该文件，请将以下内容添加到顶层的底部`CMakeLists.txt`：

CMakeLists.txt 

```cmake
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)

include(CMakePackageConfigHelpers)
```

接下来，我们执行[`configure_package_config_file()`](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#command:configure_package_config_file)。此命令将配置提供的文件，但与标准有一些具体差异[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)方式。`@PACKAGE_INIT@`为了正确利用此功能，输入文件除了所需的内容外还应包含一行文本。该变量将被替换为将设置值转换为相对路径的代码块。这些新值可以通过相同的名称引用，但前面加上`PACKAGE_`前缀。

- CMakeLists.txt 

```cmake
install(EXPORT MathFunctionsTargets
  FILE MathFunctionsTargets.cmake
  DESTINATION lib/cmake/MathFunctions
)

include(CMakePackageConfigHelpers)
# generate the config file that includes the exports
configure_package_config_file(${CMAKE_CURRENT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/example"
  NO_SET_AND_CHECK_MACRO
  NO_CHECK_REQUIRED_COMPONENTS_MACRO
  )
```

这[`write_basic_package_version_file()`](https://cmake.org/cmake/help/latest/module/CMakePackageConfigHelpers.html#command:write_basic_package_version_file)接下来是。该命令写入一个文件，该文件由[`find_package()`](https://cmake.org/cmake/help/latest/command/find_package.html#command:find_package)，记录所需包的版本和兼容性。在这里，我们使用`Tutorial_VERSION_*` 变量并说它与 兼容`AnyNewerVersion`，这表示该版本或任何更高版本与请求的版本兼容。

- CMakeLists.txt 

```cmake
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake"
  VERSION "${Tutorial_VERSION_MAJOR}.${Tutorial_VERSION_MINOR}"
  COMPATIBILITY AnyNewerVersion
)
```

最后，设置要安装的两个生成的文件：

- CMakeLists.txt 

```cmake
install(FILES
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfig.cmake
  ${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsConfigVersion.cmake
  DESTINATION lib/cmake/MathFunctions
  )
```

至此，我们已经为项目生成了可重定位的 CMake 配置，可以在项目安装或打包后使用。如果我们希望我们的项目也可以从构建目录中使用，我们只需将以下内容添加到顶层的底部`CMakeLists.txt`：

- CMakeLists.txt 

```cmake
export(EXPORT MathFunctionsTargets
  FILE "${CMAKE_CURRENT_BINARY_DIR}/MathFunctionsTargets.cmake"
)
```

通过此导出调用，我们现在生成一个，允许其他项目使用构建目录中的`MathFunctionsTargets.cmake`配置，而无需安装它。`MathFunctionsConfig.cmake`

---
下一篇：[练习12 打包调试和发布](../practice-12/)，上一篇：[练习10 选择静态或共享库](../practice-10/)，[目录](#添加导出配置)｜[首页](../README.md)