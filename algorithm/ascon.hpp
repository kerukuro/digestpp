/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_ASCON_HPP
#define DIGESTPP_ALGORITHM_ASCON_HPP

#include "../hasher.hpp"
#include "detail/ascon_provider.hpp"
#include "mixin/ascon_cxof_mixin.hpp"

/// digestpp namespace
namespace digestpp
{

/**
 * @defgroup ASCON ASCON
 * @brief ASCON Algorithms
 * @{
 */

/**
 * @brief ASCON-HASH (Ascon-Hash) hash function
 *
 * Winner of the NIST Lightweight Cryptography (LWC) competition (2023).
 * Designed by Christoph Dobraunig, Maria Eichlseder, Florian Mendel, and Martin Schläffer.
 *
 * Ascon-Hash uses a sponge construction with a 320-bit permutation and is designed
 * to provide excellent performance on both software and hardware platforms with
 * minimal resource requirements.
 * 
 * Standardized in NIST SP 800-232 (August 2025).
 *
 * @see https://csrc.nist.gov/pubs/sp/800/232/ipd
 * 
 * @hash
 *
 * @outputsize 256 bits
 *
 * @par Example:
 * @code // Output a 256-bit Ascon-Hash digest of a string
 * digestpp::ascon_hash hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 23414503bf4bde7ad0e85aec94c22ae2d7cd807996b537f9564fc2974053f139
 * @endcode
 *
 * @sa hasher, ascon_xof
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::hash>> ascon_hash;

/**
 * @brief ASCON-XOF128 extendable output function
 *
 * Extendable output function from the Ascon family.
 * Part of the NIST Lightweight Cryptography standard.
 *
 * Ascon-XOF provides 128-bit security and can generate arbitrary-length output,
 * making it suitable for key derivation, random number generation, and other
 * applications in resource-constrained environments.
 *
 * Standardized in NIST SP 800-232 (August 2025).
 *
 * @xof
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::ascon_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f3df449acea2811a43db747c1caa208f3402a17e5ceb43315455d7deff1ffc90
 * @endcode
 *
 * @sa hasher, ascon_hash, ascon_cxof
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::xof>> ascon_xof;

/**
 * @brief ASCON-CXOF128 customizable extendable output function
 *
 * A variant of ASCON-XOF128 that accepts a **customization string**.
 * This allows for domain separation: different customization strings produce
 * completely unrelated output streams for the same input message.
 *
 * Part of the NIST Lightweight Cryptography standard.
 *
 * When used without customization, output differs from Ascon-XOF128.
 *
 * Standardized in NIST SP 800-232 (August 2025).
 * Provides 128-bit security level.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_customization()` - Customization string for domain separation
 * 
 * @mixinparams customization
 *
 * @mixin{mixin::ascon_cxof_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::ascon_cxof hasher;
 * hasher.set_customization("My Custom ASCON");
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 73910abcd1ffbbd7685947734b964c516bff020c372d6a7b684ce23c69960598
 * @endcode
 *
 * @sa hasher, mixin::ascon_cxof_mixin, ascon_xof
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::cxof>, mixin::ascon_cxof_mixin> ascon_cxof;

/** @} */ // End of ASCON group

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ASCON_HPP
