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
            print('Parameters:', params)
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

class TestCase:
    def __init__(self):
        self.first, self.count, self.same = None, 0, True

    def start_one(self):
        self.count += 1

    def finish_one(self, proc):
        proc.stdout = proc.stdout.decode("utf-8")
        proc.stderr = proc.stderr.decode("utf-8")
        if self.count is 1:
            self.first = proc
            return True
        self.same = TestCase.casecmp(self.first, proc)
        if not self.same:
            TestCase.caseprint(self.first, 'expected')
            TestCase.caseprint(proc, 'got this')
        return self.same

    def summarize(self):
        if self.count <= 1 or not self.same:
            return False
        TestCase.caseprint(self.first)
        return True

    @staticmethod
    def casecmp(proc, proc0):
        return (proc.returncode == proc0.returncode
                and proc.stdout == proc0.stdout
                and proc.stderr == proc0.stderr)

    @staticmethod
    def caseprint(proc, prefix=None):
        prefix = '' if prefix is None else '(%s) ' % prefix
        print('%sRETURN:' % prefix, proc.returncode)
        if proc.stdout:
            print('%sSTDOUT:' % prefix, proc.stdout.rstrip())
        if proc.stderr:
            print('%sSTDERR:' % prefix, proc.stderr.rstrip())
        print()

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
    t = TestCase()
    for i in range(n):
        t.start_one()
        p = subprocess.run(
            args, stdout=subprocess.PIPE, stderr=subprocess.PIPE
        )
        if not t.finish_one(p):
            break
    return t.summarize()

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
    return r.summarize()

if __name__ == '__main__':
    ps = argparse.ArgumentParser(description='libENI Consensus Test')
    ps.add_argument('file', metavar='TEST_LIST', type=argparse.FileType('r'),
        help='JSON description file for list of tests')
    ps.add_argument('-n', '--n-repeat', type=int, default=3,
        help='Number of times to repeat each test.')
    args = ps.parse_args()

    tests = json.loads(args.file.read())
    success = run_tests(tests, args.n_repeat)
    if not success:
        exit(1)
