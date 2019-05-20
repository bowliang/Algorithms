/*
 *  math.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */


#ifndef MATH_HPP_
#define MATH_HPP_

#include "algorithm_fwd.hpp"
#include "math.hpp"

#include <cstdlib>
#include <cmath>
#include <ctime>

__BEGIN_ALGORITHM__

template<typename T>
T sign(T val) {
  if (val < 0) return -1;
  else if (val > 0) return 1;
  else return 0;
}

template <int n>
struct factorial {
  enum { result = n * factorial<n-1>::result };
};

template <>
struct factorial<0> {
  enum { result = 1 };
};


template <int n, int k, bool cond = (k <= n) >
struct combinations {
  enum { result = factorial<n>::result / (factorial<k>::result * factorial<n-k>::result) };
};

template <int n, int k>
struct combinations<n, k, false> {
  enum { result = 0 };
};

/*! set the seed used by the pseudo-random number generation
 *  \param seed - Unsigned integer used for the seed value.
 */
void srnd(size_t seed) {
  // if no seed is given, obtain the seed from the time
  if(seed == 0)
    srand((unsigned)time(NULL));
  // use seed given by the parameter seed
  else
    srand((unsigned)seed);
}


/*! Returns uniformly distributed pseudo-random real number in the range [0,1].
 *  \return A real number between 0 and 1 with double precision.
 */
double rnd() {
  return static_cast<double>(rand())/static_cast<double>(RAND_MAX);
}

__END_ALGORITHM__


#endif /* MATH_HPP_ */
