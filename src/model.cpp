#include <pybind11/pybind11.h>
#include <pybind11/numpy.h> 

#include "defm-common.hpp"

namespace py = pybind11;

//' Get sufficient statistics counts
//' 
//' This function computes the individual counts of the sufficient statistics
//' included in the model. 
//' @param m An object of class [DEFM].
//' @export
//' @return A matrix with the counts of the sufficient statistics.
//' @examples
//' data(valentesnsList)
//' 
//' mymodel <- new_defm(
//'   id = valentesnsList$id,
//'   Y = valentesnsList$Y,
//'   X = valentesnsList$X,
//'   order = 1
//' )
//' 
//' # Adding the intercept terms and a motif from tobacco to mj
//' term_defm_logit_intercept(mymodel)
//' term_defm_transition_formula(mymodel, "{y1, 0y2} > {y1, y2}")
//' 
//' # Initialize the model
//' init_defm(mymodel)
//' 
//' # Get the counts
//' head(get_stats(mymodel))
// [[Rcpp::export(rng = false)]]
py::array_t<double> get_stats(std::shared_ptr< defm::DEFM > m)
{
   
    auto model = m->get_model();

    // Getting sizes
    size_t nrows = ptr->get_n_rows();
    size_t ncols = model.nterms();
    size_t m_ord = ptr->get_m_order();

    const int * ID = ptr->get_ID();

    py::array_t< double > res({nrows, ncols});
    auto target = model.get_stats_target();


    size_t i_effective = 0u;
    size_t n_obs_i = 0u;
    for (size_t i = 0u; i < nrows; ++i)
    {

      // Do we need to reset the counter?
        if ((i > 0) && (*(ID + i - 1u) != *(ID + i)))
            n_obs_i = 0u;

        // Did we passed the Markov order?
        if (n_obs_i++ < m_ord)
        {
            // std::fill(res.row(i).begin(), res.row(i).end(), -99.0);
            for (size_t j = 0u; j < ncols; ++j)
                res(i, j) = -99.0;
            continue;
        }

        for (size_t j = 0u; j < ncols; ++j)
            res(i, j) = (*target)[i_effective][j];

        i_effective++;

    }

    // // Setting the names
    // Rcpp::CharacterVector cnames(0);
    // for (auto & n : model.colnames())
    //     cnames.push_back(n);
    // Rcpp::colnames(res) = cnames;

    return res;

}

void init_get_stats(py::module_ &m)
{

    m.def(
        "get_stats", &get_stats, R"pbdoc(
        Get the counts
        )pbdoc");

}


