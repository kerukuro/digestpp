/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_KUPYNA_HPP
#define DIGESTPP_ALGORITHM_KUPYNA_HPP

#include "detail/kupyna_provider.hpp"

namespace digestpp
{

typedef hasher<detail::kupyna_provider> kupyna;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_KUPYNA_HPP

