==============
Consensus Test
==============

The tool `consensus.py` aims to ensure that an ENI operation always returns
the same result when given the same input.
This is crucial for ENI to work on blockchain. Otherwise it will break the
consensus between nodes.

Prerequisites
-------------

Besides the prerequisites of libENI, `Python 3` is also required to run `consensus.py`.

Usage
-----

Check the usage of `consensus.py` by running it with the argument ``-h``.

.. code::

    usage: consensus.py [-h] TEST_LIST

    libENI Consensus Test

    positional arguments:
      TEST_LIST   JSON description file for list of tests

    optional arguments:
      -h, --help  show this help message and exit


Format of JSON Description File
-------------------------------

The format of the input JSON description file looks like this.

.. code::

    {
        "path": [
            ["op", "type:arg", ...],
            ...
        ]
    }

+------------+---------------------------------------------------------+
| Argument   | Description                                             |
+============+=========================================================+
| `path`     | **Absolute** path to the shared library.                |
+------------+---------------------------------------------------------+
| `op`       | Name of the ENI operation.                              |
+------------+---------------------------------------------------------+
| `type:arg` | Format of parameters passed to the ENI operation.       |
|            |                                                         |
|            | String: a random string of the given length.            |
|            |                                                         |
|            | - `type`: ``s``                                         |
|            | - `arg`: length of string                               |
|            |                                                         |
|            | Hex: a random hex string of the given length.           |
|            |                                                         |
|            | - `type`: ``h``                                         |
|            | - `arg`: length of hex string                           |
|            |                                                         |
|            | File: a string containing the file content.             |
|            |                                                         |
|            | - `type`: ``f``                                         |
|            | - `arg`: path to the file                               |
|            |                                                         |
|            | Only specific string-type shown above are supported     |
|            | for now.                                                |
+------------+---------------------------------------------------------+

Here is an example JSON file in libENI's own tests.

.. code::

    {
        "/home/libeni/build/examples/eni/eni_reverse.so": [
            ["reverse", "s:32"]
        ],
        "/home/libeni/build/tools/eni_crypto/eni_crypto.so": [
            ["rsa_encrypt", "f:data/pub.pem",  "s:17"],
            ["rsa_decrypt", "f:data/priv.pem", "f:data/rsa"]
        ],
        "/home/libeni/build/tools/eni_scrypt/eni_scrypt.so": [
            ["scrypt", "h:160"]
        ]
    }


Run Consensus Tests
-------------------

The `consensus.py` will run each ENI operation specified in the JSON file
several times (3 by default), and check if it returns the same output for
the same input.

.. code:: bash

    consensus.py tests.json


The output of the consensus tests will look like this (for the above example).

.. code::

    Case #1: /home/libeni/build/tools/eni_scrypt/eni_scrypt.so
    Arguments: ('scrypt', 'h:160')
    PARAMS: ["cEa0eBaDCA7bcFAB0fF30cFC1742eCA3ae34fC8bc8C30927B8AcBbF7A7ebdDeC330cf516EFcEc5d5C9a9d8BF8E71Bebf86de0faf78d4Af3A1FFf295f6CaEACc4DCd14CCfB9BEfA2FC1c372cCF2EaC38f"]
    STDOUT: ["31fddc755f864d1541b07d333ffc85c8c898aa48d4c193bf20cb8c3e8d4d94f7"]

    Case #2: /home/libeni/build/tools/eni_crypto/eni_crypto.so
    Arguments: ('rsa_encrypt', 'f:data/pub.pem', 's:17')
    PARAMS: ["-----BEGIN PUBLIC KEY-----
    MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEApr/atzUuBArbsWHkn8tU
    mq00tCV4CcLfVUVg+zr41sixYIb54rd5EFWoQ1xecYMZIbnoTl2vu9awHBZF18Dk
    NlG8pjw1Vw5EjaWrCDn734lcKGhsYe20H7138XgznwhJNuAeNy2OOwbEIkSl4jf8
    Ro+7nOuMK5yeHXAPZEMCnEipd/7gGk0aWP/E1XoqkZJnBUYN5N6mOgtV3jv62w+X
    lNlozUySI0mBmjgyymAhPm4qx5Zcf/Wmg42vbIFRrBl5PgWKGsY0L7xcPRDPAPRt
    ndUPr+CLLk5KjyHI8a2WiYrJvjUGTQNyqPM5MmLLfHMkjkbE6DshWbMZona+/5ji
    3wIDAQAB
    -----END PUBLIC KEY-----","0H2GDJ0ZBYM0EHNLU"]
    STDOUT: ["a4de681da245bf1ad8ad67df5b43f3b74aed0c277fa054c01a94cfa4f3ca19ecb4c639d4fe3aef3ae74638e44a2bfa7c25898b2fa52173e770a43242e5e761682227c1c1ac8ae9cc0602cc2a0c413719ef3b142b421aa0f8099412a769ca093e943896e12ee957019220fd23b12c877f09150fe7c7ab4b0393e6cc9a1ae9e3e91344627be43be4719e59faf89eb1ef9d802586e00850244dc2fff373da53a387b81d42660f61cb023079e955d62703fa9bf0ca82cdcecd164438426317e6e8abaa253b080f783ee556eb4c81d81852b1bd3f487341f0fcbb8f48b5240fc1033a2eb228ef27443cbc820cdb04f2bfdb98950f10c631b5c11c89683111734df89d"]

    Case #3: /home/libeni/build/tools/eni_crypto/eni_crypto.so
    Arguments: ('rsa_decrypt', 'f:data/priv.pem', 'f:data/rsa')
    PARAMS: ["-----BEGIN RSA PRIVATE KEY-----
    MIIEowIBAAKCAQEApr/atzUuBArbsWHkn8tUmq00tCV4CcLfVUVg+zr41sixYIb5
    4rd5EFWoQ1xecYMZIbnoTl2vu9awHBZF18DkNlG8pjw1Vw5EjaWrCDn734lcKGhs
    Ye20H7138XgznwhJNuAeNy2OOwbEIkSl4jf8Ro+7nOuMK5yeHXAPZEMCnEipd/7g
    Gk0aWP/E1XoqkZJnBUYN5N6mOgtV3jv62w+XlNlozUySI0mBmjgyymAhPm4qx5Zc
    f/Wmg42vbIFRrBl5PgWKGsY0L7xcPRDPAPRtndUPr+CLLk5KjyHI8a2WiYrJvjUG
    TQNyqPM5MmLLfHMkjkbE6DshWbMZona+/5ji3wIDAQABAoIBAAjwNdAmSJ4s2tPq
    VHAAXTuhVzbk30deq8wNWQJ+icIxpdhvw8tUXGf0v31E4UciaOF27q3stbPS8UPA
    KeRD0bfbr8oVZiKRgDk7jSx2tzqnSUpdNpoVPNeKt3g5IkM/FXWck+IPThV56l+P
    4Hh82cgKglsKAUyBK7SWQiz0rpoj8MWlkG0TblsMVLnOTAO0N3p3NiHxv1eUJrHK
    wyI42Mkb+nUm1jKSUAg9JuOQJUWcKzlgs8Z4+gvvOukO1tTs4EBMZdn2wYC0+BSE
    qB0Sx496fuIZ0YPExwF21h2bansEuG2kN5OnW80vnUT724bGvGv3yffyK3fZhE2M
    WdwDJtkCgYEA3Vw/O8cRxSv6gU4bWH6YE24XQz/pRvOsLLcQeXrxbxvm1ZsD65ou
    tpvA0/eF3c5KRAhoqgRGPDV7eHvRdo9v6Ih4mwp6wR9bEGU3beHCIjZPb5nCCGtk
    TCNiVt+MIXKBHXt9lKBjTnmbCvRt+chRz8yFwRpdu49GawOX6NY8YasCgYEAwNfh
    TbTRawCqC1WY1weFIn9y9NN1reFVvYZhb6stdfBUVAG6vjB0dGG0bZCJUH/+h65/
    AuvahIugw5AA+H8iTTeB2KpgCc2FmiUviohug39GMz6oabkzZH9KAZjCf5/zMhm3
    IvtVDMDXBJah7SFYsxM1sBfklPAHFlAe7zP/950CgYBM60IZzonRPv/0MKT18j97
    +PRibPHtsrywaQhzfhIpLsPek9gf5Vq4H5U40rkUoxtRWq6r7YJOZ7M44aWekicr
    4Ugvb8vKEdA9+T3yk9E2vDKMMBypek/G2UDRuSpjcPuGuCOiIr1/RmhmvRr+AerT
    z1jnCfdqNlYc14nQ4ajnswKBgDtlAj6lt25mePketwFbjpTOfkCLtI4Gfhrufaog
    JdNSXxa0paiYUfXadfDc+H3zvhhaFUJ4FAiI3M3+112yAoWX2AU8jHHYfBK660aW
    uLsFg0CbRtGxOfP1BH0zaIxYXlYK943trQdNiawfHOZlQ+V7wChpY3y/5N7pdG2m
    LWs9AoGBAMEgKXwA2ubWrxe622PHXwgUx9oja3LwmuT3oQZDtwxfs4lw3xzIgGps
    WVvgNL2aceE/qkI032ysKTIbM3JvKa7AzrGKDi8XbyE98QSKM9qyFmdrTG7UIbSo
    DNen8V4qgCV/z34+6uxWMR7AozgQmzrKogmxhZpIYdyqO4F35cMb
    -----END RSA PRIVATE KEY-----","65b4474b010b1992cfa93a57238be244248dd22060b2fe7f65791b9aecbd1086ff05a1e47977766646a7c2aac3550e2ceac3ba51c8a4f88fac32dfc8e9c39a28b20b70e4e5f5f425e2c68ff37959fa64a6838447eef4ca7200a4a720cb34e4917439a4a075105002b3bdb46625a6f0155017ef094cd08238e5ba742c4fd67bf9b275bea4b811dabc8e8b212997145b80ac78db53c0df757d57b18af6f8045ca85d2d26d1c2f45d9593595166018c6c03b320a147e0435a7bd9f109762bed60ab35ad38daa19b96e7545d4e45e4597f67c08584a8f2fa0298b55e8286780bc38c464d6dce80f062f24b80aa83df2ef816011b02758ef25ff8640e0599d021b2b9"]
    STDOUT: ["Hello World!"]

    Case #4: /home/libeni/build/examples/eni/eni_reverse.so
    Arguments: ('reverse', 's:32')
    PARAMS: ["OWU94YH9F62MGUGE86VWILXNZ7CLC1DH"]
    STDOUT: ["HD1CLC7ZNXLIWV68EGUGM26F9HY49UWO"]
