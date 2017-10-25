/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_MD5_HPP
#define DIGESTPP_ALGORITHM_MD5_HPP

#include "detail/md5_provider.hpp"

namespace digestpp
{

typedef hasher<detail::md5_provider> md5;

} // namespace digestpp

#endif

