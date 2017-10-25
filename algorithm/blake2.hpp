/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_BLAKE2_HPP
#define DIGESTPP_ALGORITHM_BLAKE2_HPP

#include "detail/blake2_provider.hpp"

namespace digestpp
{

namespace detail
{
typedef blake2_provider<512, uint64_t, blake2_provider_type::hash> blake2b_provider;
typedef blake2_provider<256, uint32_t, blake2_provider_type::hash> blake2s_provider;
typedef blake2_provider<512, uint64_t, blake2_provider_type::x_hash> blake2xb_hash_provider;
typedef blake2_provider<256, uint32_t, blake2_provider_type::x_hash> blake2xs_hash_provider;
typedef blake2_provider<512, uint64_t, blake2_provider_type::xof> blake2xb_xof_provider;
typedef blake2_provider<256, uint32_t, blake2_provider_type::xof> blake2xs_xof_provider;
}

typedef hasher<detail::blake2b_provider, detail::blake2_mixin<detail::blake2b_provider>> blake2b;
typedef hasher<detail::blake2s_provider, detail::blake2_mixin<detail::blake2s_provider>> blake2s;
typedef hasher<detail::blake2xb_hash_provider, detail::blake2_mixin<detail::blake2xb_hash_provider>> blake2xb;
typedef hasher<detail::blake2xs_hash_provider, detail::blake2_mixin<detail::blake2xs_hash_provider>> blake2xs;
typedef hasher<detail::blake2xb_xof_provider, detail::blake2_mixin<detail::blake2xb_xof_provider>> blake2xb_xof;
typedef hasher<detail::blake2xs_xof_provider, detail::blake2_mixin<detail::blake2xs_xof_provider>> blake2xs_xof;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_BLAKE2_HPP

