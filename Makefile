CXX = g++
CXXFLAGS = -std=c++17 -Wall -I h -I /usr/local/include/gtest/ -c
LXXFLAGS = -std=c++17 -Ih -pthread
OBJECTS = ./obj/puzzle.o ./obj/main.o 
GTEST = /usr/local/lib/libgtest.a
TARGET = main


$(TARGET): $(OBJECTS)
	$(CXX) $(LXXFLAGS) -o $(TARGET) $(OBJECTS) $(GTEST)
./obj/puzzle.o: ./cpp/puzzle.cpp
	$(CXX) $(CXXFLAGS) ./cpp/puzzle.cpp -o ./obj/puzzle.o
./obj/main.o: ./cpp/main.cpp
	$(CXX) $(CXXFLAGS) ./cpp/main.cpp -o ./obj/main.o
clean:
	rm -fv $(TARGET) $(OBJECTS)
