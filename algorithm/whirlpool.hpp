/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_WHIRLPOOL_HPP
#define DIGESTPP_ALGORITHM_WHIRLPOOL_HPP

#include "detail/whirlpool_provider.hpp"

namespace digestpp
{

typedef hasher<detail::whirlpool_provider> whirlpool;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_WHIRLPOOL_HPP

