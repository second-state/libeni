#!/usr/bin/env python3
#==- consensus.py --------------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
import os
import random
import string
import subprocess

T_BINDIR = os.getenv('T_BINDIR', '')
tests = {
    os.path.join(T_BINDIR, 'examples/eni/eni_reverse.so'): [
        ('reverse', 's:32'),
    ],
    os.path.join(T_BINDIR, 'examples/eni/eni_caesar_cipher.so'): [
        ('caesar_encrypt', 's:32', 's:16'),
        ('caesar_decrypt', 's:32', 's:16'),
    ],
    os.path.join(T_BINDIR, 'tools/eni_crypto/eni_crypto.so'): [
        ('rsa_encrypt', 'f:pub.pem',  's:17'),
        ('rsa_decrypt', 'f:priv.pem', 'f:rsa'),
    ],
}

def expand(args):
    def rands(n):
        return ''.join(
            random.choice(string.ascii_uppercase + string.digits)
            for _ in range(int(n))
        )
    def readf(f):
        with open(os.path.join('data', f), 'r') as fin:
            return fin.read().rstrip('\n')
    fns = {
        's': rands,
        'f': readf,
    }
    arglist = []
    for arg in args:
        arglist.append(fns[arg[0]](arg[2:]))
    return '[%s]' % ','.join(map(
        lambda x: '"%s"' % x if type(x) is str else str(x),
        arglist
    ))

def repeat(args, env, n):
    assert n > 1
    same = True
    for i in range(n):
        p = subprocess.run(
            args, env=env, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        assert p.returncode is 0
        if i is 0:
            prevout = p.stdout
        elif prevout != p.stdout:
            same = False
            print('Expect:', prevout.decode("utf-8"))
            print('Output:', p.stdout.decode("utf-8"))
            break
    else:
        if p.stdout:
            print('STDOUT:', p.stdout.decode("utf-8"))
        if p.stderr:
            print('STDERR:', p.stderr.decode("utf-8"))
    return same

def run_tests():
    def joinenv(key, value):
        return os.pathsep.join(filter(None, [value, os.getenv(key)]))
    env = {
        'PATH': joinenv('PATH', os.path.join(T_BINDIR, 'tools/eni_cli')),
        'LD_LIBRARY_PATH': joinenv('LD_LIBRARY_PATH', T_BINDIR),
    }
    n_run, n_failed = 0, 0
    for soname, oplist in tests.items():
        for args in oplist:
            op, args = args[0], args[1:]
            print('Case #%d:' % n_run, soname, op)
            try:
                params = expand(args)
            except:
                print('ERROR: failed to expand arguments', args)
                continue
            print('PARAMS:', params)
            success = repeat(['eni_run', soname, op, params], env, 3)
            n_run += 1
            n_failed += 0 if success else 1
    return n_run, n_failed

if __name__ == '__main__':
    n_run, n_failed = run_tests()
    if n_failed > 0:
        exit(1)
