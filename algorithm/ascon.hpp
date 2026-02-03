/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_ASCON_HPP
#define DIGESTPP_ALGORITHM_ASCON_HPP

#include "../hasher.hpp"
#include "detail/ascon_provider.hpp"
#include "mixin/ascon_cxof_mixin.hpp"

/// digestpp namespace
namespace digestpp
{

/**
 * @brief ASCON-HASH256 hash function
 *
 * @hash
 *
 * @outputsize 256 bits
 *
 * @par Example:\n
 * @code // Output a 256-bit Ascon-Hash digest of a string
 * digestpp::ascon_hash hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 23414503bf4bde7ad0e85aec94c22ae2d7cd807996b537f9564fc2974053f139
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::hash>> ascon_hash;

/**
 * @brief ASCON-XOF128 XOF function
 *
 * @xof
 *
 * @par Example:\n
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::ascon_xof128 hasher;
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code f3df449acea2811a43db747c1caa208f3402a17e5ceb43315455d7deff1ffc90
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::xof>> ascon_xof128;

/**
 * @brief ASCON-CXOF128 XOF function
 *
 * Customizable variant of ASCON-XOF128 XOF function.
 *
 * @xof
 *
 * @mixinparams customization
 *
 * @mixin{mixin::ascon_cxof_mixin}
 *
 * @par Example:\n
 * @code // Absorb a string and squeeze 32 bytes of output
 * digestpp::ascon_cxof128 hasher;
 * hasher.set_customization("My Custom ASCON");
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexsqueeze(32) << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 73910abcd1ffbbd7685947734b964c516bff020c372d6a7b684ce23c69960598
 * @endcode
 *
 * @sa hasher, mixin::ascon_cxof_mixin
 */
typedef hasher<detail::ascon_provider<detail::ascon_type::cxof>, mixin::ascon_cxof_mixin> ascon_cxof128;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ASCON_HPP
