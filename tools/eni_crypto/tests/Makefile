CPP_INCLUDES=-I../../../include -I..
LIBENI_SOURCES=../../../lib/eni.cpp \
    ../../../lib/json/Object.cpp \
    ../../../lib/json/Notation.cpp \
    ../../../lib/json/Value.cpp \
    ../../../lib/json/Array.cpp
SOURCES=../eni_crypto.cpp

CXX=g++

LDFLAGS=-lssl -lcrypto
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

all: check clean

check: hex rsa
	./hex_test 'A+!'
	./rsa_test 'Hello World!'

clean:
	rm -f *_test

%: %.cpp
	$(CXX) $(CPP_FLAGS) -o$@_test $? $(LIBENI_SOURCES) $(SOURCES) $(LDFLAGS)
