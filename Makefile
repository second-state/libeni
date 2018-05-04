CPP_INCLUDES=-I./include
LIBENI_SOURCES=lib/eni.cpp \
    lib/json/Object.cpp \
    lib/json/Notation.cpp \
    lib/json/Value.cpp \
    lib/json/Array.cpp

CXX=g++

LDFLAGS=-lssl -lcrypto
CPP_FLAGS=-fPIC -fno-rtti -std=c++11 $(CPP_INCLUDES)

DESTDIR ?= $(HOME)/.ethereum/eni/lib

all: libeni.so pkgs

pkgs:
	cd tools/eni_crypto && make eni_crypto.so

install: libeni.so pkgs
	mkdir -p $(DESTDIR)
	cp libeni.so $(DESTDIR)
	cp tools/eni_crypto/eni_crypto.so $(DESTDIR)

libeni.so: $(LIBENI_SOURCES)
	$(CXX) $(CPP_FLAGS) -shared -o$@ $?
