/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHAKE_HPP
#define DIGESTPP_ALGORITHM_SHAKE_HPP

#include "../hasher.hpp"
#include "detail/shake_provider.hpp"
#include "mixin/cshake_mixin.hpp"

namespace digestpp
{

/**
 * @defgroup SHAKE SHAKE
 * @brief SHAKE Algorithms
 * @{
 */

/**
 * @brief SHAKE128 extendable output function
 * 
 * Extendable Output Function (XOF) based on SHA-3/Keccak.
 * Part of the SHA-3 standard (FIPS 202).
 * 
 * SHAKE128 provides 128-bit security and can generate arbitrary-length output.
 * Unlike fixed-length hash functions, SHAKE can produce outputs of any length,
 * and can be called multiple times to generate additional output.
 * 
 * Specified in FIPS 202.
 *
 * SHAKE128 provides security equivalent to SHA3-256 (128-bit collision resistance).
 * For customizable variant with domain separation, see \ref cshake128.
 *
 * @xof
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::shake128 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f4202e3c5852f9182a0430fd8144f0a74b95e7417ecae17db0f8cfeed0e3e66e
 * @endcode
 *
 * @sa hasher, cshake128, kmac128, k12
 */
typedef hasher<detail::shake_provider<128, 24>> shake128;

/**
 * @brief SHAKE256 extendable output function
 * 
 * Extendable Output Function (XOF) based on SHA-3/Keccak.
 * Part of the SHA-3 standard (FIPS 202).
 * 
 * SHAKE256 provides 256-bit security and can generate arbitrary-length output.
 * Recommended over SHAKE128 for applications requiring higher security.
 * 
 * Specified in FIPS 202.
 *
 * SHAKE256 provides security equivalent to SHA3-512 (256-bit collision resistance).
 * For customizable variant with domain separation, see \ref cshake256.
 *
 * @xof
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::shake256 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 2f671343d9b2e1604dc9dcf0753e5fe15c7c64a0d283cbbf722d411a0e36f6ca
 * @endcode
 *
 * @sa hasher, cshake256, kmac256, m14
 */
typedef hasher<detail::shake_provider<256, 24>> shake256;

/**
 * @brief cSHAKE128 customizable extendable output function
 *
 * Customizable variant of SHAKE128 with support for function name and customization string.
 *
 * Specified in NIST SP 800-185.
 *
 * cSHAKE provides domain separation through customization parameters, allowing
 * the same underlying function to be safely used for different purposes.
 *
 * When used without customization, cSHAKE128 produces the same output as SHAKE128.
 * Function name is reserved for NIST-defined functions; use empty string for custom applications.
 * Customization string provides domain separation for different use cases.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_function_name()` - NIST function name (usually empty for custom use)
 * - `set_customization()` - Customization string for domain separation
 *
 * @mixinparams function name, customization
 *
 * @mixin{mixin::cshake_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::cshake128 hasher;
 * hasher.set_customization("My Custom SHAKE");
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 5b831bfe752f7f05d81f18f0e83a92eb48b9e3d460c10022ecb4852aa8b1f9d4
 * @endcode
 *
 * @sa hasher, shake128, mixin::cshake_mixin, k12
 */
typedef hasher<detail::shake_provider<128, 24>, mixin::cshake_mixin> cshake128;

/**
 * @brief cSHAKE256 customizable extendable output function
 *
 * Customizable variant of SHAKE256 with support for function name and customization string.
 *
 * Specified in NIST SP 800-185.
 *
 * Higher security variant of cSHAKE128, providing 256-bit security level.
 *
 * When used without customization, cSHAKE256 produces the same output as SHAKE256.
 * Function name is reserved for NIST-defined functions; use empty string for custom applications.
 * Customization string provides domain separation for different use cases.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_function_name()` - NIST function name (usually empty for custom use)
 * - `set_customization()` - Customization string for domain separation
 *
 * @mixinparams function name, customization
 *
 * @mixin{mixin::cshake_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::cshake256 hasher;
 * hasher.set_customization("My Custom SHAKE");
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code bcebde2c2e18f6efd99ee9e0def1383e86595d72e49b4754f7f727a962c3cd3d
 * @endcode
 *
 * @sa hasher, shake256, mixin::cshake_mixin, m14
 */
typedef hasher<detail::shake_provider<256, 24>, mixin::cshake_mixin> cshake256;

/** @} */ // End of SHAKE group

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_SHAKE_HPP
