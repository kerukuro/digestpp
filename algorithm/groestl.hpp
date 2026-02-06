/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_GROESTL_HPP
#define DIGESTPP_ALGORITHM_GROESTL_HPP

#include "../hasher.hpp"
#include "detail/groestl_provider.hpp"

namespace digestpp
{

/**
 * @defgroup Groestl Groestl
 * @brief Groestl Algorithm
 * @{
 */

/**
 * @brief Grøstl hash function
 * 
 * SHA-3 competition finalist based on AES-like operations.
 * Designed by Praveen Gauravaram, Lars Knudsen, Krystian Matusiewicz,
 * Florian Mendel, Christian Rechberger, Martin Schläffer, and Søren S. Thomsen.
 * 
 * Grøstl uses two AES-like permutations.
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
 * @code // Output a 256-bit Grøstl digest of a string
 * digestpp::groestl hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 8c7ad62eb26a21297bc39c2d7293b4bd4d3399fa8afab29e970471739e28b301
 * @endcode
 *
 * @sa hasher, digestpp::static_size::groestl
 */
typedef hasher<detail::groestl_provider<>> groestl;

/** @} */ // End of Groestl group

namespace static_size
{

/**
 * @defgroup Groestl Groestl
 * @{
 */

/**
 * @brief Grøstl hash function (static-size version)
 * 
 * Variant of Grøstl with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit Grøstl digest of a string
 * digestpp::static_size::groestl<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 8c7ad62eb26a21297bc39c2d7293b4bd4d3399fa8afab29e970471739e28b301
 * @endcode
 *
 * @sa hasher, digestpp::groestl
 */
template<size_t N>
using groestl = hasher<detail::groestl_provider<N>>;

/** @} */ // End of Groestl group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_GROESTL_HPP
