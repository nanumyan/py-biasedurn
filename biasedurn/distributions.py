# 
# Author: Vahan Nanumyan 2019
#
#
#
# Some of the functionality is taken from SciPy
# Copyright (c) 2003-2017 SciPy Developers. All rights reserved.
# 
#
#
import numbers
import numpy as np

from . import core


# __all__ = [}



################################################################################
###                           HELPERS                                        ###
################################################################################

# copy-pasted SciPy, which copy-pasted from scikit-learn utils/validation.py
def check_random_state(seed):
    """Turn seed into a np.random.RandomState instance
    If seed is None (or np.random), return the RandomState singleton used
    by np.random.
    If seed is an int, return a new RandomState instance seeded with seed.
    If seed is already a RandomState instance, return it.
    Otherwise raise ValueError.
    """
    if seed is None or seed is np.random:
        return np.random.mtrand._rand
    if isinstance(seed, (numbers.Integral, np.integer)):
        return np.random.RandomState(seed)
    if isinstance(seed, np.random.RandomState):
        return seed
    raise ValueError('%r cannot be used to seed a numpy.random.RandomState'
                     ' instance' % seed)


def _squeeze_output(out):
    """
    Remove single-dimensional entries from array and convert to scalar,
    if necessary.
    """
    out = out.squeeze()
    if out.ndim == 0:
        out = out[()]
    return out







################################################################################
###                        UNIVARIATE                                        ###
################################################################################














################################################################################
###                        MULTIVARIATE                                      ###
################################################################################


class multi_rv_generic(object):
    """
    Class which encapsulates common functionality between all multivariate
    distributions.
    """
    def __init__(self, seed=None):
        super(multi_rv_generic, self).__init__()
        self._random_state = check_random_state(seed)

    @property
    def random_state(self):
        """ Get or set the RandomState object for generating random variates.
        This can be either None or an existing RandomState object.
        If None (or np.random), use the RandomState singleton used by np.random.
        If already a RandomState instance, use it.
        If an int, use a new RandomState instance seeded with seed.
        """
        return self._random_state

    @random_state.setter
    def random_state(self, seed):
        self._random_state = check_random_state(seed)

    def _get_random_state(self, random_state):
        if random_state is not None:
            return check_random_state(random_state)
        else:
            return self._random_state




class multi_rv_frozen(object):
    """
    Class which encapsulates common functionality between all frozen
    multivariate distributions.
    """
    @property
    def random_state(self):
        return self._dist._random_state

    @random_state.setter
    def random_state(self, seed):
        self._dist._random_state = check_random_state(seed)















class multi_wallenius_hyper(multi_rv_generic):
    r"""
    A Multivariate Wallenius Non-central Hypergeometric Random variable

     Methods
    -------

     Parameters
    ----------

     Notes
    -----

     Examples
    --------
    """

    def __init__(self, seed=None):
        super(multi_wallenius_hyper, self).__init__(seed=seed)

    # def __call__(self, ..., seed=None):
    #     """
    #     Create a Multivariate Wallenius Non-central Hypergeometric distribution.
    #     See `multi_wallenius_hyper_frozen` for more information.
    #     """
    #     return multi_wallenius_hyper_frozen(mean, cov,
    #                                       allow_singular=allow_singular,
    #                                       seed=seed)






class multi_wallenius_hyper_frozen(multi_rv_frozen):

    def logpdf(self, x):
        x = self._dist._process_quantiles(x, self.dim)
        out = self._dist._logpdf(x, self.mean, self.cov_info.U,
                                 self.cov_info.log_pdet, self.cov_info.rank)
        return _squeeze_output(out)

    def pdf(self, x):
        return np.exp(self.logpdf(x))

    def logcdf(self, x):
        return np.log(self.cdf(x))

    def cdf(self, x):
        x = self._dist._process_quantiles(x, self.dim)
        out = self._dist._cdf(x, self.mean, self.cov, self.maxpts, self.abseps,
                              self.releps)
        return _squeeze_output(out)

    def rvs(self, size=1, random_state=None):
        return self._dist.rvs(self.mean, self.cov, size, random_state)

    def entropy(self):
        """
        Computes the differential entropy of the multivariate normal.
        Returns
        -------
        h : scalar
            Entropy of the multivariate normal distribution
        """
        log_pdet = self.cov_info.log_pdet
        rank = self.cov_info.rank
        return 0.5 * (rank * (_LOG_2PI + 1) + log_pdet)