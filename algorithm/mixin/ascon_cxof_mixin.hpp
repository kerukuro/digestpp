/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_MIXIN_ASCON_CXOF_HPP
#define DIGESTPP_MIXIN_ASCON_CXOF_HPP

namespace digestpp
{

namespace mixin
{

/**
 * \brief Defines additional public functions for Ascon-CXOF
 * \sa hasher, ascon_cxof
 */
template<typename T>
class ascon_cxof_mixin
{
public:
	/**
	 * \brief Set customization from std::string
	 *
	 * \param[in] customization Customization string
	 * \return Reference to hasher
	 */
	inline hasher<T, mixin::ascon_cxof_mixin>& set_customization(const std::string& customization)
	{
		auto& ascon = static_cast<hasher<T, mixin::ascon_cxof_mixin>&>(*this);
		ascon.provider.set_customization(customization);
		ascon.provider.init();
		return ascon;
	}

	/**
	 * \brief Set customization from raw buffer
	 *
	 * \param[in] customization Pointer to customization bytes
	 * \param[in] customization_len Customization length (in bytes)
	 * \return Reference to hasher
	 */
	template<typename C, typename std::enable_if<detail::is_byte<C>::value>::type* = nullptr>
	inline hasher<T, mixin::ascon_cxof_mixin>& set_customization(const C* customization, size_t customization_len)
	{
		return set_customization(std::string(reinterpret_cast<const char*>(customization), customization_len));
	}
};

} // namespace mixin

} // namespace digestpp

#endif // DIGESTPP_MIXIN_ASCON_CXOF_HPP
