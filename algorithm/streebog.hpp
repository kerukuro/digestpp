/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_STREEBOG_HPP
#define DIGESTPP_ALGORITHM_STREEBOG_HPP

#include "../hasher.hpp"
#include "detail/streebog_provider.hpp"

namespace digestpp
{

/**
 * @defgroup Streebog Streebog
 * @brief Streebog Algorithm
 * @{
 */

/**
 * @brief Streebog hash function
 * 
 * Russian national standard hash function (GOST R 34.11-2012).
 * 
 * Designed by the Russian Federal Security Service (FSB) and CryptoPro.
 * Streebog is the successor to GOST R 34.11-94 and is mandatory for use
 * in Russian government digital signature systems.
 * 
 * Based on a Merkle-Damgård construction with an AES-like compression function.
 * The algorithm uses a large 512-bit block size and S-boxes derived from
 * the Kuznyechik block cipher.
 * 
 * Standardized as RFC 6986 (Informational, August 2013).
 * Also in ISO/IEC 10118-3:2018.
 *
 * @warning **S-box Design Controversy**
 *
 * In 2019, cryptographer Léo Perrin (INRIA) discovered that Streebog's S-box has
 * a hidden mathematical structure that was not disclosed by its designers [1][2].
 * Key concerns:
 *
 * - **Undisclosed structure**: The S-box generation process was never publicly explained
 * - **Contradictory claims**: Designers claimed they avoided strong algebraic structure,
 *   but analysis revealed the S-box has "extremely strong algebraic structure" [1]
 * - **Backdoor concerns**: The discovered properties are similar to those that could
 *   enable backdoors in block ciphers [2][3]
 * - **Unknown designers**: It remains unclear who exactly designed the S-box and why [1]
 *
 * At IETF CFRG Meeting 105, Perrin stated: "the designers of these algorithms have
 * provided misleading information" and recommended that "these algorithms cannot be
 * trusted and should be deprecated" [3].
 *
 * **References:**
 * - [1] Perrin, L. (2019). "On the S-Box of Streebog and Kuznyechik"
 *   https://who.paris.inria.fr/Leo.Perrin/pi.html
 * - [2] Vice/Motherboard (2024). "Experts Doubt Russian Claims That Cryptographic Flaw Was a Coincidence"
 * - [3] IETF CFRG Meeting 105 Slides: "Streebog and Kuznyechik - Inconsistencies in the Claims"
 *
 * @hash
 *
 * @outputsize 256 / 512 bits
 *
 * @defaultsize none
 *
 * @throw std::runtime_error if the requested digest size is not supported
 *
 * @par Example:
 * @code // Output a 256-bit Streebog digest of a string
 * digestpp::streebog hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 3e7dea7f2384b6c5a3d0e24aaa29c05e89ddd762145030ec22c71a6db8b2c1f4
 * @endcode
 *
 * @sa hasher, kupyna, digestpp::static_size::streebog
 */
typedef hasher<detail::streebog_provider<>> streebog;

/** @} */ // End of Streebog group

namespace static_size
{

/**
 * @defgroup Streebog Streebog
 * @{
 */

/**
 * @brief Streebog hash function (static-size version)
 * 
 * Variant of Streebog with output size specified as template parameter.
 *
 * @warning **S-box Design Controversy**
 *
 * In 2019, cryptographer Léo Perrin (INRIA) discovered that Streebog's S-box has
 * a hidden mathematical structure that was not disclosed by its designers [1][2].
 * Key concerns:
 *
 * - **Undisclosed structure**: The S-box generation process was never publicly explained
 * - **Contradictory claims**: Designers claimed they avoided strong algebraic structure,
 *   but analysis revealed the S-box has "extremely strong algebraic structure" [1]
 * - **Backdoor concerns**: The discovered properties are similar to those that could
 *   enable backdoors in block ciphers [2][3]
 * - **Unknown designers**: It remains unclear who exactly designed the S-box and why [1]
 *
 * At IETF CFRG Meeting 105, Perrin stated: "the designers of these algorithms have
 * provided misleading information" and recommended that "these algorithms cannot be
 * trusted and should be deprecated" [3].
 *
 * **References:**
 * - [1] Perrin, L. (2019). "On the S-Box of Streebog and Kuznyechik"
 *   https://who.paris.inria.fr/Leo.Perrin/pi.html
 * - [2] Vice/Motherboard (2024). "Experts Doubt Russian Claims That Cryptographic Flaw Was a Coincidence"
 * - [3] IETF CFRG Meeting 105 Slides: "Streebog and Kuznyechik - Inconsistencies in the Claims"
 *
 * @hash
 *
 * @outputsize 256 / 512 bits
 *
 * @par Example:
 * @code // Output a 256-bit Streebog digest of a string
 * digestpp::static_size::streebog<256> hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:
 * @code 3e7dea7f2384b6c5a3d0e24aaa29c05e89ddd762145030ec22c71a6db8b2c1f4
 * @endcode
 *
 * @sa hasher, kupyna, digestpp::streebog
 */
template<size_t N>
using streebog = hasher<detail::streebog_provider<N>>;

/** @} */ // End of Streebog group

}

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_STREEBOG_HPP
