/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA1_HPP
#define DIGESTPP_ALGORITHM_SHA1_HPP

#include "../hasher.hpp"
#include "detail/sha1_provider.hpp"

namespace digestpp
{

/**
 * @defgroup SHA1 SHA1
 * @brief SHA1 Algorithm
 * @{
 */

/**
 * @brief SHA-1 hash function
 *
 * First generation Secure Hash Algorithm designed by the NSA and published by NIST in 1995.
 *
 * @warning SHA-1 is cryptographically broken and should NOT be used for security purposes.
 * Practical collision attacks exist since 2017. Use SHA-256, SHA-3, or any other hash function instead.
 *
 * SHA-1 may still be acceptable for legacy system compatibility (when security is not required).
 *
 * @hash
 *
 * @outputsize 160 bits
 *
 * @defaultsize 160 bits
 *
 * @par Example:
 * @code // Output a SHA1 digest of a string
 * digestpp::sha1 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 2fd4e1c67a2d28fced849ee1bb76e7391b93eb12
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::sha1_provider> sha1;

/** @} */ // End of SHA1 group

} // namespace digestpp

#endif
