/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_JG_HPP
#define DIGESTPP_ALGORITHM_JG_HPP

#include "../hasher.hpp"
#include "detail/jh_provider.hpp"

namespace digestpp
{

/**
 * @defgroup JH JH
 * @brief JH Algorithm
 * @{
 */

/**
 * @brief JH hash function
 * 
 * SHA-3 competition finalist using bitslice design.
 * Designed by Hongjun Wu.
 * 
 * JH is based on a 1024-bit internal state and uses bitslicing technique,
 * which provides resistance to side-channel attacks and good performance
 * on various platforms.
 * 
 * SHA-3 finalist (2012) - did not win but remains a secure alternative.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 *
 * @par Example:
 * @code // Output a 256-bit JH digest of a string
 * digestpp::jh hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 6a049fed5fc6874acfdc4a08b568a4f8cbac27de933496f031015b38961608a0
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::jh_provider<>> jh;

/** @} */ // End of JH group

namespace static_size
{

/**
 * @defgroup JH JH
 * @{
 */

/**
 * @brief JH hash function (static-size version)
 * 
 * Variant of JH with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit JH digest of a string
 * digestpp::static_size::jh<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 6a049fed5fc6874acfdc4a08b568a4f8cbac27de933496f031015b38961608a0
 * @endcode
 *
 * @sa hasher
 */
template<size_t N>
using jh = hasher<detail::jh_provider<N>>;

/** @} */ // End of JH group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_JG_HPP
