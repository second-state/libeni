#!/usr/bin/env python3
#==- consensus.py --------------------------------------------------------==#
#
# This file is part of the Lity project distributed under GPL-3.0.
# See LICENSE for details.
#
#==-----------------------------------------------------------------------==#
import argparse
import json
import random
import string
import subprocess

def expand(args):
    def rands(n):
        return ''.join(
            random.choice(string.ascii_uppercase + string.digits)
            for _ in range(int(n))
        )
    def readf(f):
        with open(f, 'r') as fin:
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

def repeat(args, n):
    assert n > 1
    same = True
    for i in range(n):
        p = subprocess.run(
            args, stdout=subprocess.PIPE, stderr=subprocess.PIPE
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

def run_tests(tests):
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
            success = repeat(['eni_run', soname, op, params], 3)
            n_run += 1
            n_failed += 0 if success else 1
    return n_run, n_failed

if __name__ == '__main__':
    ps = argparse.ArgumentParser(description='libENI Consensus Test')
    ps.add_argument('file', metavar='TEST_LIST', type=argparse.FileType('r'),
        help='JSON description file for list of tests')
    args = ps.parse_args()

    tests = json.loads(args.file.read())
    n_run, n_failed = run_tests(tests, args.n_repeat)
    if n_failed > 0:
        exit(1)
