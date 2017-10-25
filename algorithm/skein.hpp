/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SKEIN_HPP
#define DIGESTPP_ALGORITHM_SKEIN_HPP

#include "detail/skein_provider.hpp"

namespace digestpp
{

typedef hasher<detail::skein_provider<1024, false>, detail::skein_mixin<detail::skein_provider<1024, false>>> skein1024;
typedef hasher<detail::skein_provider<512, false>, detail::skein_mixin<detail::skein_provider<512, false>>> skein512;
typedef hasher<detail::skein_provider<256, false>, detail::skein_mixin<detail::skein_provider<256, false>>> skein256;

typedef hasher<detail::skein_provider<1024, true>, detail::skein_mixin<detail::skein_provider<1024, true>>> skein1024_xof;
typedef hasher<detail::skein_provider<512, true>, detail::skein_mixin<detail::skein_provider<512, true>>> skein512_xof;
typedef hasher<detail::skein_provider<256, true>, detail::skein_mixin<detail::skein_provider<256, true>>> skein256_xof;

} // namespace digestpp

#endif





