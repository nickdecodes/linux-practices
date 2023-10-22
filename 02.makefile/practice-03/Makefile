# CXX 定义了编译器。
CXX = g++
# CXXFLAGS 包含了编译选项，例如 -Wall 开启所有警告，-std=c++11 使用 C++11 标准。
CXXFLAGS = -Wall -std=c++11

# OBJS 是根据源文件生成的目标文件列表。
SRCS = main.cpp hello.cpp
# 使用简化的方式生成目标文件列表
OBJS = $(SRCS:.cpp=.o)

# TARGET 是最终生成的可执行文件。
TARGET = main

# 默认目标是最终可执行文件
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(OBJS) -o $@

# 通用的规则，用于生成目标文件
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $< -o $@

# 清理操作
clean:
	rm -rf $(OBJS) $(TARGET)

.PHONY: all clean