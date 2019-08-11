from . import JSONTestCase


class NestedArrayTest(JSONTestCase):
    #       01234567890123456789
    data = '["foo", ["nested"]]'

    def test_0(self):
        self.assertRange(
            ['arrayGet', self.data, 0, len(self.data), 0],
            1, 6
        )

    def test_1(self):
        self.assertRange(
            ['arrayGet', self.data, 0, len(self.data), 1],
            8, 18
        )

    def test_1_0(self):
        self.assertRange(
            ['arrayGet', self.data, 8, 18, 0],
            9, 17
        )

    def test_parse_array(self):
        self.assertRanges(
            ['parseArray', self.data, 0, len(self.data)],
            1, 6, 8, 18
        )



class NestedObjectTest(JSONTestCase):
    #       0         1         2         3         4         5
    #       0123456789012345678901234567890123456789012345678901234
    data = '{"a": {"b": {"c": "d", "x": "y"}, "x": "y"}, "x": "y"}'

    def test_a(self):
        self.assertRange(
            ['objectGet', self.data, 0, len(self.data), 'a'],
            6, 43
        )

    def test_a_b(self):
        self.assertRange(
            ['objectGet', self.data, 6, 43, 'b'],
            12, 32
        )

    def test_a_b_c(self):
        self.assertRange(
            ['objectGet', self.data, 12, 32, 'c'],
            18, 21
        )
