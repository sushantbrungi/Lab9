CXX = g++
CXXFLAGS = -std=c++17 -Wall -O2
TARGET = lab9
SRC = main.cpp

all:
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

run:
	./$(TARGET) sample.txt

clean:
	rm -f $(TARGET)
