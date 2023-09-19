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
   
    // Getting sizes
    size_t nrows = m->get_n_rows();
    size_t ncols = m->nterms();
    size_t m_ord = m->get_m_order();

    const int * ID = m->get_ID();

    py::array_t< double > res({nrows, ncols});

    auto res_buff = res.request();
    double * res_ptr = static_cast< double * >(res_buff.ptr);

    auto target = m->get_stats_target();

    std::function<size_t(size_t,size_t,size_t,size_t)> element_access;

    if (m->get_column_major())
    {

        element_access = [](size_t i, size_t j, size_t nrow, size_t) -> size_t {
            return i + j * nrow;
        };

    } else {

        element_access = [](size_t i, size_t j, size_t, size_t ncol) -> size_t {
            return j + i * ncol;
        };

    }

    
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
            {
                *(res_ptr + element_access(i, j, nrows, ncols)) = -99.0;
                // res(i, j) = -99.0;
            }
            continue;
        }

        for (size_t j = 0u; j < ncols; ++j)
        {
            *(res_ptr + element_access(i, j, nrows, ncols)) = (*target)[i_effective][j];
        }

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


