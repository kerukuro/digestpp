/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_BLAKE2P_HPP
#define DIGESTPP_PROVIDERS_BLAKE2P_HPP

#include "../../detail/functions.hpp"
#include "../../detail/absorb_data.hpp"
#include "../../detail/validate_hash_size.hpp"
#include "blake2_provider.hpp"
#include <array>
#include <limits>

namespace digestpp
{

namespace detail
{

template<typename T, blake2_type type, size_t HS = 0>
class blake2p_provider
{
public:
	static const bool is_xof = type == blake2_type::xof;

	template<size_t hss=HS, typename std::enable_if<hss == 0>::type* = nullptr>
	blake2p_provider(size_t hashsize = N)
		: main(hashsize), hs(hashsize), squeezing(false)
	{
		static_assert(sizeof(T) == 8 || sizeof(T) == 4, "Invalid T size");

		if (type == blake2_type::hash)
			detail::validate_hash_size(hashsize, N);
		else if (type == blake2_type::x_hash)
			detail::validate_hash_size(hashsize, N * sizeof(T) * 4 - 16);
		
		main.set_blake2p_params(P, 1, 0);

		for (size_t p = 0; p < P; p++)
		{
			leaf[p] = blake2_provider<T, type, HS>(hashsize);
			leaf[p].set_blake2p_params(static_cast<uint8_t>(P), 0, static_cast<uint8_t>(p));
		}
	}

	template<size_t hss=HS, typename std::enable_if<hss != 0>::type* = nullptr>
	blake2p_provider()
		: main(), hs(hss), squeezing(false)
	{
		static_assert(sizeof(T) == 8 || sizeof(T) == 4, "Invalid T size");

		const size_t limit = type == blake2_type::hash ? N : type == blake2_type::x_hash ? N * sizeof(T) * 4 - 16 : SIZE_MAX;
		static_assert(hss <= limit && hss > 0 && hss % 8 == 0);

		main.set_blake2p_params(P, 1, 0);

		for (size_t p = 0; p < P; p++)
		{
			leaf[p].set_blake2p_params(static_cast<uint8_t>(P), 0, static_cast<uint8_t>(p));
		}
	}

	~blake2p_provider()
	{
		clear();
	}

	inline void init()
	{
		pos = 0;
		total = 0;
		squeezing = false;

		main.init();
		for (size_t p = 0; p < P; p++)
		{
			leaf[p].init();
		}
	}

	inline void update(const unsigned char* data, size_t len)
	{
		detail::absorb_bytes(data, len, m.size(), m.size(), m.data(), pos, total,
			[this](const unsigned char* data, size_t len) { transform(data, len); });
	}

	inline void set_key(const std::string& key)
	{
		main.set_key(key);
		for (size_t p = 0; p < P; p++)
			leaf[p].set_key(key);
	}

	inline void set_salt(const unsigned char* salt, size_t salt_len)
	{
		main.set_salt(salt, salt_len);
		for (size_t p = 0; p < P; p++)
			leaf[p].set_salt(salt, salt_len);
	}

	inline void set_personalization(const unsigned char* personalization, size_t personalization_len)
	{
		main.set_personalization(personalization, personalization_len);
		for (size_t p = 0; p < P; p++)
			leaf[p].set_personalization(personalization, personalization_len);
	}

	inline void squeeze(unsigned char* hash, size_t hs)
	{
		size_t processed = 0;
		if (!squeezing)
		{
			squeezing = true;
			finalize();
		}
		main.squeeze(hash, hs);
	}

	inline void final(unsigned char* hash)
	{
		total += pos * 8;
		if (type == blake2_type::hash)
		{
			finalize();
			main.final(hash);
		}
		else
			squeeze(hash, hs / 8);
	}

	inline void clear()
	{
		zero_memory(m);
		main.clear();
		for (size_t p = 0; p < P; p++)
			leaf[p].clear();
	}

	inline size_t hash_size() const { return hs; }

private:

	inline void finalize()
	{
		if (512 != pos)
			memset(&m[pos], 0, 512 - pos);
		for (size_t i = 0; i < P; i++)
		{
			if (pos > i * sizeof(T) * 16)
			{
				size_t prev = i * sizeof(T) * 16;
				size_t next = prev + sizeof(T) * 16;
				size_t len = pos < next ? pos - prev : sizeof(T) * 16;
				leaf[i].update(&m[i * sizeof(T) * 16], len);
			}
			uint8_t buf[N / 8];
			leaf[i].final(buf, N);
			main.update(buf, sizeof(buf));
		}
	}

	inline void transform(const unsigned char* data, size_t num_blks)
	{
#ifdef _OPENMP
#pragma omp parallel for
#endif
		for (int i = 0; i < static_cast<int>(P); i++)
		{
			for (size_t blk = 0; blk < num_blks; blk++)
			{
				leaf[i].update(data + blk * 512 + i * 16 * sizeof(T), sizeof(T) * 16);
			}
		}
	}

	constexpr static size_t N = sizeof(T) == 8 ? 512 : 256;
	constexpr static size_t P = sizeof(T) == 8 ? 4 : 8;
	blake2_provider<T, type, HS> main;
	std::array<blake2_provider<T, type, HS>, P> leaf;
	std::array<unsigned char, 512> m;
	size_t pos;
	uint64_t total;
	size_t hs;
	bool squeezing;
};

} // namespace detail

} // namespace digestpp

#endif
