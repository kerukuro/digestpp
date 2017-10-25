/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_STREEBOG_HPP
#define DIGESTPP_ALGORITHM_STREEBOG_HPP

#include "detail/streebog_provider.hpp"

namespace digestpp
{

typedef hasher<detail::streebog_provider> streebog;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_STREEBOG_HPP

