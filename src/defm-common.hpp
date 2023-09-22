#ifndef DEFM_COMMON_H
#define DEFM_COMMON_H

using namespace pybind11::literals;

inline void pyprinter(const char * fmt, ...) 
{

  // Creating a buffer
  char buffer[1024];

  va_list args;
  va_start(args, fmt);
  vsprintf(&buffer[0], fmt, args);
  va_end(args);

  // Passing to pyprint
  pybind11::print(std::string(buffer), pybind11::arg("end") = "");

}

#define printf_barry pyprinter

#include "barry.hpp"
#include "models/defm.hpp"

inline void check_covar(
  int & idx_,
  std::string & idx,
  std::shared_ptr< defm::DEFM > & ptr
) {

  // Retrieving the matching covariate
  if (idx != "")
  {

    // Getting the covariate names
    auto cnames = ptr->get_X_names();

    // Can we find it?
    for (size_t i = 0u; i < cnames.size(); ++i) {
      if (cnames[i] == idx)
      {
        idx_ = i;
        break;
      }
    }

    if (idx_ < 0)
      throw std::range_error(
        "The variable " + idx + "does not exists."
        );

  }

}
#endif