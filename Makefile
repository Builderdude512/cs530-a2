CXX=g++

CXXFLAGS=-Wall -Wextra -std=c++11 -I.

TARGET=asxe

SOURCES=main.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(TARGET)

clean:
	rm -f $(TARGET)
