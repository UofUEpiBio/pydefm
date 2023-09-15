#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> // for py::array_t
#include "barry.hpp"
#include "models/defm.hpp"
#include <vector>

namespace py = pybind11;

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

int add(int i, int j) {
    return i + j;
}


std::shared_ptr< defm::DEFM > new_defm(
    py::array_t< int > id,
    py::array_t< int > y,
    py::array_t< double > x
    ) {

    // std::vector<int> id = {1, 2, 3, 4, 5};
    // std::vector<int> y = {1, 2, 3, 4, 5};
    // std::vector<double> x = {1.0, 2.0, 3.0, 4.0, 5.0};

    // Accessing the data buffer
    auto id_buff = id.request();
    auto y_buff = y.request();
    auto x_buff = x.request();

    int n_id = id.size();
    int n_y = y.size();
    int n_x = x.size();

    std::shared_ptr< defm::DEFM > object(new defm::DEFM(
        static_cast< int * >(id_buff.ptr),
        static_cast< int * >(y_buff.ptr),
        static_cast< double * >(x_buff.ptr),
        static_cast< size_t >(n_id),
        static_cast< size_t >(n_y),
        static_cast< size_t >(n_x),
        false,
        false
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

PYBIND11_MODULE(_core, m) {
    m.doc() = R"pbdoc(
        Pybind11 example plugin
        -----------------------

        .. currentmodule:: scikit_build_example

        .. autosummary::
           :toctree: _generate

           add
           subtract
    )pbdoc";

    m.def("add", &add, R"pbdoc(
        Add two numbers

        Some other explanation about the add function.
    )pbdoc");

    // Example with lambda function
    m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
        Subtract two numbers

        Some other explanation about the subtract function.
    )pbdoc");

    // Only this is necesary to expose the class
    py::class_<defm::DEFM, std::shared_ptr<defm::DEFM>>(m, "DEFM")
        // .def(py::init<>())
        .def("print", &defm::DEFM::print, R"pbdoc(
            Print the object

            Some other explanation about the print function.)
        )pbdoc");

    // Example with shared_ptr
    m.def("new_defm", &new_defm, R"pbdoc(
        Create a new DEFM object

        Some other explanation about the new_defm function.
    )pbdoc");

    m.def("print_y", &print_y, R"pbdoc(
        Print the y vector

        Some other explanation about the print_y function.")
        )pbdoc");

#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}
