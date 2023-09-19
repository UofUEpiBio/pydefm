#ifndef DEFM_COMMON_H
#define DEFM_COMMON_H

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