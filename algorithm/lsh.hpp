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
 * @brief LSH256 hash function
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
 * @par Example:\n
 * @code // Output a 256-bit LSH256 digest of a string
 * digestpp::lsh256 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code f8025b61eb10d80a7f03ccfb906222a0645bb175fdeee9595f223936edbf7070
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::lsh_provider<uint32_t>> lsh256;


/**
 * @brief LSH512 hash function
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
 * @par Example:\n
 * @code // Output a 256-bit LSH512 digest of a string
 * digestpp::lsh512 hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 5e4ebe2017e84f35420bda7486ebbd791e0ece579cc18e49341b9a526466e633
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::lsh_provider<uint64_t>> lsh512;

namespace static_length
{

/**
 * @brief LSH256 hash function (static-length version)
 *
 * @hash
 *
 * @outputsize 8 - 256 bits
 *
 * @par Example:\n
 * @code // Output a 256-bit LSH256 digest of a string
 * digestpp::static_length::lsh256<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code f8025b61eb10d80a7f03ccfb906222a0645bb175fdeee9595f223936edbf7070
 * @endcode
 *
 * @sa hasher
 */
template<size_t N>
using lsh256 = hasher<detail::lsh_provider<uint32_t, N>>;

/**
 * @brief LSH512 hash function (static-length version)
 *
 * @hash
 *
 * @outputsize 8 - 512 bits
 *
 * @par Example:\n
 * @code // Output a 256-bit LSH512 digest of a string
 * digestpp::static_length::lsh512<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 5e4ebe2017e84f35420bda7486ebbd791e0ece579cc18e49341b9a526466e633
 * @endcode
 *
 * @sa hasher
 */
template<size_t N>
using lsh512 = hasher<detail::lsh_provider<uint64_t, N>>;

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_LSH_HPP
