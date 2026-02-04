/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_ESCH_HPP
#define DIGESTPP_ALGORITHM_ESCH_HPP

#include "../hasher.hpp"
#include "detail/esch_provider.hpp"

/// digestpp namespace
namespace digestpp
{

/**
 * @brief Esch hash function
 *
 * @hash
 *
 * @outputsize 256 / 384 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * @par Example:\n
 * @code // Output a 256-bit Esch digest of a string
 * digestpp::esch hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code d43f87a0fe60fc5925064880c6116c136b6d94fa24a93dffcb35d178c3af932c
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::esch_provider<512, false>> esch;

/**
 * @brief Esch-256 in XOF mode
 *
 * @xof
 *
 * @par Example:\n
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::esch_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 8f2e2748fb97b99ad18aed8f9f72cad036fb00b1a21147bb0273551d07bf9d80
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::esch_provider<384, true>> esch256_xof;

/**
 * @brief Esch-384 in XOF mode
 *
 * @xof
 *
 * @par Example:\n
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::esch_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 355b7d373fdbbdbc9332586714e676087847a71d529a818930db17a268fd021f
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::esch_provider<512, true>> esch384_xof;

namespace static_length
{

/**
 * @brief Esch hash function (static-length version)
 *
 * @hash
 *
 * @outputsize 256 / 384 bits
 *
 * @par Example:\n
 * @code // Output a 256-bit Esch digest of a string
 * digestpp::static_length::esch<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code d43f87a0fe60fc5925064880c6116c136b6d94fa24a93dffcb35d178c3af932c
 * @endcode
 *
 * @sa hasher
 */
template<size_t N>
using esch = hasher<detail::esch_provider<512, false, N>>;

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ESCH_HPP
