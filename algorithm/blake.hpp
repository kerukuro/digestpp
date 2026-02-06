/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_BLAKE_HPP
#define DIGESTPP_ALGORITHM_BLAKE_HPP

#include "../hasher.hpp"
#include "detail/blake_provider.hpp"
#include "mixin/blake_mixin.hpp"

namespace digestpp
{

/**
 * @defgroup BLAKE BLAKE
 * @brief BLAKE Algorithm
 * @{
 */

/**
 * @brief BLAKE hash function (SHA-3 finalist)
 * 
 * Original BLAKE algorithm, finalist in the NIST SHA-3 competition.
 * Based on the ChaCha stream cipher and HAIFA construction.
 * Designed by Jean-Philippe Aumasson, Luca Henzen, Willi Meier, and Raphael C.-W. Phan.
 * 
 * @hash
 *
 * @outputsize 224 / 256 / 384 / 512 bits
 *
 * @defaultsize none (must be specified)
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * **Optional parameters:**
 * - `set_salt()` - Salt for hash randomization
 *   - 16 bytes for BLAKE-224 and BLAKE-256
 *   - 32 bytes for BLAKE-384 and BLAKE-512
 *
 * @mixinparams salt
 *
 * @mixin{mixin::blake_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE digest of a string
 * digestpp::blake hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 7576698ee9cad30173080678e5965916adbb11cb5245d386bf1ffda1cb26c9d7
 * @endcode
 *
 * @sa hasher, mixin::blake_mixin, digestpp::static_size::blake
 */
typedef hasher<detail::blake_provider<>, mixin::blake_mixin> blake;

/** @} */ // End of BLAKE group

namespace static_size
{

/**
 * @defgroup BLAKE BLAKE
 * @{
 */

/**
 * @brief BLAKE hash function (static-size version)
 * 
 * Variant of BLAKE with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 224 / 256 / 384 / 512 bits
 *
 * **Optional parameters:**
 * - `set_salt()` - Salt for hash randomization
 *   - 16 bytes for BLAKE-224 and BLAKE-256
 *   - 32 bytes for BLAKE-384 and BLAKE-512
 *
 * @mixinparams salt
 *
 * @mixin{mixin::blake_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE digest of a string
 * digestpp::static_size::blake<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 7576698ee9cad30173080678e5965916adbb11cb5245d386bf1ffda1cb26c9d7
 * @endcode
 *
 * @sa hasher, mixin::blake_mixin, digestpp::blake
 */
template<size_t N>
using blake = hasher<detail::blake_provider<N>, mixin::blake_mixin>;

/** @} */ // End of BLAKE group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_BLAKE_HPP
