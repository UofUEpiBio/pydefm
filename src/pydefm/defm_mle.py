from scipy.optimize import minimize
import numpy as np

# Function to print an array using two digits
def print_array(arr):
  return "[" + ", ".join([f"{'' if x < 0 else ' '}{x:.2f}" for x in arr]) + "]"

class defm_mle_fit:
  """
  Represents the result of a Maximum Likelihood Estimation (MLE) fit in the DEFM model.

  Attributes:
    par (list): The estimated parameter values.
    or_ (list): The odds ratios corresponding to the estimated parameter values.
    se (list): The standard errors of the estimated parameter values.
    ll (float): The log-likelihood value of the fit.
    optimres (object): The optimization result object containing additional information.
  """

  def __init__(self, par, or_, se, ll, optimres):
    self.par = par
    self.or_ = or_
    self.se = se
    self.ll = ll
    self.optimres = optimres

  def __str__(self):
    return f"defm_mle_fit\n\tpar =" + \
      print_array(self.par) + \
      ",\n\tor  =" + \
      print_array(self.or_) + \
      ",\n\tse  ="+ \
      print_array(self.se) + \
      f"\n\tll  ={self.ll: .2f}"

def defm_mle(obj, par):
  """
  Maximum Likelihood Estimation using the defm method.

  Parameters:
  obj (object): The object containing the likelihood function.
  par (array-like): The initial parameter values.

  Returns:
  defm_mle_fit: An instance of the defm_mle_fit class containing the estimated parameters, odds ratios, standard errors, log-likelihood value, and optimization results.
  """
  def ll(par):
    return -obj.likelihood(par, as_log=True)

  res = minimize(ll, par)
  return defm_mle_fit(
    par=res.x,
    or_=np.exp(res.x),
    se=np.sqrt(np.diag(res.hess_inv)),
    ll=-res.fun,
    optimres=res
  )
