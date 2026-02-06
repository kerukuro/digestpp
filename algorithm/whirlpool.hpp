/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_WHIRLPOOL_HPP
#define DIGESTPP_ALGORITHM_WHIRLPOOL_HPP

#include "../hasher.hpp"
#include "detail/whirlpool_provider.hpp"

namespace digestpp
{

/**
 * @defgroup Whirlpool Whirlpool
 * @brief Whirlpool Algorithm
 * @{
 */

/**
 * @brief Whirlpool hash function
 *
 * ISO/IEC standard hash function (ISO/IEC 10118-3:2004) based on a modified AES cipher.
 * Designed by Vincent Rijmen (co-creator of AES) and Paulo S. L. M. Barreto.
 *
 * Whirlpool uses a 512-bit block cipher in Miyaguchi-Preneel construction,
 * with an 8×8 S-box derived from the AES design principles. The algorithm
 * provides excellent security properties and is suitable for applications
 * requiring 256-bit security level.
 *
 * Standardized as ISO/IEC 10118-3:2004.
 * Recommended by NESSIE (New European Schemes for Signatures, Integrity, and Encryption).
 * Always produces 512-bit output.
 *
 * @hash
 *
 * @outputsize 512 bits
 *
 * @defaultsize 512 bits
 *
 * @par Example:
 * @code // Output a Whirlpool digest of a string
 * digestpp::whirlpool hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code b97de512e91e3828b40d2b0fdce9ceb3c4a71f9bea8d88e75c4fa854df36725fd2b52eb6544edcacd6f8beddfea403cb55ae31f03ad62a5ef54e42ee82c3fb35
 * @endcode
 *
 * @sa hasher, groestl
 */
typedef hasher<detail::whirlpool_provider> whirlpool;

/** @} */ // End of Whirlpool group

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_WHIRLPOOL_HPP
