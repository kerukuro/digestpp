/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_KUPYNA_HPP
#define DIGESTPP_ALGORITHM_KUPYNA_HPP

#include "../hasher.hpp"
#include "detail/kupyna_provider.hpp"

namespace digestpp
{

/**
 * @defgroup Kupyna Kupyna
 * @brief Kupyna Algorithm
 * @{
 */

/**
 * @brief Kupyna hash function
 *
 * Ukrainian national standard hash function (DSTU 7564:2014).
 * Designed by Roman Oliynykov, Ivan Gorbenko, Oleksandr Kazymyrov,
 * Victor Ruzhentsev, Oleksandr Kuznetsov, Yurii Gorbenko, Artem Boiko,
 * Oleksandr Dyrda, Viktor Dolgov, and Andrii Pushkaryov.
 *
 * Kupyna is based on a Merkle-Damgård construction with Davies-Meyer compression
 * function, using an AES-like block cipher as the internal primitive.
 *
 * Designed to replace GOST R 34.11-94 in Ukrainian government and military applications.
 * The algorithm provides good security margins and competitive performance.
 *
 * Ukrainian national standard (DSTU 7564:2014).
 *
 * @hash
 *
 * @outputsize 256 / 512 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * @par Example:
 * @code // Output a 256-bit Kupyna digest of a string
 * digestpp::kupyna hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 996899f2d7422ceaf552475036b2dc120607eff538abf2b8dff471a98a4740c6
 * @endcode
 *
 * @sa hasher, groestl
 */

typedef hasher<detail::kupyna_provider<>> kupyna;

/** @} */ // End of Kupyna group

namespace static_size
{

/**
 * @defgroup Kupyna Kupyna
 * @{
 */

/**
 * @brief Kupyna hash function (static-size version)
 * 
 * Variant of Kupyna with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 256 / 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit Kupyna digest of a string
 * digestpp::static_size::kupyna<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 996899f2d7422ceaf552475036b2dc120607eff538abf2b8dff471a98a4740c6
 * @endcode
 *
 * @sa hasher, groestl
 */

template<size_t N>
using kupyna = hasher<detail::kupyna_provider<N>>;

/** @} */ // End of Kupyna group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_KUPYNA_HPP
