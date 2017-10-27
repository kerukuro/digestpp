/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_K12M14_HPP
#define DIGESTPP_ALGORITHM_K12M14_HPP

#include "detail/k12m14_provider.hpp"

namespace digestpp
{

typedef hasher<detail::k12m14_provider<128>, detail::k12m14_mixin> k12;
typedef hasher<detail::k12m14_provider<256>, detail::k12m14_mixin> m14;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_K12M14_HPP


