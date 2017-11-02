/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_KMAC_HPP
#define DIGESTPP_ALGORITHM_KMAC_HPP

#include "detail/kmac_provider.hpp"

namespace digestpp
{

typedef hasher<detail::kmac_provider<128, false>, detail::kmac_mixin> kmac128;
typedef hasher<detail::kmac_provider<256, false>, detail::kmac_mixin> kmac256;
typedef hasher<detail::kmac_provider<128, true>, detail::kmac_mixin> kmac128_xof;
typedef hasher<detail::kmac_provider<256, true>, detail::kmac_mixin> kmac256_xof;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_KMAC_HPP


