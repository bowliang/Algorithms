/*
 *  algorithm_fwd.hpp
 *  algorithm
 *
 *  Created by Bowen Liang.
 *
 */

#ifndef ALGORITHM_FWD_HPP_
#define ALGORITHM_FWD_HPP_

#include <cstddef>
#include <string>

#include "algorithm-config.hpp"

#ifndef HAVE_NEW_STD

// define static assert macro only if the new standard is not supported
#define STATIC_CHECK(expr, msg) \
{ CompileTimeError<((expr) != 0)> ERROR_##msg; (void)ERROR_##msg; }

#endif /* HAVE_NEW_STD */

#define __BEGIN_ALGORITHM__ namespace algorithm {
#define __END_ALGORITHM__ }


__BEGIN_ALGORITHM__


__END_ALGORITHM__



#endif /* ALGORITHM_FWD_HPP_ */


