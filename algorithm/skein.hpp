/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SKEIN_HPP
#define DIGESTPP_ALGORITHM_SKEIN_HPP

#include "../hasher.hpp"
#include "detail/skein_provider.hpp"
#include "mixin/skein_mixin.hpp"

namespace digestpp
{

/**
 * @defgroup Skein Skein
 * @brief Skein Algorithms
 * @{
 */

/**
 * @brief Skein1024 hash function
 * 
 * SHA-3 finalist based on the Threefish tweakable block cipher.
 * Designed by Bruce Schneier, Niels Ferguson, Stefan Lucks, Doug Whiting, 
 * Mihir Bellare, Tadayoshi Kohno, Jon Callas, and Jesse Walker.
 * 
 * High-security variant of Skein using a 1024-bit internal state.
 * Provides the highest security margin in the Skein family.
 * 
 * Skein1024 produces outputs that are independent from Skein256 and Skein512
 * even for the same output length. For example: skein512(256) ≠ skein1024(256)
 * 
 * Skein1024 is designed for applications requiring very high security levels
 * or very long hash outputs (up to 1024 bits and beyond).
 * 
 * Use this variant when the required hash size is known in advance.
 * For unknown output size (streaming output), use \ref skein1024_xof.
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * @defaultsize 1024 bits
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Skein1024 digest of a string
 * digestpp::skein1024 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 054922d4393e36af62143986221555bee407671f6e57631bd7273e215a714833
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein1024_xof, digestpp::static_size::skein1024
 */
typedef hasher<detail::skein_provider<1024, false>, mixin::skein_mixin> skein1024;

/**
 * @brief Skein512 hash function
 * 
 * SHA-3 finalist based on the Threefish tweakable block cipher.
 * Designed by Bruce Schneier, Niels Ferguson, Stefan Lucks, Doug Whiting, 
 * Mihir Bellare, Tadayoshi Kohno, Jon Callas, and Jesse Walker.
 * 
 * Skein512 uses a 512-bit internal state and is the recommended variant 
 * for general-purpose use.
 * 
 * Skein512 produces outputs that are independent from Skein256 and Skein1024
 * even for the same output length. For example: skein256(256) ≠ skein512(256)
 * 
 * Use this variant when the required hash size is known in advance.
 * For unknown output size (streaming output), use \ref skein512_xof
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * @defaultsize 512 bits
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Skein512 digest of a string
 * digestpp::skein512 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code b3250457e05d3060b1a4bbc1428bc75a3f525ca389aeab96cfa34638d96e492a
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein512_xof, digestpp::static_size::skein512
 */
typedef hasher<detail::skein_provider<512, false>, mixin::skein_mixin> skein512;

/**
 * @brief Skein256 hash function
 * 
 * SHA-3 finalist based on the Threefish tweakable block cipher.
 * Designed by Bruce Schneier, Niels Ferguson, Stefan Lucks, Doug Whiting, 
 * Mihir Bellare, Tadayoshi Kohno, Jon Callas, and Jesse Walker.
 * 
 * Compact variant of Skein using a 256-bit internal state.
 * Suitable for resource-constrained environments or when smaller state is preferred.
 * 
 * Skein256 produces outputs that are independent from Skein512 and Skein1024
 * even for the same output length. For example: skein256(256) ≠ skein512(256)
 * 
 * Use this variant when the required hash size is known in advance.
 * For unknown output size (streaming output), use \ref skein256_xof.
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * @defaultsize 256 bits
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 512-bit Skein256 digest of a string
 * digestpp::skein256 hasher(512);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f8138e72cdd9e11cf09e4be198c234acb0d21a9f75f936e989cf532f1fa9f4fb21d255811f0f1592fb3617d04704add875ae7bd16ddbbeaed4eca6eb9675d2c6
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein256_xof, digestpp::static_size::skein256
 */
typedef hasher<detail::skein_provider<256, false>, mixin::skein_mixin> skein256;

/**
 * @brief Skein1024 in XOF mode
 * 
 * Extendable Output Function (XOF) mode of Skein1024.
 * Highest security variant with 1024-bit internal state.
 * 
 * In XOF mode, you can call squeeze() multiple times to generate arbitrary amounts of output.
 * For fixed-length output known in advance, use \ref skein1024.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::skein1024_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 20cd7366b0a3713037fdbf8c635ea190943261455689792a327d93a9fd74dedf
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein1024
 */
typedef hasher<detail::skein_provider<1024, true>, mixin::skein_mixin> skein1024_xof;

/**
 * @brief Skein512 in XOF mode
 *
 * Extendable Output Function (XOF) mode of Skein512.
 * Use when the required output length is not known in advance or when streaming output is needed.
 *
 * In XOF mode, you can call squeeze() multiple times to generate arbitrary amounts of output.
 * For fixed-length output known in advance, use \ref skein512.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::skein512_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code cd7447a48e387ca4461e75ede8424566f7ed816a80bfac5bed291ac107f96170
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein512
 */
typedef hasher<detail::skein_provider<512, true>, mixin::skein_mixin> skein512_xof;

/**
 * @brief Skein256 in XOF mode
 *
 * Extendable Output Function (XOF) mode of Skein256.
 * Compact variant with 256-bit internal state.
 *
 * In XOF mode, you can call squeeze() multiple times to generate arbitrary amounts of output.
 * For fixed-length output known in advance, use \ref skein256.
 *
 * @xof
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::skein256_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 217021fbabe331c5753024fe4c17a005a698b037859ca8f4f0fb9112dce5605c
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein256
 */
typedef hasher<detail::skein_provider<256, true>, mixin::skein_mixin> skein256_xof;

/** @} */ // End of Skein group

namespace static_size
{

/**
 * @defgroup Skein Skein
 * @{
 */

/**
 * @brief Skein1024 hash function (static-size version)
 * 
 * Variant of Skein1024 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Skein1024 digest of a string
 * digestpp::static_size::skein1024<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 054922d4393e36af62143986221555bee407671f6e57631bd7273e215a714833
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein1024_xof, digestpp::skein1024
 */
template<size_t N>
using skein1024 = hasher<detail::skein_provider<1024, false, N>, mixin::skein_mixin>;

/**
 * @brief Skein512 hash function (static-size version)
 *
 * Variant of Skein512 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 256-bit Skein512 digest of a string
 * digestpp::static_size::skein512<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code b3250457e05d3060b1a4bbc1428bc75a3f525ca389aeab96cfa34638d96e492a
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein512_xof, digestpp::skein512
 */
template<size_t N>
using skein512 = hasher<detail::skein_provider<512, false, N>, mixin::skein_mixin>;

/**
 * @brief Skein256 hash function (static-size version)
 * 
 * Variant of Skein256 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize arbitrary (any number of bits divisible by 8)
 *
 * **Optional parameters:**
 * - `set_key()` - Key of any length for MAC/PRF mode
 * - `set_personalization()` - Personalization string for domain separation
 * - `set_nonce()` - Nonce for randomization
 *
 * @mixinparams personalization, nonce, key
 *
 * @mixin{mixin::skein_mixin}
 *
 * @par Example:
 * @code // Output a 512-bit Skein256 digest of a string
 * digestpp::static_size::skein256<512> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f8138e72cdd9e11cf09e4be198c234acb0d21a9f75f936e989cf532f1fa9f4fb21d255811f0f1592fb3617d04704add875ae7bd16ddbbeaed4eca6eb9675d2c6
 * @endcode
 *
 * @sa hasher, mixin::skein_mixin, skein256_xof, digestpp::skein256
 */
template<size_t N>
using skein256 = hasher<detail::skein_provider<256, false, N>, mixin::skein_mixin>;

/** @} */ // End of Skein group

}

} // namespace digestpp

#endif
