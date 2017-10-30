/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA2_HPP
#define DIGESTPP_ALGORITHM_SHA2_HPP

#include "detail/sha2_provider.hpp"

namespace digestpp
{

typedef hasher<detail::sha2_provider<uint64_t>> sha512;
typedef hasher<detail::sha2_provider<uint64_t, 384>> sha384;
typedef hasher<detail::sha2_provider<uint32_t, 256>> sha256;
typedef hasher<detail::sha2_provider<uint32_t, 224>> sha224;


} // namespace digestpp

#endif

