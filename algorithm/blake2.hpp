/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_BLAKE2_HPP
#define DIGESTPP_ALGORITHM_BLAKE2_HPP

#include "detail/blake2_provider.hpp"

namespace digestpp
{

typedef hasher<detail::blake2_provider<uint64_t, detail::blake2_type::hash>, detail::blake2_mixin> blake2b;
typedef hasher<detail::blake2_provider<uint32_t, detail::blake2_type::hash>, detail::blake2_mixin> blake2s;
typedef hasher<detail::blake2_provider<uint64_t, detail::blake2_type::x_hash>, detail::blake2_mixin> blake2xb;
typedef hasher<detail::blake2_provider<uint32_t, detail::blake2_type::x_hash>, detail::blake2_mixin> blake2xs;
typedef hasher<detail::blake2_provider<uint64_t, detail::blake2_type::xof>, detail::blake2_mixin> blake2xb_xof;
typedef hasher<detail::blake2_provider<uint32_t, detail::blake2_type::xof>, detail::blake2_mixin> blake2xs_xof;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_BLAKE2_HPP

