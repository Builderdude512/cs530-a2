# Source code for assignment 2
# Connor Shands-Sparks - REDID:
# Connor Symons - REDID:828475798
CXX=g++

CXXFLAGS=-Wall -Wextra -std=c++11 -I.

TARGET=asxe

SOURCES=main.cpp instruction.cpp symtab.cpp typedef.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
