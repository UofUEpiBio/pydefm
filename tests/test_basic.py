from __future__ import annotations

import scikit_build_example as m
import numpy as np

y = np.array([1, 2, 3])
x = np.array([1, 2, 3])
id = np.array([1, 2, 3])

m.new_defm(y, x, id)


def test_version():
    assert m.__version__ == "0.0.1"


def test_add():
    assert m.add(1, 2) == 3


def test_sub():
    assert m.subtract(1, 2) == -1
