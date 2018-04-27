CPP_INCLUDES=-I../include
LIBENI_SOURCES=../lib/eni.cpp

CC=gcc
CXX=g++

CFLAGS=-fPIC
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: test clean

%.so: %.cpp
	$(CXX) $(CPP_FLAGS) -shared -o$@ $? $(LIBENI_SOURCES)

clean:
	rm -f *.so

test: eni_reverse.so
	$(CXX) $(CPP_FLAGS) -shared -olibeni.so $(LIBENI_SOURCES)
	$(CC) -o$@ main.c $(CFLAGS) -ldl -L. -leni
	LD_LIBRARY_PATH=. ./$@ 'Hello World' | diff -qs - expected.txt
	rm -f $@
