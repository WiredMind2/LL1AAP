CXX = g++
CXXFLAGS = -Wall -g

TARGET = main
SRCS = main.cpp lexer.cpp symbole.cpp
OBJS = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	del $(OBJS) $(TARGET) $(TARGET).exe
