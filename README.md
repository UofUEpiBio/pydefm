# pydefm: Python bindings for defm

| CI           | status                                                                                                                                                         |
|--------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------|
| conda.recipe | [![Conda Actions Status](https://github.com/UofUEpiBio/pydefm/workflows/Conda/badge.svg)](https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3AConda) |
| pip builds   | [![Pip Actions Status](https://github.com/UofUEpiBio/pydefm/workflows/Pip/badge.svg)](https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3APip)       |

This is a python wrapper of the [`barry c++`
library](https://github.com/USCbiostats/barry), and in particular, of
the `defm` module that provides utilities for fitting discrete
exponential family models. This is possible using the
[`pybind11`](https://pybind11.readthedocs.io/en/stable/) library (which
rocks!).

The `defm` module is already
<a href="https://github.com/UofUEpiBio/defm" target="_blank">implemented
in R</a>

## Installation

- clone this repository
- `pip install ./pydefm`

## CI Examples

There are examples for CI in `.github/workflows`. A simple way to
produces binary “wheels” for all platforms is illustrated in the
“wheels.yml” file, using
[`cibuildwheel`](https://cibuildwheel.readthedocs.io).

## Test call

``` python
import pydefm as m
import numpy as np

y = np.array([0, 10, 3])
x = np.array([1, 2.0, 3.4])
id = np.array([11, 2, 3])

obj = m.new_defm(id, y, x)

# Printing the object on screen shows it is a pointer
obj
```

    <pydefm._core.DEFM at 0x7feeb40b2c70>

``` python
# We can export member functions from the C++ class. Here is
# an example of a function defined in the C++ class:
obj.print()
```

Currently, the C++ code uses `printf` to print to the screen, which is a
different buffer from Python (the problem will be solved using <a
href="https://pybind11.readthedocs.io/en/stable/advanced/pycpp/utilities.html?highlight=print#using-python-s-print-function-in-c"
target="_blank">this</a>).

``` python
# Checking if the data is recovered
m.print_y(obj)
```

    Num. of Arrays       : 0
    Support size         : 0
    Support size range   : [2147483647, 0]
    Transform. Fun.      : no
    Model terms (0)    :
    Model Y variables (3):
      0) y0
      1) y1
      2) y2
    0 10 3 
