/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_BLAKE_HPP
#define DIGESTPP_ALGORITHM_BLAKE_HPP

#include "detail/blake_provider.hpp"

namespace digestpp
{

typedef hasher<detail::blake_provider, detail::blake_mixin> blake;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_BLAKE_HPP

