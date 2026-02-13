/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_BLAKE2P_HPP
#define DIGESTPP_ALGORITHM_BLAKE2P_HPP

#include "../hasher.hpp"
#include "detail/blake2p_provider.hpp"
#include "mixin/blake2_mixin.hpp"

/// digestpp namespace
namespace digestpp
{

/**
 * @defgroup BLAKE2 BLAKE2
 * @brief BLAKE2 Algorithms
 * @{
 */

/**
 * @brief BLAKE2bp hash function
 * 
 * Parallel version of BLAKE2b function.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @defaultsize 512 bits
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 * 
 * **Optional parameters:**
 * - `set_salt()` - 16-byte salt for hash randomization
 * - `set_personalization()` - 16-byte string for domain separation
 * - `set_key()` - Up to 64-byte key for MAC mode (keyed hashing)
 *
 * @mixinparams salt, personalization, key
 *
 * @mixin{mixin::blake2_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE2bp digest of a string
 * digestpp::blake2bp hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 4184d2acbcce03adc3b8f2fccd1ae3d6ced3aa0b051ae648f6986bb46579a0cf
 * @endcode
 *
 * @sa hasher, mixin::blake2_mixin, digestpp::blake2b, digestpp::static_size::blake2bp
 */
typedef hasher<detail::blake2p_provider<uint64_t, detail::blake2_type::hash>, mixin::blake2_mixin> blake2bp;

/**
 * @brief BLAKE2sp hash function
 * 
 * Parallel version of BLAKE2s function.
 *
 * @hash
 *
 * @outputsize 8 - 256 bits
 *
 * @defaultsize 256 bits
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 *
 * **Optional parameters:**
 * - `set_salt()` - 8-byte salt for hash randomization
 * - `set_personalization()` - 8-byte string for domain separation
 * - `set_key()` - Up to 32-byte key for MAC mode (keyed hashing)
 *
 * @mixinparams salt, personalization, key
 *
 * @mixin{mixin::blake2_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE2sp digest of a string
 * digestpp::blake2sp hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code cf192976714bb648e72b29fa90e6bf0fbc5bf2efe7d5c26ed8ff34e855368691
 * @endcode
 *
 * @sa hasher, mixin::blake2_mixin, digestpp::blake2s, digestpp::static_size::blake2sp
 */
typedef hasher<detail::blake2p_provider<uint32_t, detail::blake2_type::hash>, mixin::blake2_mixin> blake2sp;

/** @} */ // End of BLAKE2 group

namespace static_size
{

/**
 * @defgroup BLAKE2 BLAKE2
 * @{
 */

/**
 * @brief BLAKE2bp hash function (static-size version)
 * 
 * Variant of BLAKE2bp with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * **Optional parameters:**
 * - `set_salt()` - 16-byte salt
 * - `set_personalization()` - 16-byte personalization
 * - `set_key()` - Up to 64-byte key
 *
 * @mixinparams salt, personalization, key
 *
 * @mixin{mixin::blake2_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE2bp digest of a string
 * digestpp::static_size::blake2bp<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 4184d2acbcce03adc3b8f2fccd1ae3d6ced3aa0b051ae648f6986bb46579a0cf
 * @endcode
 *
 * @sa hasher, mixin::blake2_mixin, digestpp::blake2bp, blake2b
 */
template<size_t N>
using blake2bp = hasher<detail::blake2p_provider<uint64_t, detail::blake2_type::hash, N>, mixin::blake2_mixin>;

/**
 * @brief BLAKE2sp hash function (static-size version)
 * 
 * Variant of BLAKE2sp with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 256 bits
 *
 * **Optional parameters:**
 * - `set_salt()` - 8-byte salt
 * - `set_personalization()` - 8-byte personalization
 * - `set_key()` - Up to 32-byte key
 *
 * @mixinparams salt, personalization, key
 *
 * @mixin{mixin::blake2_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit BLAKE2sp digest of a string
 * digestpp::static_size::blake2sp<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code cf192976714bb648e72b29fa90e6bf0fbc5bf2efe7d5c26ed8ff34e855368691
 * @endcode
 *
 * @sa hasher, mixin::blake2_mixin, digestpp::blake2sp, blake2s
 */
template<size_t N>
using blake2sp = hasher<detail::blake2p_provider<uint32_t, detail::blake2_type::hash, N>, mixin::blake2_mixin>;

/** @} */ // End of BLAKE2 group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_BLAKE2P_HPP
