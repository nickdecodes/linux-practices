CXX = g++ # 编译命令
CXXFLAGS = -Wall -g # 编译参数
OBJS = main.o # 生成对象

.PHONY: clean # 伪目标 通常用于clean操作

all:
	$(CXX) -c $(CXXFLAGS) *.cpp # 编译所有.cpp文件省去链接文件过程
	$(CXX) $(CXXFLAGS) $(OBJS) -o main # 直接生成对象文件
    
clean:
	rm -rf *.o main
