import unittest
import os
import json
import subprocess
import struct


def eni_xx(xx, libpath, name, input):
    o = subprocess.check_output([xx, libpath, name, json.dumps(input)])
    return json.loads(o)


class JSONTestCase(unittest.TestCase):
    LIBPATH = os.path.join(os.environ['T_BINDIR'], 'examples/eni/eni_json.so')

    def assertReturns(self, input, output):
        self.assertEqual(
            eni_xx('eni_run', self.LIBPATH, 'json', input),
            output
        )

    def assertRange(self, input, expected_begin, expected_end):
        o = eni_xx('eni_run', self.LIBPATH, 'json', input)
        actual_begin, actual_end = struct.unpack('>ii', o[0].encode('ascii'))
        self.assertEqual((actual_begin, actual_end), (expected_begin, expected_end))

    def assertRanges(self, input, *expected):
        o = eni_xx('eni_run', self.LIBPATH, 'json', input)
        actual = struct.unpack('>%di' % len(expected), o[0].encode('ascii'))
        self.assertEqual(actual, expected)
