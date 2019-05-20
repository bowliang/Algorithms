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

#include <math.h>
#include <algorithm>

__BEGIN_ALGORITHM__

template<typename T>
T sign(T val);

template <int n>
struct factorial;

template <int n, int k, bool cond = (k <= n) >
struct combinations;

//! Funtion that sets the seed used by the pseudo-random number generation.
void srnd(size_t);

//! Function that returns uniformly distributed pseudo-random real number in the range [0,1].
double rnd();

__END_ALGORITHM__


#endif /* MATH_HPP_ */
