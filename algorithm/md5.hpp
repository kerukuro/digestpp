/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_MD5_HPP
#define DIGESTPP_ALGORITHM_MD5_HPP

#include "../hasher.hpp"
#include "detail/md5_provider.hpp"

namespace digestpp
{

/**
 * @defgroup MD5 MD5
 * @brief MD5 Algorithm
 * @{
 */

/**
 * @brief MD5 hash function
 * 
 * Historic hash function designed by Ronald Rivest in 1991.
 * 
 * @warning MD5 is cryptographically BROKEN and MUST NOT be used for any security purpose.
 * Practical collision attacks have been demonstrated since 2004, and chosen-prefix
 * collision attacks are now computationally feasible.
 * 
 * **Known vulnerabilities:**
 * - Collision attacks: trivial (seconds on modern hardware)
 * - Chosen-prefix collisions: practical (2019 research)
 * - Used in real-world attacks (Flame malware, 2012)
 * - Should never be used for digital signatures, certificates, or password storage
 * 
 * MD5 may still be acceptable for legacy protocol compatibility (when no security is required).
 * 
 * @hash
 *
 * @outputsize 128 bits
 *
 * @defaultsize 128 bits
 *
 * @par Example:
 * @code // Output an MD5 digest of a string
 * digestpp::md5 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 9e107d9d372bb6826bd81d3542a419d6
 * @endcode
 *
 * @sa hasher, sha256, blake2b, skein512
 */
typedef hasher<detail::md5_provider> md5;

/** @} */ // End of MD5 group

} // namespace digestpp

#endif
