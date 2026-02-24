CXX = g++
CXXFLAGS = -Wall -g

# Debug parameter
DEBUG ?= 0
CXXFLAGS += -DDEBUG=$(DEBUG)

TARGET = main
SRCS = main.cpp lexer.cpp symbole.cpp automaton.cpp
OBJS = $(SRCS:.cpp=.o)

ifeq ($(OS),Windows_NT)
	RM = del /Q /F
	TARGET_EXT = .exe
else
	RM = rm -f
	TARGET_EXT =
endif

all: $(TARGET)$(TARGET_EXT)

$(TARGET)$(TARGET_EXT): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-$(RM) $(OBJS) $(TARGET)$(TARGET_EXT)
