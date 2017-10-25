/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SM3_HPP
#define DIGESTPP_ALGORITHM_SM3_HPP

#include "detail/sm3_provider.hpp"

namespace digestpp
{

typedef hasher<detail::sm3_provider> sm3;

} // namespace digestpp

#endif

