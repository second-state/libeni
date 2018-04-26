CPP_INCLUDES=-I../include
LIBENI_SOURCES=../lib/eni.cpp

CC=gcc
CXX=g++

CFLAGS=-fPIC $(CPP_INCLUDES)
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: test clean

%.so: %.cpp
	$(CXX) $(CPP_FLAGS) -shared -o$@ $? $(LIBENI_SOURCES)

clean:
	rm -f *.so

test: eni_reverse.so
	$(CC) -o$@ main.c $(CFLAGS) -ldl
	./$@ 'Hello World' | diff -qs - expected.txt
	rm -f $@
