Examples of ENI
===============

## Directory Structure

| Path            | Description                                     |
| --------------- | ----------------------------------------------- |
| eni_reverse.cpp | A small demo for implementing an ENI operation by including <eni.h> and subclassing `EniBase`. |
| main.c          | Show how to load and call the ENI operation.    |


## Instructions

Build and run this example, and check its output.

```
make
```

You should see something looks like this.

```
gcc -otest main.c -fPIC -ldl -L. -leni
LD_LIBRARY_PATH=. ./test 'Hello World' | diff -qs - output.txt
Files - and output.txt are identical
```
