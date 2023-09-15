# pydefm: Python bindings for defm


|      CI              | status |
|----------------------|--------|
| conda.recipe         | [![Conda Actions Status][actions-conda-badge]][actions-conda-link] |
| pip builds           | [![Pip Actions Status][actions-pip-badge]][actions-pip-link] |

This is a python wrapper of the [`barry c++` library][barry-git], and in
particular, of the `defm` module that provides utilities for fitting
discrete exponential family models.


[barry-git]: https://github.com/USCbiostats/barry
[gitter-badge]:            https://badges.gitter.im/pybind/Lobby.svg
[gitter-link]:             https://gitter.im/pybind/Lobby
[actions-badge]:           https://github.com/UofUEpiBio/pydefm/workflows/Tests/badge.svg
[actions-conda-link]:      https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3AConda
[actions-conda-badge]:     https://github.com/UofUEpiBio/pydefm/workflows/Conda/badge.svg
[actions-pip-link]:        https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3APip
[actions-pip-badge]:       https://github.com/UofUEpiBio/pydefm/workflows/Pip/badge.svg
[actions-wheels-link]:     https://github.com/UofUEpiBio/pydefm/actions?query=workflow%3AWheels
[actions-wheels-badge]:    https://github.com/UofUEpiBio/pydefm/workflows/Wheels/badge.svg

## Installation


- clone this repository
- `pip install ./pydefm`


## CI Examples


There are examples for CI in `.github/workflows`. A simple way to produces
binary "wheels" for all platforms is illustrated in the "wheels.yml" file,
using [`cibuildwheel`][].


Test call
---------

```python
import pydefm as m
import numpy as np

y = np.array([0, 10, 3])
x = np.array([1, 2.0, 3.4])
id = np.array([11, 2, 3])

obj = m.new_defm(id, y, x)

obj.print()

# Just testing whether the function works
m.print_y(obj)
```

[`cibuildwheel`]:          https://cibuildwheel.readthedocs.io
