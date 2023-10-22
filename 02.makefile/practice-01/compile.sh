# !/bin/bash

# 源文件和目标可执行文件的名称
SOURCE_FILE="main.cpp"
TARGET_EXECUTABLE="a.out"

# 编译器和编译选项
CXX="g++" 
CXXFLAGS="-Wall -g" 

# 预处理（Preprocessing）
echo "1. Preprocessing: $SOURCE_FILE -> ${SOURCE_FILE%.cpp}.i"
$CXX -E $SOURCE_FILE -o ${SOURCE_FILE%.cpp}.i

# 编译（Compiling）
echo "2. Compiling: ${SOURCE_FILE%.cpp}.i -> ${SOURCE_FILE%.cpp}.s"
$CXX $CXXFLAGS -S ${SOURCE_FILE%.cpp}.i -o ${SOURCE_FILE%.cpp}.s

# 汇编（Assembling）
echo "3. Assembling: ${SOURCE_FILE%.cpp}.s -> ${SOURCE_FILE%.cpp}.o"
$CXX $CXXFLAGS -c ${SOURCE_FILE%.cpp}.s -o ${SOURCE_FILE%.cpp}.o

# 链接（Linking）
echo "4. Linking: ${SOURCE_FILE%.cpp}.o -> $TARGET_EXECUTABLE"
$CXX $CXXFLAGS ${SOURCE_FILE%.cpp}.o -o $TARGET_EXECUTABLE

# 清理临时文件
# echo "5. Cleaning up temporary files"
# rm -f ${SOURCE_FILE%.cpp}.i ${SOURCE_FILE%.cpp}.s ${SOURCE_FILE%.cpp}.o ${TARGET_EXECUTABLE}

echo "Compilation completed!"