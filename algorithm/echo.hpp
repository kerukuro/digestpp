/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_ALGORITHM_ECHO_HPP
#define DIGESTPP_ALGORITHM_ECHO_HPP

#include "../hasher.hpp"
#include "detail/echo_provider.hpp"
#include "mixin/echo_mixin.hpp"

namespace digestpp
{

/**
 * @brief Echo hash function
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
 * @mixinparams salt
 *
 * @mixin{mixin::echo_mixin}
 *
 * @par Example:\n
 * @code // Output a 256-bit Echo digest of a string
 * digestpp::echo hasher(256);
 * hasher.absorb("The quick brown fox jumps over the lazy dog");
 * std::cout << hasher.hexdigest() << '\n';
 * @endcode
 *
 * @par Example output:\n
 * @code 3c3c10b84e818cbddfd71e1aefc6cb9cd7fd1b84acb5765813e716734a97d422
 * @endcode
 *
 * @sa hasher
 */
typedef hasher<detail::echo_provider, mixin::echo_mixin> echo;

} // namespace digestpp

#endif // DIGESTPP_ALGORITHM_ECHO_HPP

