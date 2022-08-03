/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_MIXINS_ECHO_HPP
#define DIGESTPP_MIXINS_ECHO_HPP

namespace digestpp
{

namespace mixin
{

/**
 * \brief Defines additional public functions for ECHO algorithm.
 * \sa hasher, echo
 */
template<typename T>
class echo_mixin
{
public:

	/**
	 * \brief Set salt from std::string
	 *
	 * Supported salt size is 16 bytes.
	 *
	 * \param[in] salt String with salt
	 * \throw std::runtime_error if salt size is not supported.
	 * \return Reference to hasher
	 */
	inline hasher<T, mixin::echo_mixin>& set_salt(const std::string& salt)
	{
		return set_salt(salt.c_str(), salt.size());
	}

	/**
	 * \brief Set salt from raw buffer
	 *
	 * Supported salt size is 16 bytes.
	 *
	 * \param[in] salt Pointer to salt bytes
	 * \param[in] salt_len Salt length (in bytes)
	 * \throw std::runtime_error if salt size is not supported.
	 * \return Reference to hasher
	 */
	template<typename C, typename std::enable_if<detail::is_byte<C>::value>::type* = nullptr>
	inline hasher<T, mixin::echo_mixin>& set_salt(const C* salt, size_t salt_len)
	{
		auto& echo = static_cast<hasher<T, mixin::echo_mixin>&>(*this);
		echo.provider.set_salt(reinterpret_cast<const unsigned char*>(salt), salt_len);
		echo.provider.init();
		return echo;
	}
};

} // namespace mixin

} // namespace digestpp

#endif

