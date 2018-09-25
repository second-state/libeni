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

class TestResult:
    def __init__(self):
        self.n_tests, self.n_run, self.n_failed = 0, 0, 0

    def start_one(self, soname, *args):
        self.n_tests += 1
        print('Case #%d:' % self.n_tests, soname)
        print('Arguments:', args)
        op, params = None, None
        try:
            op, args = args[0], args[1:]
            params = expand(args)
            print('PARAMS:', params)
        except:
            print('ERROR: failed to expand arguments', args)
        return op, params

    def finish_one(self, success):
        self.n_run += 1
        self.n_failed += 0 if success else 1

    def summarize(self):
        if self.n_tests != self.n_run:
            return False
        if self.n_failed is not 0:
            return False
        return True

def expand(args):
    def rands(n):
        return ''.join(
            random.choice(string.ascii_uppercase + string.digits)
            for _ in range(int(n))
        )
    def readf(f):
        with open(f, 'r') as fin:
            return fin.read().rstrip('\n')
    def randh(n):
        return ''.join(
            random.choice(string.hexdigits)
            for _ in range(int(n))
        )
    fns = {
        's': rands,
        'f': readf,
        'h': randh,
    }
    arglist = []
    for arg in args:
        arglist.append(fns[arg[0]](arg[2:]))
    return '[%s]' % ','.join(map(
        lambda x: '"%s"' % x if type(x) is str else str(x),
        arglist
    ))

def repeat(args, n):
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

def run_tests(tests, n_repeat):
    assert n_repeat > 1
    r = TestResult()
    for soname, oplist in tests.items():
        for args in oplist:
            op, params = r.start_one(soname, *args)
            if not op or not params:
                continue
            success = repeat(['eni_run', soname, op, params], n_repeat)
            r.finish_one(success)
    return r

if __name__ == '__main__':
    ps = argparse.ArgumentParser(description='libENI Consensus Test')
    ps.add_argument('file', metavar='TEST_LIST', type=argparse.FileType('r'),
        help='JSON description file for list of tests')
    ps.add_argument('-n', '--n-repeat', type=int, default=3,
        help='Number of times to repeat each test.')
    args = ps.parse_args()

    tests = json.loads(args.file.read())
    r = run_tests(tests, args.n_repeat)
    if not r.summarize():
        exit(1)
