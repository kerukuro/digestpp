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
 * @defgroup Esch Esch
 * @brief Esch Algorithms
 * @{
 */

/**
 * @brief Esch hash function
 * 
 * Hash function based on the Sparkle permutation family.
 * A finalist in the **NIST Lightweight Cryptography** competition.
 * 
 * Designed by Christof Beierle, Alex Biryukov, Luan Cardoso dos Santos,
 * Johann Großschädl, Léo Perrin, Aleksei Udovenko, Vesselin Velichkov,
 * and Qingju Wang.
 * 
 * Esch uses the ARX (Addition-Rotation-XOR) design philosophy and is optimized
 * for software implementations on resource-constrained devices. The algorithm
 * provides good performance on both 8-bit microcontrollers and 32-bit/64-bit platforms.
 * 
 * @hash
 *
 * @outputsize 256 / 384 bits
 *
 * @defaultsize none (must be specified)
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * @par Example:
 * @code // Output a 256-bit Esch digest of a string
 * digestpp::esch hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code d43f87a0fe60fc5925064880c6116c136b6d94fa24a93dffcb35d178c3af932c
 * @endcode
 *
 * @sa hasher, esch256_xof
 */
typedef hasher<detail::esch_provider<512, false>> esch;

/**
 * @brief XOEsch256 (Esch-256 in XOF mode)
 * 
 * Extendable output function based on Esch-256/Sparkle384.
 * 
 * XOEsch allows squeezing arbitrary amounts of data, making it suitable
 * for key derivation and other applications in lightweight cryptography.
 * 
 * Lightweight alternative to SHAKE for constrained environments 
 * based on Sparkle384 permutation.
 *
 * @xof
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::esch_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 8f2e2748fb97b99ad18aed8f9f72cad036fb00b1a21147bb0273551d07bf9d80
 * @endcode
 *
 * @sa hasher, esch, esch384_xof
 */
typedef hasher<detail::esch_provider<384, true>> esch256_xof;

/**
 * @brief XOEsch384 (Esch-384 in XOF mode)
 * 
 * Extendable output function based on Esch-384/Sparkle512.
 * Higher security variant providing 192-bit security level.
 * 
 * @xof
 *
 * @par Example:
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::esch_xof hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 355b7d373fdbbdbc9332586714e676087847a71d529a818930db17a268fd021f
 * @endcode
 *
 * @sa hasher, esch, esch256_xof
 */
typedef hasher<detail::esch_provider<512, true>> esch384_xof;

/** @} */ // End of Esch group

namespace static_size
{

/**
 * @defgroup Esch Esch
 * @{
 */

/**
 * @brief Esch hash function (static-size version)
 * 
 * Variant of Esch with output size specified as template parameter.
 *
 * @hash
 *
 * @outputsize 256 / 384 bits
 *
 * @tparam N Digest size in bits (256 or 384).
 *
 * @par Example:
 * @code // Output a 256-bit Esch digest of a string
 * digestpp::static_size::esch<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code d43f87a0fe60fc5925064880c6116c136b6d94fa24a93dffcb35d178c3af932c
 * @endcode
 *
 * @sa hasher
 */
template<size_t N>
using esch = hasher<detail::esch_provider<512, false, N>>;

/** @} */ // End of Esch group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ESCH_HPP
