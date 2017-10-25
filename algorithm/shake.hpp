/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHAKE_HPP
#define DIGESTPP_ALGORITHM_SHAKE_HPP

#include "detail/shake_provider.hpp"

namespace digestpp
{

typedef hasher<detail::shake_provider<128, 24>> shake128;
typedef hasher<detail::shake_provider<256, 24>> shake256;
typedef hasher<detail::shake_provider<128, 24>, detail::cshake_mixin<detail::shake_provider<128, 24>>> cshake128;
typedef hasher<detail::shake_provider<256, 24>, detail::cshake_mixin<detail::shake_provider<256, 24>>> cshake256;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_SHAKE_HPP


