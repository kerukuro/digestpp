/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_SM3_HPP
#define DIGESTPP_ALGORITHM_SM3_HPP

#include "../hasher.hpp"
#include "detail/sm3_provider.hpp"

namespace digestpp
{

/**
 * @defgroup SM3 SM3
 * @brief SM3 Algorithm
 * @{
 */

/**
 * @brief SM3 hash function
 *
 * Chinese national standard hash function (GB/T 32905-2016).
 * Designed by Xiaoyun Wang, Hongbo Yu, and Yiqun Lisa Yin.
 *
 * SM3 is part of the Chinese ShangMi (Commercial Cryptography) suite
 * of cryptographic algorithms. It is mandatory for use in Chinese
 * government and commercial applications.
 *
 * The algorithm is similar in structure to SHA-256, using a Merkle-Damgård
 * construction with 32-bit operations, but with different constants,
 * rotation amounts, and message schedule.
 *
 * Chinese national standard (GB/T 32905-2016).
 * Also standardized as ISO/IEC 10118-3:2018
 *
 * @hash
 *
 * @outputsize 256 bits
 *
 * @defaultsize 256 bits
 *
 * @par Example:
 * @code // Output a SM3 digest of a string
 * digestpp::sm3 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 5fdfe814b8573ca021983970fc79b2218c9570369b4859684e2e4c3fc76cb8ea
 * @endcode
 *
 * @sa hasher, sha256
 */
typedef hasher<detail::sm3_provider> sm3;

/** @} */ // End of SM3 group

} // namespace digestpp

#endif
