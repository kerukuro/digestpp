/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SHA2_HPP
#define DIGESTPP_ALGORITHM_SHA2_HPP

#include "../hasher.hpp"
#include "detail/sha2_provider.hpp"

namespace digestpp
{

/**
 * @defgroup SHA2 SHA2
 * @brief SHA2 Algorithm
 * @{
 */

/**
 * @brief SHA-512 hash function
 * 
 * Member of the SHA-2 family, widely used cryptographic hash function.
 * Designed by the NSA and published by NIST in 2001 as part of FIPS 180-2.
 *
 * 64-bit variant of SHA-2 family, providing high security and performance on 64-bit platforms.
 * 
 * SHA-512 can produce outputs from 8 to 512 bits. Truncated variants (SHA-512/t) provide
 * outputs different from other SHA-2 functions of the same length.
 * For example: SHA-512/256 ≠ SHA-256 (different algorithm, different output).
 * 
 * Specified in FIPS 180-4.
 *
 * SHA-512/256 is recommended over SHA-256 on 64-bit systems for better performance.
 * Full SHA-512 (512-bit output) provides the highest security in SHA-2 family.
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
 * @par Example:
 * @code // Output a SHA-512/256 digest of a string
 * digestpp::sha512 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code dd9d67b371519c339ed8dbd25af90e976a1eeefd4ad3d889005e532fc5bef04d
 * @endcode
 *
 * @sa hasher, digestpp::static_size::sha512
 */
typedef hasher<detail::sha2_provider<uint64_t>> sha512;

/**
 * @brief SHA-384 hash function
 * 
 * Member of the SHA-2 family, widely used cryptographic hash function.
 * Designed by the NSA and published by NIST in 2001 as part of FIPS 180-2.
 *
 * Uses 64-bit operations and is optimized for 64-bit platforms.
 * 
 * SHA-384 is SHA-512 with different initial values and truncated to 384 bits.
 * It provides 192-bit security level.
 * 
 * Specified in FIPS 180-4.
 * Good balance between security and performance for 64-bit systems.
 *
 * @hash
 *
 * @outputsize 384 bits
 *
 * @defaultsize 384 bits
 *
 * @par Example:
 * @code // Output a SHA-384 digest of a string
 * digestpp::sha384 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code ca737f1014a48f4c0b6dd43cb177b0afd9e5169367544c494011e3317dbf9a509cb1e5dc1e85a941bbee3d7f2afbc9b1
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::sha2_provider<uint64_t, 384>> sha384;

/**
 * @brief SHA-256 hash function
 * 
 * Member of the SHA-2 family, widely used cryptographic hash function.
 * Designed by the NSA and published by NIST in 2001 as part of FIPS 180-2.
 * 
 * SHA-256 uses 32-bit operations and is optimized for 32-bit platforms.
 * On 64-bit systems, SHA-512/256 may offer better performance.
 *
 * Specified in FIPS 180-4.
 *
 * @hash
 *
 * @outputsize 256 bits
 *
 * @defaultsize 256 bits
 *
 * @par Example:
 * @code // Output a SHA-256 digest of a string
 * digestpp::sha256 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592
 * @endcode
 *
 * @sa hasher, sha512, digestpp::static_size::sha512
 */
typedef hasher<detail::sha2_provider<uint32_t, 256>> sha256;

/**
 * @brief SHA-224 hash function
 * 
 * Member of the SHA-2 family, widely used cryptographic hash function.
 * Designed by the NSA and published by NIST in 2001 as part of FIPS 180-2.
 * 
 * SHA-224 is SHA-256 with different initial values and truncated output.
 * It uses the same algorithm and has similar performance characteristics.
 * Designed to provide 112-bit security level.
 * 
 * SHA-224 uses 32-bit operations and is optimized for 32-bit platforms.
 * On 64-bit systems, SHA-512/224 may offer better performance.
 * 
 * Specified in FIPS 180-4.
 *
 * @hash
 *
 * @outputsize 224 bits
 *
 * @defaultsize 224 bits
 *
 * @par Example:
 * @code // Output a SHA-224 digest of a string
 * digestpp::sha224 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 730e109bd7a8a32b1cb9d9a09aa2325d2430587ddbc0c38bad911525
 * @endcode
 *
 * @sa hasher, sha512, digestpp::static_size::sha512
 */
typedef hasher<detail::sha2_provider<uint32_t, 224>> sha224;

/** @} */ // End of SHA2 group

namespace static_size
{

/**
 * @defgroup SHA2 SHA2
 * @{
 */

/**
 * @brief SHA-512 hash function (static-size version)
 * 
 * Variant of SHA-512 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @par Example:
 * @code // Output a SHA-512/256 digest of a string
 * digestpp::static_size sha512<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code dd9d67b371519c339ed8dbd25af90e976a1eeefd4ad3d889005e532fc5bef04d
 * @endcode
 *
 * @sa hasher, digestpp::sha512
 */
template<size_t N>
using sha512 = hasher<detail::sha2_provider<uint64_t, N>>;

/** @} */ // End of SHA2 group

}

} // namespace digestpp

#endif
