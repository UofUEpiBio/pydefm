# pydefm: Python bindings for defm

| CI           | status                                                                                                                                                                     |
|--------------|----------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| conda.recipe | [![Conda Actions Status](https://github.com/UofUEpiBio/pydefm/actions/workflows/conda.yml/badge.svg)](https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3AConda) |
| pip builds   | [![Pip Actions Status](https://github.com/UofUEpiBio/pydefm/actions/workflows/pip.yml/badge.svg)](https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3APip)       |

This is a python wrapper of the [`barry c++`
library](https://github.com/USCbiostats/barry), and in particular, of
the `defm` module that provides utilities for fitting discrete
exponential family models. This is possible using the
[`pybind11`](https://pybind11.readthedocs.io/en/stable/) library (which
rocks!).

The `defm` module is already
<a href="https://github.com/UofUEpiBio/defm" target="_blank">implemented
in R</a> and it can be used to count motifs and build Markov Random
fields and other models like ERGMs. More information in [this
preprint](https://arxiv.org/abs/2211.00627).

# Installation

- clone this repository
- `pip install ./pydefm`

# Examples

## Base setup

Here we show how to create a `defm` object and add terms to it. We will
use the following data:

``` python
# Loading the module
import pydefm as m
import numpy as np

# Creating a binary array
y = np.column_stack(
  (np.array([0, 0, 1, 1, 1, 1]),
  np.array([0, 1, 1, 0, 0, 1]))
)

# Adding some random X plus the ids
x = np.array([1, 2.0, 3.4, 3, 1, 2])
id = np.array([1, 1, 1, 2, 2, 2])
```

Once we have the needed data – the binary array `y`, the covariates `x`
and the ids `id` – we can create a `defm` object.

``` python
# Creating the object
obj = m.new_defm(id, y, x, column_major = False)

# Printing the object on screen shows it is a pointer
obj
```

    <pydefm._core.DEFM at 0x7f602865fd30>

Adding terms via formula

``` python
m.term_formula(obj, "{y0}")
m.term_formula(obj, "{y1}")
m.term_formula(obj, "{0y0, y1}")
obj.init()
obj.print() 
```

    Num. of Arrays       : 6
    Support size         : 6
    Support size range   : [4, 4]
    Arrays in powerset   : 24
    Transform. Fun.      : no
    Model terms ( 3)    :
     - Logit intercept y0
     - Logit intercept y1
     - Motif {y0⁻, y1⁺}
    Model rules (1)    :
     - Markov model of order 0
    Model Y variables (2):
      0) y0
      1) y1

``` python
counts = m.get_stats(obj)
counts
```

    array([[0., 0., 0.],
           [0., 1., 1.],
           [1., 1., 0.],
           [1., 0., 0.],
           [1., 0., 0.],
           [1., 1., 0.]])

Notice the first two columns coincide with the `y` array:

``` python
y
```

    array([[0, 0],
           [0, 1],
           [1, 1],
           [1, 0],
           [1, 0],
           [1, 1]])

Computing likelihood

``` python
par = np.array([.5, -.5, 1.0])
obj.likelihood(par, as_log = True)

# Finding the MLE
res = m.defm_mle(obj, np.array([.5, -.5, 1.0]))
print(res)
```

    defm_mle_fit
        par =[ 0.69, --0.00,  0.00],
        or  =[ 2.00,  1.00,  1.00],
        se  =[ 1.24,  1.02,  1.73]
        ll  =-7.98

And simulating

``` python
m.simulate(obj, par)
```

    array([[0, 0],
           [0, 1],
           [1, 0],
           [1, 1],
           [1, 1],
           [1, 0]], dtype=int32)

# Acknowledgements

This port work was supported by the Office of the Assistant Secretary of
Defense for Health Affairs through the Epilepsy Research Program under
Award No. HT94252310221. Opinions, interpretations, conclusions, and
recommendations are those of the author and are not necessarily endorsed
by the Department of Defense.
