TOOL_PATH = C:/msys64/ucrt64/bin

export PATH := $(TOOL_PATH);$(PATH)

CC      = $(TOOL_PATH)/gcc
CXX     = $(TOOL_PATH)/g++

CFLAGS   = -Wall -g -O3 -finput-charset=UTF-8 -fexec-charset=UTF-8
CXXFLAGS = -Wall -g -O3 -finput-charset=UTF-8 -fexec-charset=UTF-8
TARGET   = main.exe

SRCS_C   = $(wildcard *.c)
SRCS_CPP = $(wildcard *.cpp)
OBJS     = $(SRCS_C:.c=.o) $(SRCS_CPP:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	@chcp 65001 > nul 
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.c
	@chcp 65001 > nul 
	$(CC) $(CFLAGS) -c $< -o $@

%.o: %.cpp
	@chcp 65001 > nul
	$(CXX) $(CXXFLAGS) -c $< -o $@
    
run: $(TARGET)
	@chcp 65001 > nul 
	$(TARGET)

clean:
	del /q *.o $(TARGET)
	