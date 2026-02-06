/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_ECHO_HPP
#define DIGESTPP_ALGORITHM_ECHO_HPP

#include "../hasher.hpp"
#include "detail/echo_provider.hpp"
#include "mixin/echo_mixin.hpp"

namespace digestpp
{

/**
 * @defgroup ECHO ECHO
 * @brief ECHO Algorithm
 * @{
 */

/**
 * @brief Echo hash function
 * 
 * SHA-3 competition candidate based on AES-like operations.
 * Designed by Ryad Benadjila, Olivier Billet, Henri Gilbert, Gilles Macario-Rat,
 * Thomas Peyrin, Matt Robshaw, and Yannick Seurin.
 * 
 * Echo uses AES-like components in a wide-pipe construction and supports
 * salted hashing for additional security in specific scenarios.
 * 
 * SHA-3 candidate (second round).
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @defaultsize none (must be specified)
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 *
 * **Optional parameters:**
 * - `set_salt()` - 16-byte salt for randomized hashing
 *
 * @mixinparams salt
 *
 * @mixin{mixin::echo_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Echo digest of a string
 * digestpp::echo hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 3c3c10b84e818cbddfd71e1aefc6cb9cd7fd1b84acb5765813e716734a97d422
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::echo_provider<>, mixin::echo_mixin> echo;

/** @} */ // End of ECHO group

namespace static_size
{

/**
 * @defgroup ECHO ECHO
 * @{
 */

/**
 * @brief Echo hash function (static-size version)
 *
 * Variant of Echo with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * **Optional parameters:**
 * - `set_salt()` - 16-byte salt for randomized hashing
 *
 * @mixinparams salt
 *
 * @mixin{mixin::echo_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Echo digest of a string
 * digestpp::static_size::echo<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 3c3c10b84e818cbddfd71e1aefc6cb9cd7fd1b84acb5765813e716734a97d422
 * @endcode
 *
 * @sa hasher, groestl
 */
template<size_t N>
using echo = hasher<detail::echo_provider<N>, mixin::echo_mixin>;

/** @} */ // End of ECHO group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ECHO_HPP

