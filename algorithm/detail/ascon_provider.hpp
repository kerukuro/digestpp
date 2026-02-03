/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_ASCON_HPP
#define DIGESTPP_PROVIDERS_ASCON_HPP

#include "../../detail/functions.hpp"
#include "../../detail/absorb_data.hpp"
#include "../../detail/validate_hash_size.hpp"
#include "constants/ascon_constants.hpp"
#include <array>

namespace digestpp
{

namespace detail
{

template<ascon_type type>
class ascon_provider
{
public:
	static const bool is_xof = type != ascon_type::hash;

	ascon_provider()
		: squeezing(false)
	{
	}

	~ascon_provider()
	{
		clear();
	}

	inline void init()
	{
		pos = 0;
		total = 0;
		squeezing = false;
		zero_memory(H);
		zero_memory(m);

/* 
		Here is how the initial values are calculated:

		if (type == ascon_type::cxof)
			H[0] = 0x0000080000cc0004ull;
		else if (type == ascon_type::xof)
			H[0] = 0x0000080000cc0003ull;
		else
		{
			H[0] = 0x0000080100cc0002ull;
			uint16_t hs = 256; // theoretically can be different
			memcpy(reinterpret_cast<unsigned char*>(&H[0]) + 3, &hs, sizeof(hs));
		}
		transform(m.data(), 1);
*/

		if (type == ascon_type::cxof)
			memcpy(H.data(), ascon_constants<void>::IVCXOF, sizeof(ascon_constants<void>::IVCXOF));
		else if (type == ascon_type::xof)
			memcpy(H.data(), ascon_constants<void>::IVXOF, sizeof(ascon_constants<void>::IVXOF));
		else
			memcpy(H.data(), ascon_constants<void>::IVHASH, sizeof(ascon_constants<void>::IVHASH));

		if (type == ascon_type::cxof)
		{
			uint64_t Z0 = Z.length() * 8;
			update(reinterpret_cast<const unsigned char*>(&Z0), sizeof(Z0));
			Z0 = 1ull;
			if (!Z.empty())
				update(reinterpret_cast<const unsigned char*>(Z.data()), Z.length());
			size_t pad = Z.length() % 8;
			update(reinterpret_cast<const unsigned char*>(&Z0), 8 - pad);
		}
	}

	template<ascon_type t=type, typename std::enable_if<t == ascon_type::cxof>::type* = nullptr>
	inline void set_customization(const std::string& customization)
	{
		Z = customization;
	}

	inline void update(const unsigned char* data, size_t len)
	{
		detail::absorb_bytes(data, len, 8, 8, m.data(), pos, total,
			[this](const unsigned char* data, size_t len) { transform(data, len); });
	}

	inline void squeeze(unsigned char* hash, size_t hs)
	{
		size_t r = rate / 8;
		size_t processed = 0;
		if (!squeezing)
		{
			m[pos++] = '\x01';
			if (r != pos)
				memset(&m[pos], 0, r - pos);
			transform(m.data(), 1);
			memset(m.data(), 0, r);
			squeezing = true;
		}
		else if (pos < r)
		{
			size_t to_copy = std::min(hs, r - pos);
			memcpy(hash, reinterpret_cast<unsigned char*>(H.data()) + pos, to_copy);
			processed += to_copy;
			pos += to_copy;
		}
		else if (pos == r)
		{
			transform(m.data(), 1);
		}

		while (processed < hs)
		{
			if (processed)
				transform(m.data(), 1);
			pos = std::min(hs - processed, r);
			memcpy(hash + processed, H.data(), pos);
			processed += pos;
		}
	}

	inline void final(unsigned char* hash)
	{
		return squeeze(hash, 256 / 8);
	}

	inline void clear()
	{
		zero_memory(H);
		zero_memory(m);
	}

	inline size_t hash_size() const { return 256; }

private:

	inline void transform(const unsigned char* data, size_t num_blks)
	{
		for (size_t blk = 0; blk < num_blks; blk++)
		{
			H[0] ^= reinterpret_cast<const uint64_t*>(data)[blk];

			for (int i = 0; i < 12; i++)
			{
				H[2] ^= ascon_constants<void>::RC[i];

				H[0] ^= H[4];
				H[4] ^= H[3];
				H[2] ^= H[1];

				uint64_t t0 = H[0] ^ (~H[1] & H[2]);
				uint64_t t1 = H[1] ^ (~H[2] & H[3]);
				uint64_t t2 = H[2] ^ (~H[3] & H[4]);
				uint64_t t3 = H[3] ^ (~H[4] & H[0]);
				uint64_t t4 = H[4] ^ (~H[0] & H[1]);

				t1 ^= t0;
				t0 ^= t4;
				t3 ^= t2;
				t2 = ~t2;

				H[0] = t0 ^ rotate_right(t0, 19) ^ rotate_right(t0, 28);
				H[1] = t1 ^ rotate_right(t1, 61) ^ rotate_right(t1, 39);
				H[2] = t2 ^ rotate_right(t2, 1) ^ rotate_right(t2, 6);
				H[3] = t3 ^ rotate_right(t3, 10) ^ rotate_right(t3, 17);
				H[4] = t4 ^ rotate_right(t4, 7) ^ rotate_right(t4, 41);
			}
		}
	}


	std::array<uint64_t, 5> H;
	std::array<unsigned char, 64> m;
	std::string Z;
	const size_t rate = 64;
	size_t pos;
	uint64_t total;
	bool squeezing;
};

} // namespace detail

} // namespace digestpp

#endif
