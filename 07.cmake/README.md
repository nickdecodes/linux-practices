# 什么是 CMake

[官方主页](http://www.cmake.org/) | [官方文档](https://cmake.org/cmake/help/latest/) | [官方教程](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)

你或许听过好几种 Make 工具，例如 [GNU Make](https://www.hahack.com/wiki/tools-makefile.html) ，QT 的 [qmake](http://qt-project.org/doc/qt-4.8/qmake-manual.html) ，微软的 [MS nmake](http://msdn.microsoft.com/en-us/library/ms930369.aspx)，BSD Make（[pmake](http://www.freebsd.org/doc/en/books/pmake/)），[Makepp](http://makepp.sourceforge.net/)，等等。这些 Make 工具遵循着不同的规范和标准，所执行的 Makefile 格式也千差万别。这样就带来了一个严峻的问题：如果软件想跨平台，必须要保证能够在不同平台编译。而如果使用上面的 Make 工具，就得为每一种标准写一次 Makefile ，这将是一件让人抓狂的工作。

CMake 就是针对上面问题所设计的工具：它首先允许开发者编写一种平台无关的 CMakeLists.txt 文件来定制整个编译流程，然后再根据目标用户的平台进一步生成所需的本地化 Makefile 和工程文件，如 Unix 的 Makefile 或 Windows 的 Visual Studio 工程。从而做到“Write once, run everywhere”。显然，CMake 是一个比上述几种 make 更高级的编译配置工具。一些使用 CMake 作为项目架构系统的知名开源项目有 [VTK](http://www.vtk.org/)、[ITK](http://www.itk.org/)、[KDE](http://kde.org/)、[OpenCV](http://www.opencv.org.cn/opencvdoc/2.3.2/html/modules/core/doc/intro.html)、[OSG](http://www.openscenegraph.org/) 等 [[1\]](https://www.hahack.com/codes/cmake/#fn1)。

# 前期准备

1.  一台电脑 + 操作系统(linux[ubuntu | centos], mac), 个人常用的就是这些系统，如果你是windows的话，一些东西是通用的，出现异常情况请自行查找资料

2.  安装基础环境(vim, gcc, g++, make, cmake等)

    -    ubuntu

    
    ```bash
    # 安装Vim：
    sudo apt update
    sudo apt install vim
    # 安装GCC和g++：
    sudo apt install gcc g++
    # 安装Make工具：
    sudo apt install make
    # 安装cmake工具
    sudo apt install cmake
    ```
    
    -    centos
    
    
    ```bash
    # 安装Vim：
    sudo yum install vim
    # 安装GCC和g++：
    sudo yum install gcc gcc-c++
    # 安装Make工具：
    sudo yum install make
    # 安装cmake工具
    sudo yum install cmake
    ```

    -    mac
    
    
    ```bash
    # macOS通常已经预装了Vim，但你也可以通过Homebrew来安装：
    # 安装Homebrew（如果尚未安装）：
    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
    # 安装Vim：
    brew install vim
    # 安装Xcode Command Line Tools（这会包括GCC、g++和Make工具）：
    xcode-select --install
    # 安装cmake工具
    brew install cmake
    ```

# 使用说明

1.  如果你在这方面已经是大佬了，我建议您可以简单看一下，查缺补漏，也可以给出您宝贵的意见
2.  如果你是一个小白，那么我们就通过下面的练习一起来研究一下cmake吧  
- [练习1 构建一个基本项目](./practice-01/)
- [练习2 添加库](./practice-02/)
- [练习3 添加库的使用要求](./practice-03/)
- [练习4 添加生成器表达式](./practice-04/)
- [练习5 安装和测试](./practice-05/)
- [练习6 添加对测试仪表板的支持](./practice-06/)
- [练习7 添加系统自省](./practice-07/)
- [练习8 添加自定义命令和生成的文件](./practice-08/)
- [练习9 打包安装程序](./practice-09/)
- [练习10 选择静态或共享库](./practice-10/)
- [练习11 添加导出配置](./practice-11/)
- [练习12 打包调试和发布](./practice-12/)

# 迁移到CMake

CMake 可以很轻松地构建出在适合各个平台执行的工程环境。而如果当前的工程环境不是 CMake ，而是基于某个特定的平台，是否可以迁移到 CMake 呢？答案是可能的。下面针对几个常用的平台，列出了它们对应的迁移方案。

## autotools

- [am2cmake](https://projects.kde.org/projects/kde/kdesdk/kde-dev-scripts/repository/revisions/master/changes/cmake-utils/scripts/am2cmake) 可以将 autotools 系的项目转换到 CMake，这个工具的一个成功案例是 KDE 。
- [Alternative Automake2CMake](http://emanuelgreisen.dk/stuff/kdevelop_am2cmake.php.tgz) 可以转换使用 automake 的 KDevelop 工程项目。
- [Converting autoconf tests](http://www.cmake.org/Wiki/GccXmlAutoConfHints)

## qmake

- [qmake converter](http://www.cmake.org/Wiki/CMake:ConvertFromQmake) 可以转换使用 QT 的 qmake 的工程。

## Visual-Studio

- [vcproj2cmake.rb](http://vcproj2cmake.sf.net/) 可以根据 Visual Studio 的工程文件（后缀名是 `.vcproj` 或 `.vcxproj`）生成 CMakeLists.txt 文件。
- [vcproj2cmake.ps1](http://nberserk.blogspot.com/2010/11/converting-vc-projectsvcproj-to.html) vcproj2cmake 的 PowerShell 版本。
- [folders4cmake](http://sourceforge.net/projects/folders4cmake/) 根据 Visual Studio 项目文件生成相应的 “source_group” 信息，这些信息可以很方便的在 CMake 脚本中使用。支持 Visual Studio 9/10 工程文件。

## CMakeLists.txt自动推导

- [gencmake](http://websvn.kde.org/trunk/KDE/kdesdk/cmake/scripts/) 根据现有文件推导 CMakeLists.txt 文件。
- [CMakeListGenerator](http://www.vanvelzensoftware.com/postnuke/index.php?name=Downloads&req=viewdownload&cid=7) 应用一套文件和目录分析创建出完整的 CMakeLists.txt 文件。仅支持 Win32 平台。
