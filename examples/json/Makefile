CPP_INCLUDES=-I../../include
LIBENI_JSON_SOURCES=\
    ../../lib/json/Object.cpp \
    ../../lib/json/Notation.cpp \
    ../../lib/json/Value.cpp \
    ../../lib/json/Array.cpp

CC=gcc
CXX=g++

CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: test

test:
	$(CXX) $(CPP_FLAGS) -o$@ main.cpp $(LIBENI_JSON_SOURCES)
	./$@ ex3.json | diff -qs - expected.txt
	rm -f $@
