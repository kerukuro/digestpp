/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA1_HPP
#define DIGESTPP_ALGORITHM_SHA1_HPP

#include "detail/sha1_provider.hpp"

namespace digestpp
{

typedef hasher<detail::sha1_provider> sha1;

} // namespace digestpp

#endif

