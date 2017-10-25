/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_GROESTL_HPP
#define DIGESTPP_ALGORITHM_GROESTL_HPP

#include "detail/groestl_provider.hpp"

namespace digestpp
{

typedef hasher<detail::groestl_provider> groestl;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_GROESTL_HPP

