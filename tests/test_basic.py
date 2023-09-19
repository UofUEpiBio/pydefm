from __future__ import annotations

import pydefm as m
import numpy as np

y = np.array([0, 10, 3])
x = np.array([1, 2.0, 3.4])
id = np.array([11, 2, 3])

obj = m.new_defm(id, y, x, column_major = False)

obj.print()

# Just testing whether the function works
m.print_y(obj)


def test_version():
    assert m.__version__ == "0.0.1"

print("Everything passed")