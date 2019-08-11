import json
from . import JSONTestCase


class BasicContainerTest(JSONTestCase):
    #         01234567890123456789012345678
    OBJECT = '{"a": "bcdef", "b": "hijkl"}'
    ARRAY_ = '["qwert", "yuiop"]'

    def test_object_a(self):
        self.assertRange(
            ['objectGet', self.OBJECT, 0, len(self.OBJECT), 'a'],
            6, 13
        )

    def test_object_b(self):
        self.assertRange(
            ['objectGet', self.OBJECT, 0, len(self.OBJECT), 'b'],
            20, 27
        )

    def test_array_0(self):
        self.assertRange(
            ['arrayGet', self.ARRAY_, 0, len(self.ARRAY_), 0],
            1, 8
        )

    def test_array_1(self):
        self.assertRange(
            ['arrayGet', self.ARRAY_, 0, len(self.ARRAY_), 1],
            10, 17
        )
