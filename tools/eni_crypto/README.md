An ENI package for OpenSSL Crypto Library
=========================================

This package currently implements ENI operations for RSA encryption and
decryption using the OpenSSL library.

## Directory Structure

| Path           | Description                                             |
| -------------- | ------------------------------------------------------- |
| tests/         | Unit-tests for this ENI package.                        |
| Makefile       | Makefile for this ENI package.                          |
| eni_crypto.h   | Class and function definitions of this ENI package.     |
| eni_crypto.cpp | Implementation and C interface of this ENI package.     |
| demo.c         | Demonstration to load and call the ENI operations.      |


## Build `eni_crypto.so`

```
make all
```

## Run Demo

Build and run the demo.

```
make check
```

The output should look like this.

```
["-----BEGIN PUBLIC KEY-----
MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApr/atzUuBArbsWHkn8tU
...
3wIDAQAB
-----END PUBLIC KEY-----","Hello World!"]
["-----BEGIN RSA PRIVATE KEY-----
MIIEowIBAAKCAQEApr/atzUuBArbsWHkn8tUmq00tCV4CcLfVUVg+zr41sixYIb5
...
DNen8V4qgCV/z34+6uxWMR7AozgQmzrKogmxhZpIYdyqO4F35cMb
-----END RSA PRIVATE KEY-----","10dc857395c5be6feda8b59160367c1ab7a492ab5ed32e912ce329c98056075281c95f57104689e1593f528220fc96c31eb148622229ad76160783f1c2cc7514faae5094da4e0177f4389380f08f604e179ebccb271014e59893758e216a6ab6b502339aeae67ca2bd48fdef948e9ece0ce23987bc883191e0ed457a59e21edaa2092a45f7ce5d3d4571f4f513ef635d47321592ce9a00803aece5a0f2ec0b885d5dfc77edef45f1fb100a5e1a8d6c4c04e43b542f2faf40e9e5a7e51b6f532711341d9da166835698b22d6a81b0ecfcb5c6429f929dbe2b6856f260f02ebd59db2f6fd97e9c8e1c1998dc3aa5ec1dabbfc2965160a0499e2d9d7ccc8288ce35"]
Files - and output.txt are identical
```

## Run Tests

Build and run the unit-tests.

```
cd tests
make
```

The output should look like this.

```
./hex_test 'A+!'
412b21
A+!
./rsa_test 'Hello World!'
Hello World!
Hello World!
```
