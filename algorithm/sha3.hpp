/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA3_HPP
#define DIGESTPP_ALGORITHM_SHA3_HPP

#include "detail/sha3_provider.hpp"

namespace digestpp
{

typedef hasher<detail::sha3_provider> sha3;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_SHA3_HPP


