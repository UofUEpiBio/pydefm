#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // for py::array_t
#include "defm-common.hpp"

namespace py = pybind11;

inline std::shared_ptr< defm::DEFM > term_formula(
    std::shared_ptr< defm::DEFM > m,
    std::string formula,
    std::string idx = "",
    std::string vname = ""
) {


    int idx_ = -1;

    // This will set the covar index, if needed
    check_covar(idx_, idx, m);

    defm::counter_transition_formula(
        m->get_counters(), formula,
        m->get_m_order(), m->get_n_y(),
        idx_, vname,
        &m->get_X_names(),
        &m->get_Y_names()
    );

    return m;


}

void init_formulas(py::module_ &m)
{

    m.def(
        "term_formula", &term_formula, R"pbdoc(
        Add a term to the model
        )pbdoc",
        py::arg("m"),
        py::arg("formula"),
        py::arg("idx") = "",
        py::arg("vname") = ""
        );

}
