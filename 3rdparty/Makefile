SRCS = $(wildcard *.c)
#这条语句定义了一个变量SRCS，它的值就是当前面目录下面所有的以.c结尾的源文件。
 
OBJS = $(SRCS:.c = .o)
#这里变量OBJS的值就是将SRCS里面所有.c文件编译出的.o目标文件
 
CC = gcc
#变量CC代表我们要使用的编译器
 
#指定头文件位置:
INCLUDES = -I ../include
INCLUDES += -I ./src
INCLUDES += -I ../3rdparty/opencv/include
			 
#指定库文件和路径
LIBS = -L -lpthreads 
LIBS += -L ./src
LIBS += -L ../3rdparty/opencv/lib/
		
#这里指定除了编译器默认的头文件和库文件的路径之外需要额外引用的头文件路径以及库的路径（×××表示路径）。
 
CCFLAGS = -g -Wall -O0
#CCFLAGS变量存放的是编译选项
 
kit_app : $(OBJS)
	$(CC) $^ -o $@ $(INCLUDES) $(LIBS)
#my_app依赖于所有的.o文件，$^代表$(OBJS)，$@代表my_app
 
%.o : %.c
	$(CC) -c $< $(CCFLAGS)
#将所有的.c源代码编译成.o目标文件S
clean:
	#rm *.o
	rm kit_app
#在执行make clean之后删除所有编译过程中生成的.o文件。
 
.PHONY:clean
#每次执行make clean时都要执行rm *.o命令
