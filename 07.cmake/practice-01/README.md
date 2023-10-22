# 构建一个基本项目

- [必不可少的命令](#必不可少的命令)
    - [cmake_minimum_required](#cmake_minimum_required)
    - [project](#project)
    - [add_executable](#add_executable)
    - [初始化项目](#初始化项目)
- [指定C++标准](#指定c标准)
    - [CMAKE_CXX_STANDARD](#cmake_cxx_standard)
    - [CMAKE_CXX_STANDARD_REQUIRED](#cmake_cxx_standard_required)
    - [set函数](#set函数)
    - [优化项目指定标准](#优化项目指定标准)
- [添加版本号和配置的头文件](#添加版本号和配置的头文件)
    - [_VERSION_MAJOR](#_version_major)
    - [_VERSION_MINOR](#_version_minor)
    - [configure_file](#configure_file)
    - [target_include_directories](#target_include_directories)
    - [优化项目版本号并配置头文件](#优化项目版本号并配置头文件)

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

本文将介绍 CMake 的一些基本语法、命令和变量。介绍这些概念后，我们将完成一个简单的 CMake 项目。

最基本的 CMake 项目是从单个源代码文件构建的可执行文件。对于像这样的简单项目，`CMakeLists.txt`只需要一个包含三个命令的文件即可。

>   **注意：**虽然 CMake 支持大写、小写和混合大小写命令，但首选小写命令，并将在整个教程中使用。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

## 必不可少的命令

最基础的 CMakeLists.txt 一定会首先使用以下几个命令

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### cmake_minimum_required

[`cmake_minimum_required()`](https://cmake.org/cmake/help/latest/command/cmake_minimum_required.html#command:cmake_minimum_required)是一个用于指定构建特定项目所需的最低CMake版本的函数。这个函数应该在你的CMakeLists.txt文件的开头调用，以确保所使用的CMake版本与项目的要求兼容。

以下是`cmake_minimum_required()`函数的基本语法：

```cmake
cmake_minimum_required(VERSION major.minor [FATAL_ERROR])
```

-   `major.minor`：指定所需的最低CMake版本，格式为"major.minor"。例如，如果你需要CMake 3.10或更高版本，你可以指定`3.10`。
-   `FATAL_ERROR`（可选）：如果包括`FATAL_ERROR`参数，CMake会在不满足最低要求版本时生成错误并停止配置项目。如果省略此参数，CMake会生成警告并继续配置。

以下是一个在CMakeLists.txt文件中使用`cmake_minimum_required()`的示例：

```cmake
cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
```

在这个示例中，指定了CMake版本3.10作为最低要求版本，如果使用较低版本的CMake进行项目配置，将生成致命错误并停止配置过程。

在CMakeLists.txt文件中包括`cmake_minimum_required()`是一种良好的习惯，以确保项目的用户或开发人员具备兼容的CMake版本来构建项目。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### project

[`project()`](https://cmake.org/cmake/help/latest/command/project.html#command:project)函数用于定义一个项目，并指定项目的名称及相关属性。这个函数通常位于CMakeLists.txt文件的开头，用于设置项目的名称和其他信息。下面是 `project()` 函数的基本语法：

```cmake
project(ProjectName [CXX] [C] [Languages...])
```

-   `ProjectName`: 项目的名称，是一个必需的参数。这将成为你的项目的名称标识符。
-   `[CXX]`: 指示该项目将使用C++编程语言。这是一个可选参数，如果你的项目是C++项目，通常会包含它。
-   `[C]`: 指示该项目将使用C编程语言。这是一个可选参数，如果你的项目是C项目，通常会包含它。
-   `[Languages...]`: 允许你指定项目使用的其他编程语言。这是一个可选参数。

下面是一个示例，演示如何使用 `project()` 函数：

```cmake
project(MyCMakeProject CXX)
```

在这个示例中，项目的名称被设置为 "MyCMakeProject"，并指定该项目将使用C++编程语言。

你可以根据你的项目的需要来自定义 `project()` 函数的参数，以确保CMake正确识别和配置你的项目。此函数还可以用于设置其他项目属性，如版本信息和描述等。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### add_executable

 [`add_executable()`](https://cmake.org/cmake/help/latest/command/add_executable.html#command:add_executable)用于指定生成一个可执行文件的目标。这个函数将源代码文件编译成一个可执行文件，并可以为该可执行文件指定名称以及其所需的源代码文件列表。

以下是 `add_executable()` 函数的基本语法：

```cmmake
add_executable(targetName source1 [source2 ...])
```

-   `targetName`: 可执行文件的目标名称，你可以自定义它，这将是在构建过程中生成的可执行文件的名称。
-   `source1`, `source2`, 等等: 源代码文件的列表，这些文件将被编译以生成可执行文件。通常，你会列出你的项目的源文件，例如 `.cpp` 文件。

以下是一个示例，演示如何使用 `add_executable()` 函数来创建一个名为 "myapp" 的可执行文件：

```cmake
add_executable(myapp main.cpp helper.cpp)
```

在这个示例中，`add_executable()` 函数将编译 `main.cpp` 和 `helper.cpp` 这两个源文件，然后生成一个名为 "myapp" 的可执行文件。

通常，你会将 `add_executable()` 放在项目的CMakeLists.txt文件中，以指定项目的可执行文件以及其源代码文件。这是构建可执行文件的关键步骤之一，让CMake知道应该如何生成可执行文件。

---

下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### 初始化项目

1.   创建目录`practice-01`

     ```bash
     mkdir practice-01
     ```

2.   创建源文件`main.cpp`

     ```bash
     touch main.cpp
     ```

3.   编辑`main.cpp`，我们实现一个程序计算数字的平方根

     ```cpp
     /**
     @Author  : nickdecodes
     @Email   : 
     @Usage   : 
     @Filename: main.cpp
     @DateTime: 2023/10/18 22:15
     @Software: vscode
     **/
     
     #include <cmath>
     #include <cstdlib>
     #include <iostream>
     #include <string>
     
     int main(int argc, char* argv[]) {
         if (argc < 2) {
             std::cout << "Usage: " << argv[0] << " number" << std::endl;
             return 1;
         }
     
         const double inputValue = atof(argv[1]);
         const double outputValue = sqrt(inputValue);
         std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;
         return 0;
     }
     ```

4.   创建`CMakeLists.txt`

     ```cmake
     # Set the minimum required version of CMake to be 3.10
     cmake_minimum_required(VERSION 3.10)
     
     # Create a project named Practice
     project(Practice)
     
     # Add an executable called a.out to the project
     add_executable(a.out main.cpp)
     ```

5.   在当前目录下，创建一个`build`文件夹来存放编译结果

     ```bash
     mkdir build
     ```

6.   接下来，进入到`build`目录进行构建

     ```bash
     cmake ../
     ```

     构建完成后你将会看到如下内容

     ```bash
     .
     ├── CMakeCache.txt
     ├── CMakeFiles/ # 这里我忽略了很多cmake生成的缓存文件
     ├── Makefile
     └── cmake_install.cmake
     ```

7.   这时有两种方法去编译

     -   `cmake --build .`这是cmake的编译方式
     -   `make` 我们看到已经生成了Makefile，这时如果你的系统应该已经安装了make，你就可以使用make去编译了

     但是我们还是使用cmake的方式去编译，毕竟我们正在练习cmake，在build目录下执行`cmake --build .`，你将会看到目录下多了一个`a.out`可执行文件

     ```bash
     .
     ├── CMakeCache.txt
     ├── CMakeFiles/
     ├── Makefile
     ├── a.out # 这就是我们编译出来的可执行文件
     └── cmake_install.cmake
     ```

8.   接下来我们测试一下，使用`./a.out 4`, 预期的结果应该是2

     ```bash
     ./a.out 4
     > The square root of 4 is 2
     ```

     看起来程序正常运行了，没有问题

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

## 指定C++标准

CMake 有一些特殊变量，这些变量要么在幕后创建，要么在由项目代码设置时对 CMake 有意义。其中许多变量都以 开头`CMAKE_`。为项目创建变量时避免这种命名约定。其中两个特殊的用户可设置变量是 [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)和[`CMAKE_CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD_REQUIRED.html#variable:CMAKE_CXX_STANDARD_REQUIRED)。这些可以一起使用来指定构建项目所需的 C++ 标准。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### CMAKE_CXX_STANDARD

 [`CMAKE_CXX_STANDARD`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD.html#variable:CMAKE_CXX_STANDARD)用于指定项目中C++编译器要遵循的C++标准。这个变量用于设置编译器选项，以确保项目源代码在编译时使用所需的C++标准。

通常，你可以在你的CMakeLists.txt文件中使用 `set()` 函数来设置 `CMAKE_CXX_STANDARD` 变量，如下所示：

```cmake
set(CMAKE_CXX_STANDARD 11)
```

在这个示例中，`CMAKE_CXX_STANDARD` 被设置为11，表示C++11标准。你可以将其设置为所需的任何C++标准，如C++14、C++17、C++20等。

要在CMake项目中设置C++标准，通常有以下几个步骤：

1. 在CMakeLists.txt文件中使用 `set(CMAKE_CXX_STANDARD <version>)` 来指定所需的C++标准版本。

2. 通常，建议在 `project()` 函数之前设置C++标准，以确。例如：

```cmake
cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 11)
project(MyCMakeProject)
```

3. 随后，CMake会根据你的设置，生成相应C++标准的编译器选项，确保项目在编译时使用正确的标准。

设置正确的C++标准非常重要，因为它会影响编译器的行为和支持的C++特性。根据项目的需求和目标，你可以选择合适的C++标准版本。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### CMAKE_CXX_STANDARD_REQUIRED

[`CMAKE_CXX_STANDARD_REQUIRED`](https://cmake.org/cmake/help/latest/variable/CMAKE_CXX_STANDARD_REQUIRED.html#variable:CMAKE_CXX_STANDARD_REQUIRED)用于指示是否要求编译器强制使用指定的C++标准。当这个变量设置为 `TRUE` 时，如果编译器不支持所需的C++标准，CMake会生成一个致命错误并停止项目的配置。

默认情况下，`CMAKE_CXX_STANDARD_REQUIRED` 的值是 `FALSE`，这意味着如果编译器不支持所需的C++标准，CMake会生成一个警告，但不会停止项目的配置。

你可以在CMakeLists.txt文件中使用 `set()` 函数来设置 `CMAKE_CXX_STANDARD_REQUIRED` 变量的值，如下所示：

```cmake
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
```

在这个示例中，`CMAKE_CXX_STANDARD_REQUIRED` 被设置为 `TRUE`，这意味着如果编译器不支持所需的C++标准，CMake将生成一个致命错误，停止项目的配置。

通常情况下，将 `CMAKE_CXX_STANDARD_REQUIRED` 设置为 `TRUE` 是一个良好的做法，因为这有助于确保项目在不支持所需C++标准的编译器上不会被意外构建，从而增加项目的可移植性和稳定性。当你明确要求特定的C++标准时，最好将 `CMAKE_CXX_STANDARD_REQUIRED` 设置为 `TRUE`。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### set函数

在CMake中，[`set()`](https://cmake.org/cmake/help/latest/command/set.html#command:set)函数用于设置变量的值。这可以是普通的变量，也可以是CMake的内置变量或用户定义的变量。`set()` 函数的基本语法如下：

```cmake
set(variable value)
```

- `variable`: 要设置的变量的名称。
- `value`: 要为变量设置的值。

你可以使用 `set()` 函数来创建、修改或重新分配变量的值。这对于配置和自定义CMake项目的构建过程非常有用。

以下是一些示例用法：

1. **创建一个变量**：

```cmake
set(my_variable "Hello, World!")
```

2. **修改现有变量的值**：

```cmake
set(my_variable "New Value")
```

3. **设置多个变量**：

```cmake
set(variable1 "Value1")
set(variable2 "Value2")
```

4. **使用变量**：

```cmake
message("The value of my_variable is: ${my_variable}")
```

这将在CMake构建过程中打印变量的值。

5. **设置CMake变量**：

CMake还具有许多内置变量，如`CMAKE_CXX_STANDARD`，可以使用 `set()` 函数来设置这些变量的值。例如：

```cmake
set(CMAKE_CXX_STANDARD 11)
```

这将设置CMake的C++标准变量为C++11。

`set()` 函数是CMake配置和构建脚本中的重要工具，它使你能够控制和自定义构建过程。你可以使用它来设置各种类型的变量，包括字符串、布尔值、列表等，以满足项目的需求。

---

下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### 优化项目指定标准

1.  修改`CMakelists.txt`如下

    ```bash
    # Set the minimum required version of CMake to be 3.10
    cmake_minimum_required(VERSION 3.10)
    
    # Create a project named Practice
    project(Practice)
    
    # Set the variable CMAKE_CXX_STANDARD to 11 and the variable CMAKE_CXX_STANDARD_REQUIRED to True
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    
    # Add an executable called a.out to the project
    add_executable(a.out main.cpp)
    ```

2.  因为我指定了cpp版本main.cpp，也需要稍微改动如下

    ```cpp
    /**
    @Author  : nickdecodes
    @Email   : 
    @Usage   : 
    @Filename: main.cpp
    @DateTime: 2023/10/18 22:15
    @Software: vscode
    **/
    
    #include <cmath>
    // #include <cstdlib> // Remove this line
    #include <iostream>
    #include <string>
    
    int main(int argc, char* argv[]) {
        if (argc < 2) {
            std::cout << "Usage: " << argv[0] << " number" << std::endl;
            return 1;
        }
    
        const double inputValue = std::stod(argv[1]);
        // const double inputValue = atof(argv[1]);
    
        const double outputValue = sqrt(inputValue);
        std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;
        return 0;
    }
    
    ```

3.  接下来我继续去构建项目

    ```bash
    cd build && cmake ../ # 先构建
    cmake --build . # 在编译
    
    ./a.out 4 # 测试
    > The square root of 4 is 2
    ```

    看起来依然没有问题

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

## 添加版本号和配置的头文件

有时，让文件中定义的变量 `CMakelists.txt`在源代码中也可用可能会很有用。在这种情况下，我们想打印项目版本。

实现此目的的一种方法是使用配置的头文件。我们创建一个输入文件，其中包含一个或多个要替换的变量。这些变量具有特殊的语法，看起来像`@VAR@`. 然后，我们使用[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令将输入文件复制到给定的输出文件，并将这些变量替换为文件`VAR` 中的当前值`CMakelists.txt`。

虽然我们可以直接在源代码中编辑版本，但首选使用此功能，因为它创建单一事实来源并避免重复。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### _VERSION_MAJOR

在CMake中，[`<PROJECT-NAME>_VERSION_MAJOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MAJOR.html#variable:_VERSION_MAJOR)通常用于访问项目的主要版本号。这是你可能为项目定义的版本信息的一部分。`<PROJECT-NAME>` 应替换为你的项目的实际名称。

例如，如果你有一个名为 "MyProject" 的项目，并且你已定义了它的版本信息，你可以这样访问主要版本号：

```cmake
message("MyProject 的主要版本号是 ${MyProject_VERSION_MAJOR}")
```

在这个示例中，`${MyProject_VERSION_MAJOR}` 是一个CMake变量，通常会在项目的配置文件中定义（通常在 `ConfigVersion.cmake` 或 `Config.cmake` 文件中）。`MyProject_VERSION_MAJOR` 的值将作为项目版本信息的一部分进行设置。

主要版本号通常是版本号的一部分，比如 "1.2.3"，其中 "1" 是主要版本号，"2" 是次要版本号，"3" 是修订版本号。你可以在你的CMake项目些版本组件，用于各种用途，如生成配置文件，将版本信息包括在你的代码中，或根据项目的版本来控制构建过程。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### _VERSION_MINOR

在 CMake 中，[`<PROJECT-NAME>_VERSION_MINOR`](https://cmake.org/cmake/help/latest/variable/PROJECT-NAME_VERSION_MINOR.html#variable:_VERSION_MINOR)通常用于访问项目的次要版本号。这是你可能为项目定义的版本信息的一部分。`<PROJECT-NAME>` 应替换为你的项目的实际名称。

例如，如果你有一个名为 "MyProject" 的项目，并且你已定义了它的版本信息，你可以这样访问次要版本号：

```cmake
message("MyProject 的次要版本号是 ${MyProject_VERSION_MINOR}")
```

在这个示例中，`${MyProject_VERSION_MINOR}` 是一个 CMake 变量，通常会在项目的配置文件中定义（通常在 `ConfigVersion.cmake` 或 `Config.cmake` 文件中）。`MyProject_VERSION_MINOR` 的值将作为项目版本信息的一部分进行设置。

次要版本号通常是版本号的一部分，比如 "1.2.3"，其中 "2" 是次要版本号，"1" 是主要版本号，"3" 是修订版本号。你可以在你的 CMake 项目中访问和使用这些版本组件，用于各种用途，如生成配置文件，将版本信息包括在你的代码中，或根据项目的版本来控制构建过程。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### configure_file

[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)用于在生成构建系统时复制文件并替换其中的变量值。这通常用于生成配置文件，其中包含一些特定于构建的信息，如路径、版本号等。

`configure_file` 命令的基本语法如下：

```cmake
configure_file(input_file output_file [@ONLY])
```

- `input_file`: 要处理的输入文件的路径。
- `output_file`: 生成的输出文件的路径。
- `@ONLY`（可选参数）: 如果包括 `@ONLY`，则只有 `@VAR@` 格式的变量才会被替换。如果省略 `@ONLY`，那么所有变量都将被替换。

在 `input_file` 中，你可以包含要替换的变量，这些变量通常以 `@VAR@` 格式出现。然后，在 `configure_file` 命令中，你可以指定这些变量的值，以便在 `output_file` 中进行替换。这使得你可以根据的特定参数动态生成配置文件。

以下是一个简单的示例，假设你有一个输入文件 `config.h.in`，其中包含一个版本号变量 `@VERSION@`，然后你可以使用 `configure_file` 命令来生成一个配置文件 `config.h`，如下所示：

```cmake
configure_file(config.h.in config.h)
```

然后，在 `config.h.in` 文件中：

```c
#define VERSION "@VERSION@"
```

在 CMakeLists.txt 文件中，你可以使用 `set()` 命令来设置 `VERSION` 变量的值：

```cmake
set(VERSION "1.0.0")
```

当你运行 CMake 构建时，`configure_file` 命令将生成一个 `config.h` 文件，其中 `@VERSION@` 会被替换为 "1.0.0"。这使得你可以在生成的代码中引用版本号等配置信息。

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### target_include_directories

[`target_include_directories()`](https://cmake.org/cmake/help/latest/command/target_include_directories.html#command:target_include_directories)用于指定一个目标（通常是可执行文件或库）的头文件包含路径。这可以帮助CMake构建系统知道在构建项目时应该包含哪些头文件目录，以便正确编译和链接代码。

`target_include_directories` 命令的基本语法如下：

```cmake
target_include_directories(target
    [SYSTEM] [BEFORE]
    [INTERFACE | PUBLIC | PRIVATE] directory1 [directory2 ...]
)
```

- `target`: 要为其指定头文件目录的目标，通常是一个可执行文件或库。
- `SYSTEM`（可选）: 指定包含目录为系统目录，这会影响编译器的警告行为。
- `BEFORE`（可选）: 指定将新的包含目录插入到现有目录之前。
- `INTERFACE | PUBLIC | PRIVATE`（可选）: 指定包含目录的可见性级别，控制哪些目录对依赖于此目标的目标可见。`INTERFACE` 表示只对依赖此目标的目标可见，`PUBLIC` 表示对依赖此目标的目标和此目标本身可见，`PRIVATE` 表示仅对此目标本身可见。
- `directory1`, `directory2`, 等等: 要包含的头文件目录的路径。

通常，你可以在你的 CMakeLists.txt 文件中使用 `target_include_directories` 命令来为特定目标指定头文件包含目录。例如，如果你有一个名为 "myapp" 的可执行文件目标，并且需要包含 "include" 目录中的头文件，你可以这样使用：

```cmake
target_include_directories(myapp PRIVATE include)
```

在这个示例中，`PRIVATE` 选项表示 "myapp" 目标私有地包含 "include" 目录，这意味着只有 "myapp" 可以访问这些头文件目录，而依赖于 "myapp" 的其他目标不会自动获得这些目录。

`target_include_directories` 命令非常有用，因为它允许你在项目中管理头文件的包含路径，并确保构建系统能够正确地找到和包含所需的头文件。

---

下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)

### 优化项目版本号并配置头文件

这次相对要复杂一点了，我们创建一个输入文件，其中包含一个或多个要替换的变量。这些变量具有特殊的语法，看起来像`@VAR@`. 然后，我们使用[`configure_file()`](https://cmake.org/cmake/help/latest/command/configure_file.html#command:configure_file)命令将输入文件复制到给定的输出文件，并将这些变量替换为文件`VAR` 中的当前值`CMakelists.txt`。

1.  修改`CMakelists.txt`如下

    ```cmake
    # Set the minimum required version of CMake to be 3.10
    cmake_minimum_required(VERSION 3.10)
    
    # Create a project named Practice
    # Set the project version number as 1.0 in the above project command
    project(Practice VERSION 1.0)
    
    # Set the variable CMAKE_CXX_STANDARD to 11 and the variable CMAKE_CXX_STANDARD_REQUIRED to True
    set(CMAKE_CXX_STANDARD 11)
    set(CMAKE_CXX_STANDARD_REQUIRED True)
    
    # Use configure_file to configure and copy config.h.in to config.h
    configure_file(config.h.in config.h)
    
    # Add an executable called a.out to the project
    add_executable(a.out main.cpp)
    # Hint: Be sure to specify the source file as tutorial.cxx
    
    # Use target_include_directories to include ${PROJECT_BINARY_DIR}
    target_include_directories(a.out PUBLIC "${PROJECT_BINARY_DIR}")
    ```

2.  在`practice-01`目录下创建config.h.in文件，内容如下

    ```cmake
    // Define Tutorial_VERSION_MAJOR and Tutorial_VERSION_MINOR
    #define Practice_VERSION_MAJOR @Practice_VERSION_MAJOR@
    #define Practice_VERSION_MINOR @Practice_VERSION_MINOR@
    ```

3.  修改`main.cpp`文件如下

    ```cpp
    /**
    @Author  : nickdecodes
    @Email   : 
    @Usage   : 
    @Filename: main.cpp
    @DateTime: 2023/10/18 22:15
    @Software: vscode
    **/
    
    // A simple program that computes the square root of a number
    #include <cmath>
    // #include <cstdlib> // Remove this line
    #include <iostream>
    #include <string>
    #include "config.h" // Include config.h
    
    int main(int argc, char* argv[]) {
        if (argc < 2) {
            std::cout << argv[0] << " Version " << Practice_VERSION_MAJOR << "."  << Practice_VERSION_MINOR << std::endl;
            std::cout << "Usage: " << argv[0] << " number" << std::endl;
            return 1;
        }
    
        // convert input to double
        const double inputValue = std::stod(argv[1]);
        // const double inputValue = atof(argv[1]);
    
        // calculate square root
        const double outputValue = sqrt(inputValue);
        std::cout << "The square root of " << inputValue << " is " << outputValue << std::endl;
        return 0;
    }
    ```

4.  接下来还是去构建，编译如下

    ```bash
    cd build && cmake ../ # 先构建
    cmake --build . # 在编译
    
    ./a.out 4 # 测试
    > The square root of 4 is 2
    
    # 看起来程序没有问题，但是当我们错误使用的时候
    ./a.out       
    
    > ./a.out Version 1.0 # 打印了当前项目的版本号
    > Usage: ./a.out number
    ```

---
下一篇：[练习2 添加库](../practice-02/)，[目录](#构建一个基本项目)｜[首页](../README.md)