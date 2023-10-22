# 打包安装程序

- [温故知新](#温故知新)

---
下一篇：[练习10 选择静态或共享库](../practice-10/)，上一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，[目录](#打包安装程序)｜[首页](../README.md)

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

接下来假设我们想要将我们的项目分发给其他人以便他们可以使用它。我们希望在各种平台上提供二进制和源代码发行版。这与我们之前在 中所做的安装略有不同，我们之前安装的是从源代码构建的二进制文件。在此示例中，我们将构建支持二进制安装和包管理功能的安装包。为了实现这一目标，我们将使用 CPack 创建特定于平台的安装程序。具体来说，我们需要在顶级文件的底部添加几行。[`Installing and Testing`](https://cmake.org/cmake/help/latest/guide/tutorial/Installing and Testing.html#guide:tutorial/Installing and Testing)`CMakeLists.txt`

- CMakeLists.txt 

```
include(InstallRequiredSystemLibraries)
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/License.txt")
set(CPACK_PACKAGE_VERSION_MAJOR "${Tutorial_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${Tutorial_VERSION_MINOR}")
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)
```

这就是全部内容了。我们首先包括 [`InstallRequiredSystemLibraries`](https://cmake.org/cmake/help/latest/module/InstallRequiredSystemLibraries.html#module:InstallRequiredSystemLibraries)。该模块将包括当前平台项目所需的任何运行时库。接下来，我们将一些 CPack 变量设置为存储该项目的许可证和版本信息的位置。版本信息已在本教程前面设置，并且已`License.txt`包含在此步骤的顶级源目录中。这[`CPACK_SOURCE_GENERATOR`](https://cmake.org/cmake/help/latest/module/CPack.html#variable:CPACK_SOURCE_GENERATOR)变量选择源包的文件格式。

最后我们包括[`CPack module`](https://cmake.org/cmake/help/latest/module/CPack.html#module:CPack)它将使用这些变量和当前系统的一些其他属性来设置安装程序。

下一步是以通常的方式构建项目，然后运行 [`cpack`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#manual:cpack(1))可执行的。要构建二进制发行版，请从二进制目录运行：

```bash
cpack
```

要指定生成器，请使用该[`-G`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#cmdoption-cpack-G)选项。对于多配置构建，请使用[`-C`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#cmdoption-cpack-C)来指定配置。例如：

```bash
cpack -G ZIP -C Debug
```

有关可用生成器的列表，请参阅[`cpack-generators(7)`](https://cmake.org/cmake/help/latest/manual/cpack-generators.7.html#manual:cpack-generators(7))或致电 . 一个[`cpack --help`](https://cmake.org/cmake/help/latest/manual/cpack.1.html#cmdoption-cpack-h)[`archive generator`](https://cmake.org/cmake/help/latest/cpack_gen/archive.html#cpack_gen:CPack Archive Generator)*就像 ZIP 一样，它会创建所有已安装*文件 的压缩存档。

要创建完整源代码树的存档，您可以输入：

```bash
cpack --config CPackSourceConfig.cmake
```

或者，从 IDE运行或右键单击目标 。`make package``Package``Build Project`

运行二进制目录中找到的安装程序。然后运行已安装的可执行文件并验证其是否有效。

---
下一篇：[练习10 选择静态或共享库](../practice-10/)，上一篇：[练习8 添加自定义命令和生成的文件](../practice-08/)，[目录](#打包安装程序)｜[首页](../README.md)