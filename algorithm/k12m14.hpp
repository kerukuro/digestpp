/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_K12M14_HPP
#define DIGESTPP_ALGORITHM_K12M14_HPP

#include "../hasher.hpp"
#include "detail/k12m14_provider.hpp"
#include "mixin/k12m14_mixin.hpp"

namespace digestpp
{

/**
 * @defgroup KangarooTwelve KangarooTwelve
 * @brief KangarooTwelve Algorithms
 * @{
 */

/**
 * @brief KangarooTwelve (K12) extendable output function
 * 
 * High-performance XOF based on Keccak with reduced rounds for speed.
 * Designed by Guido Bertoni, Joan Daemen, Michaël Peeters, Gilles Van Assche,
 * Ronny Van Keer, and Benoît Viguier (the Keccak/SHA-3 team).
 * 
 * KangarooTwelve uses 12 rounds of Keccak-p[1600] instead of 24 rounds
 * in SHAKE128, providing excellent performance while maintaining 128-bit security.
 * 
 * Recommended for high-performance applications.
 * Standardized as RFC 9861 (Informational, October 2025).
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_customization()` - Customization string for domain separation
 *
 * @mixinparams customization
 *
 * @mixin{mixin::k12m14_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::k12 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code b4f249b4f77c58df170aa4d1723db1127d82f1d98d25ddda561ada459cd11a48
 * @endcode
 *
 * @sa hasher, mixin::k12m14_mixin, m14, shake128, kt128
 */
typedef hasher<detail::k12m14_provider<128, detail::kangaroo_type::k12>, mixin::k12m14_mixin> k12;

/**
 * @brief KT128 - alias for KangarooTwelve
 *
 * Alternative name for KangarooTwelve (K12).
 * KT128 emphasizes the 128-bit security level.
 *
 * @xof
 *
 * @sa k12
 */
typedef k12 kt128;

/**
 * @brief MarsupilamiFourteen (M14) extendable output function
 *
 * High-security variant of KangarooTwelve, providing 256-bit security.
 * Uses the same design principles as K12 but with a larger security margin.
 *
 * MarsupilamiFourteen uses 14 rounds of Keccak-p[1600] and provides security
 * equivalent to SHAKE256, while maintaining better performance characteristics.
 *
 * Recommended for high-security, high-performance applications.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_customization()` - Customization string for domain separation
 *
 * @mixinparams customization
 *
 * @mixin{mixin::k12m14_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::m14 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 3611bcaa666347770dbffd4562f137c5adfe2e09f3c4268ef7c7d7c0e6c5d59c
 * @endcode
 *
 * @sa hasher, mixin::k12m14_mixin, k12, shake256
 */
typedef hasher<detail::k12m14_provider<256, detail::kangaroo_type::m14>, mixin::k12m14_mixin> m14;

/**
 * @brief KT256 extendable output function
 *
 * Alternative high-security XOF based on KangarooTwelve design principles.
 * KT256 uses 12 rounds (same as K12) but with 256-bit security configuration.
 *
 * Similar to SHAKE256 but with reduced rounds for performance.
 * Different from MarsupilamiFourteen (M14) in round count.
 *
 * Standardized as RFC 9861 (Informational, October 2025).
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_customization()` - Customization string for domain separation
 *
 * @xof
 *
 * @mixinparams customization
 *
 * @mixin{mixin::k12m14_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::kt256 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code b23d2e9cea9f4904e02bec06817fc10ce38ce8e93ef4c89e6537076af8646404
 * @endcode
 *
 * @sa hasher, mixin::k12m14_mixin, k12, m14, shake256
 */
typedef hasher<detail::k12m14_provider<256, detail::kangaroo_type::k12>, mixin::k12m14_mixin> kt256;

/** @} */ // End of KangarooTwelve group

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_K12M14_HPP
