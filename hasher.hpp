/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_HASHER_HPP
#define DIGESTPP_HASHER_HPP

#include <string>
#include <array>
#include <algorithm>
#include <vector>
#include <iterator>
#include <sstream>
#include <cstring>
#include <iomanip>

#include "detail/traits.hpp"
#include "detail/stream_width_fixer.hpp"

namespace digestpp
{

template<class HashProvider, class Mixin = detail::null_mixin<HashProvider>>
class hasher : public Mixin
{
	public:

	// Default constructor
	// Used for hash functions with fixed output size, hash functions with sensible default output size
	// and exendable output functions (XOFs).
	template<typename H=HashProvider, typename std::enable_if<std::is_default_constructible<H>::value>::type* = nullptr>
	hasher() : Mixin(provider)
	{ 
		provider.init();
	}
	
	// Constructor
	// Used with hash functions which can produce variable output size.
	// If the requested output size is not supported by the algorithm, std::runtime_error will be thrown.
	template<typename H=HashProvider, typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
	hasher(size_t hashsize) : provider(hashsize), Mixin(provider)
	{
		provider.init();
	}

	// Absorbs bytes from a C-style pointer to character buffer
	template<typename T, typename std::enable_if<detail::is_byte<T>::value>::type* = nullptr>
	inline hasher& absorb(const T* t, size_t len)
	{
		provider.update(reinterpret_cast<const unsigned char*>(t), len);
		return *this;
	}

	// Absorbs bytes from std::basic_string
	template<typename T, 
		typename std::enable_if<detail::is_byte<T>::value && !std::is_same<T, std::string::value_type>::value>::type* = nullptr>
	inline hasher& absorb(const std::basic_string<T>& istr)
	{
		if (!istr.empty())
			provider.update(reinterpret_cast<const unsigned char*>(&istr[0]), istr.size());
		return *this;
	}

	// Absorbs bytes from std::string
	inline hasher& absorb(const std::string& istr)
	{
		if (!istr.empty())
			provider.update(reinterpret_cast<const unsigned char*>(&istr[0]), istr.size());
		return *this;
	}

	// Absorbs bytes from std::istream
	template<typename T, typename std::enable_if<detail::is_byte<T>::value>::type* = nullptr>
	inline hasher& absorb(std::basic_istream<T>& istr)
	{
		const int tmp_buffer_size = 10000;
		unsigned char buffer[tmp_buffer_size];
		size_t len = 0;
		while (istr.read(reinterpret_cast<T*>(buffer), sizeof(buffer)))
		{
			provider.update(buffer, sizeof(buffer));
			len += sizeof(buffer);
		}
		size_t gcount = istr.gcount();
		if (gcount)
		{
			provider.update(buffer, gcount);
			len += gcount;
		}
		return *this;
	}

	// Absorbs bytes from an iterator sequence
	template<typename IT>
	inline hasher& absorb(IT begin, IT end)
	{
		while (begin != end)
		{
			unsigned char byte = *begin++;
			provider.update(&byte, 1);
		}
		return *this;
	}

	// In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data 
	// into user-provided preallocated buffer.
	template<typename T, typename H=HashProvider, 
		typename std::enable_if<detail::is_byte<T>::value && detail::is_xof<H>::value>::type* = nullptr>
	inline void squeeze(T* buf, size_t len)
	{
		provider.squeeze(reinterpret_cast<unsigned char*>(buf), len);
	}
	
	// In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data 
	// and write them into the output iterator.
	template<typename OI, typename H=HashProvider, typename std::enable_if<detail::is_xof<H>::value>::type* = nullptr>
	inline void squeeze(size_t len, OI it)
	{
		std::vector<unsigned char> hash(len);
		provider.squeeze(&hash[0], len);
		std::copy(hash.begin(), hash.end(), it);
	}

	// In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data 
	// and return them as hex string.
	template<typename H=HashProvider, typename std::enable_if<detail::is_xof<H>::value>::type* = nullptr>
	inline std::string hexsqueeze(size_t len)
	{
		std::ostringstream res;
		res << std::setfill('0') << std::hex;
		squeeze(len, std::ostream_iterator<detail::stream_width_fixer<unsigned int, 2>>(res, ""));
		return res.str();
	}

	// Output raw digest to user-provided preallocated buffer.
	template<typename T, typename H=HashProvider, 
		typename std::enable_if<detail::is_byte<T>::value && !detail::is_xof<H>::value>::type* = nullptr>
	inline void digest(T* buf, size_t len) const
	{
		if (len != provider.hash_size() / 8)
			throw std::runtime_error("Invalid buffer size");

		HashProvider copy(provider);
		copy.final(buf);
	}

	// In case HashProvider is a hash function, generates binary digest from absorbed data and write it via output iterator.
	template<typename OI, typename H=HashProvider, typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
	inline void digest(OI it) const
	{
		HashProvider copy(provider);
		std::vector<unsigned char> hash(provider.hash_size() / 8);
		copy.final(&hash[0]);
		std::copy(hash.begin(), hash.end(), it);
	}

	// In case HashProvider is a hash function, returns hex digest of absorbed data.
	template<typename H=HashProvider, typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
	inline std::string hexdigest() const
	{
		std::ostringstream res;
		res << std::setfill('0') << std::hex;
		digest(std::ostream_iterator<detail::stream_width_fixer<unsigned int, 2>>(res, ""));
		return res.str();
	}

	// Resets the state to start new digest computation.
	inline void reset(bool resetParameters = false) 
	{
		if (resetParameters)
			provider.clear();
		provider.init();
	}

private:
	HashProvider provider;
};


} // namespace digestpp

#endif // DIGESTPP_HASHER_HPP

