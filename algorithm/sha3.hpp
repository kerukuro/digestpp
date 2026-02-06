/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA3_HPP
#define DIGESTPP_ALGORITHM_SHA3_HPP

#include "../hasher.hpp"
#include "detail/sha3_provider.hpp"

namespace digestpp
{

/**
 * @defgroup SHA3 SHA3
 * @brief SHA3 Algorithm
 * @{
 */

/**
 * @brief SHA-3 hash function
 *
 * Winner of the NIST SHA-3 competition (2012), based on the Keccak algorithm.
 * Designed by Guido Bertoni, Joan Daemen, Michaël Peeters, and Gilles Van Assche.
 *
 * SHA-3 uses a completely different design (sponge construction) compared to SHA-1 and SHA-2.
 * It provides an alternative to SHA-2 with different security properties and resistance
 * to length-extension attacks.
 *
 * Specified in FIPS 202 (2015).
 * SHA-3 is not a replacement for SHA-2, but an alternative.
 * SHA-2 remains secure and widely used; SHA-3 provides diversity.
 *
 * @hash
 *
 * @outputsize 224 / 256 / 384 / 512 bits
 *
 * @defaultsize none (must be specified)
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * @par Example:
 * @code // Output a 256-bit SHA-3 digest of a string
 * digestpp::sha3 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 69070dda01975c8c120c3aada1b282394e7f032fa9cf32f4cb2259a0897dfc04
 * @endcode
 *
 * @sa hasher, digestpp::static_size::sha3
 */
typedef hasher<detail::sha3_provider<>> sha3;

/** @} */ // End of SHA3 group

namespace static_size
{

/**
 * @defgroup SHA3 SHA3
 * @{
 */

/**
 * @brief SHA-3 hash function (static-size version)
 *
 * Variant of SHA-3 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 224 / 256 / 384 / 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit SHA-3 digest of a string
 * digestpp::static_size::sha3<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 69070dda01975c8c120c3aada1b282394e7f032fa9cf32f4cb2259a0897dfc04
 * @endcode
 *
 * @sa hasher, digestpp::sha3
 */
template<size_t N>
using sha3 = hasher<detail::sha3_provider<N>>;

/** @} */ // End of SHA3 group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_SHA3_HPP
