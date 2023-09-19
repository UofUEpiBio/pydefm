#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // for py::array_t
#include "defm-common.hpp"
#include <vector>

namespace py = pybind11;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)


std::shared_ptr< defm::DEFM > new_defm(
    py::array_t< int > id, 
    /*
    python uses row-major. defm uses col-major. Need to address this with:
    https://pybind11.readthedocs.io/en/stable/advanced/pycpp/numpy.html?highlight=mutable_data#arrays
    */
    py::array_t< int > y, 
    py::array_t< double > x,
    size_t order = 0u,
    bool copy = false,
    bool column_major = false
    ) {

    // Accessing the data buffer
    auto id_buff = id.request();
    auto y_buff = y.request();
    auto x_buff = x.request();

    int n_id = id.size();
    int n_y = y.ndim() == 1 ? 1 : y.shape(1);
    int n_x = x.ndim() == 1 ? 1 : x.shape(1);

    std::shared_ptr< defm::DEFM > object(new defm::DEFM(
        static_cast< int * >(id_buff.ptr),
        static_cast< int * >(y_buff.ptr),
        static_cast< double * >(x_buff.ptr),
        static_cast< size_t >(n_id),
        static_cast< size_t >(n_y),
        static_cast< size_t >(n_x),
        order,
        copy,
        column_major
    ));

    return object;
}

/**
 * @brief Print the y vector
 * @param object The DEFM object
*/
void print_y(const std::shared_ptr< defm::DEFM > & object) {
    
    auto Y = object->get_Y();
    for (size_t i = 0u; i < object->get_n_y(); ++i)
        std::cout << (*(Y + i)) << " ";

    std::cout << std::endl;

    return;
}

// Externally declared
void init_formulas(py::module_ &);
void init_get_stats(py::module_ &);

PYBIND11_MODULE(_core, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: pydefm

        .. autosummary::
           :toctree: _generate

           new_defm
           print_y
    )pbdoc";

    // Only this is necesary to expose the class
    py::class_<defm::DEFM, std::shared_ptr<defm::DEFM>>(m, "DEFM")
        // .def(py::init<>())
        .def("print", &defm::DEFM::print, R"pbdoc(
            Print the object

            Some other explanation about the print function.)
        )pbdoc")
        .def("init", &defm::DEFM::init, R"pbdoc(
            Initialize the object

            Some other explanation about the init function.)
        )pbdoc");

    // Example with shared_ptr
    m.def("new_defm", &new_defm, R"pbdoc(
        Create a new DEFM object

        Some other explanation about the new_defm function.
    )pbdoc",
        py::arg("id"),
        py::arg("y"),
        py::arg("x"),
        py::arg("order") = 0,
        py::arg("copy") = false,
        py::arg("column_major") = false
        );

    m.def("print_y", &print_y, R"pbdoc(
        Print the y vector

        Some other explanation about the print_y function.")
        )pbdoc");

    init_formulas(m);
    init_get_stats(m);

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
