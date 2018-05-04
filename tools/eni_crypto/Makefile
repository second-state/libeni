CPP_INCLUDES=-I../../include
LIBENI_SOURCES=../../lib/eni.cpp \
    ../../lib/json/Object.cpp \
    ../../lib/json/Notation.cpp \
    ../../lib/json/Value.cpp \
    ../../lib/json/Array.cpp

CC=gcc
CXX=g++

CFLAGS=-fPIC
LDFLAGS=-lssl -lcrypto
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: libeni.so eni_crypto.so

check: test

libeni.so: $(LIBENI_SOURCES)
	$(CXX) $(CPP_FLAGS) -shared -o$@ $?

%.so: %.cpp
	$(CXX) $(CPP_FLAGS) -shared -o$@ $? $(LIBENI_SOURCES) $(LDFLAGS)

clean:
	rm -f *.so

test: libeni.so eni_crypto.so
	$(CC) -o$@ demo.c $(CFLAGS) -ldl -L. -leni
	LD_LIBRARY_PATH=. ./$@ 'Hello World!' | diff -qs - output.txt
	@echo TODO: compare the output with 'expected.txt' instead of 'output.txt'
	rm -f $@
