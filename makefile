CC = g++
CXXFLAGS=-lpthread -g -std=c++11
target:Test.cpp ThreadPool.o
	$(CC) Test.cpp ThreadPool.o -o Test $(CXXFLAGS)
ThreadPool.o:ThreadPool.cpp
	$(CC) -c ThreadPool.cpp $(CXXFLAGS)
clean:
	rm *.o
