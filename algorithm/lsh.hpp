/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_LSH_HPP
#define DIGESTPP_ALGORITHM_LSH_HPP

#include "../hasher.hpp"
#include "detail/lsh_provider.hpp"

namespace digestpp
{

/**
 * @defgroup LSH LSH
 * @brief LSH Algorithms
 * @{
 */

/**
 * @brief LSH256 hash function
 * 
 * LSH (Lightweight Secure Hash) function designed for high performance
 * on general-purpose software environments including PCs and smart devices.
 *
 * Designed by KISA (Korea Internet & Security Agency).
 *
 * LSH uses a wide-pipe Merkle-Damgård structure. The compression function uses
 * ARX (Addition, Rotation, XOR) operations for efficient software implementation.
 * 
 * LSH (Lightweight Secure Hash) is optimized for software implementation
 * and designed as an alternative to SHA-2, with competitive performance
 * and modern security properties.
 * 
 * Korean national standard: KS X 3262.
 * Approved by Korean Cryptographic Module Validation Program (KCMVP).
 * LSH256 is optimized for 32-bit platforms.
 *
 * @hash
 *
 * @outputsize 8 - 256 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 *
 * @par Example:
 * @code // Output a 256-bit LSH256 digest of a string
 * digestpp::lsh256 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f8025b61eb10d80a7f03ccfb906222a0645bb175fdeee9595f223936edbf7070
 * @endcode
 *
 * @sa hasher, lsh512
 */
typedef hasher<detail::lsh_provider<uint32_t>> lsh256;


/**
 * @brief LSH512 hash function
 * 
 * Lightweight Secure Hash function, 64-bit word variant.
 * Designed by KISA (Korea Internet & Security Agency).
 * 
 * LSH-512 is optimized for 64-bit platforms and provides higher security levels
 * than LSH-256, with support for up to 512-bit output.
 * 
 * Korean national standard: KS X 3262.
 * Approved by Korean Cryptographic Module Validation Program (KCMVP).
 * LSH512 is optimized for 64-bit platforms.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not divisible by 8 (full bytes),
 * or is not within the supported range
 *
 * @par Example:
 * @code // Output a 256-bit LSH512 digest of a string
 * digestpp::lsh512 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 5e4ebe2017e84f35420bda7486ebbd791e0ece579cc18e49341b9a526466e633
 * @endcode
 *
 * @sa hasher, lsh256
 */
typedef hasher<detail::lsh_provider<uint64_t>> lsh512;

/** @} */ // End of LSH group

namespace static_size
{

/**
 * @defgroup LSH LSH
 * @{
 */

/**
 * @brief LSH256 hash function (static-size version)
 * 
 * Variant of LSH256 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 256 bits
 *
 * @par Example:
 * @code // Output a 256-bit LSH256 digest of a string
 * digestpp::static_size::lsh256<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code f8025b61eb10d80a7f03ccfb906222a0645bb175fdeee9595f223936edbf7070
 * @endcode
 *
 * @sa hasher, lsh512, digestpp::lsh256
 */
template<size_t N>
using lsh256 = hasher<detail::lsh_provider<uint32_t, N>>;

/**
 * @brief LSH512 hash function (static-size version)
 * 
 * Variant of LSH512 with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit LSH512 digest of a string
 * digestpp::static_size::lsh512<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 5e4ebe2017e84f35420bda7486ebbd791e0ece579cc18e49341b9a526466e633
 * @endcode
 *
 * @sa hasher, lsh256, digestpp::lsh512
 */
template<size_t N>
using lsh512 = hasher<detail::lsh_provider<uint64_t, N>>;

/** @} */ // End of LSH group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_LSH_HPP
