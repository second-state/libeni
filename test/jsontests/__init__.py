import unittest
import os
import json
import subprocess


def eni_xx(xx, libpath, name, input):
    o = subprocess.check_output([xx, libpath, name, json.dumps(input)])
    return json.loads(o)


def u32hex2int(b):
    assert len(b) == 8, len(b)
    return int(b, 16)


class JSONTestCase(unittest.TestCase):
    LIBPATH = os.path.join(os.environ['T_BINDIR'], 'examples/eni/eni_json.so')

    def assertReturns(self, input, output):
        self.assertEqual(
            eni_xx('eni_run', self.LIBPATH, 'json', input),
            output
        )

    def assertRange(self, input, expected_begin, expected_end):
        o = eni_xx('eni_run', self.LIBPATH, 'json', input)
        actual_begin, actual_end = u32hex2int(o[0][:8]), u32hex2int(o[0][8:])
        self.assertEqual((actual_begin, actual_end), (expected_begin, expected_end))

    def assertRanges(self, input, *expected):
        o = eni_xx('eni_run', self.LIBPATH, 'json', input)
        actual = tuple(u32hex2int(o[0][i:i+8]) for i in range(0, len(expected) * 8, 8))
        self.assertEqual(actual, expected)
