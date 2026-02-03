/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_ASCON_CONSTANTS_HPP
#define DIGESTPP_PROVIDERS_ASCON_CONSTANTS_HPP

namespace digestpp
{

namespace detail
{

template<typename T>
struct ascon_constants
{
	const static uint64_t RC[12];
	const static uint64_t IVHASH[5];
	const static uint64_t IVXOF[5];
	const static uint64_t IVCXOF[5];
};

template<typename T>
const uint64_t ascon_constants<T>::RC[12] = {
	0x00000000000000f0ull, 0x00000000000000e1ull, 0x00000000000000d2ull, 0x00000000000000c3ull,
	0x00000000000000b4ull, 0x00000000000000a5ull, 0x0000000000000096ull, 0x0000000000000087ull,
	0x0000000000000078ull, 0x0000000000000069ull, 0x000000000000005aull, 0x000000000000004bull
};

template<typename T>
const uint64_t ascon_constants<T>::IVHASH[5] = {
	0x9b1e5494e934d681ull, 0x4bc3a01e333751d2ull, 0xae65396c6b34b81aull, 0x3c7fd4a4d56a4db3ull,
	0x1a5c464906c5976dull
};

template<typename T>
const uint64_t ascon_constants<T>::IVXOF[5] = {
	0xda82ce768d9447ebull, 0xcc7ce6c75f1ef969ull, 0xe7508fd780085631ull, 0x0ee0ea53416b58ccull,
	0xe0547524db6f0bdeull
};

template<typename T>
const uint64_t ascon_constants<T>::IVCXOF[5] = {
	0x675527c2a0e8de03ull, 0x43d12d7dc0377bbcull, 0xe9901dec426e81b5ull, 0x2ab14907720780b6ull,
	0x8f3f1d02d432bc46ull
};

enum class ascon_type
{
	hash,
	xof,
	cxof
};

} // namespace detail

} // namespace digestpp

#endif // DIGESTPP_PROVIDERS_ASCON_CONSTANTS_HPP
