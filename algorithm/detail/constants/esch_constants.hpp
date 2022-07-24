/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_ESCH_CONSTANTS_HPP
#define DIGESTPP_PROVIDERS_ESCH_CONSTANTS_HPP

namespace digestpp
{

namespace detail
{

template<typename T>
struct esch_constants
{
	const static uint32_t C[8];
};

template<typename T>
const uint32_t esch_constants<T>::C[8] = {
	0xb7e15162, 0xbf715880, 0x38b4da56, 0x324e7738, 0xbb1185eb, 0x4f7c7b57, 0xcfbfa1c8, 0xc2b3293d
};

} // namespace detail

} // namespace digestpp

#endif
