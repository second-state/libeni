CPP_INCLUDES=-I../../include
LIBENI_SOURCES=../../lib/eni.cpp \
    ../../lib/json/Object.cpp \
    ../../lib/json/Notation.cpp \
    ../../lib/json/Value.cpp \
    ../../lib/json/Array.cpp
GOLDEN_OUTPUT=./expected.txt

CC=gcc
CXX=g++

CFLAGS=-fPIC
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: eni_caesar_cipher.so
	$(CXX) $(CPP_FLAGS) -shared -olibeni.so $(LIBENI_SOURCES) 
%.so: %.cpp
	$(CXX) $(CPP_FLAGS) -shared -o$@ $? $(LIBENI_SOURCES)

clean:
	rm -f *.so test

test: eni_caesar_cipher.so
	$(CC) -o$@ main.c $(CFLAGS) -ldl -L. -leni -g3
	LD_LIBRARY_PATH=. ./$@ "Hello World!" "HELLOGCC" | diff -qs - $(GOLDEN_OUTPUT)
	rm -f $@
