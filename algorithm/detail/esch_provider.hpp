/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_ESCH_HPP
#define DIGESTPP_PROVIDERS_ESCH_HPP

#include "../../detail/functions.hpp"
#include "../../detail/absorb_data.hpp"
#include "../../detail/validate_hash_size.hpp"
#include "constants/esch_constants.hpp"
#include <array>

namespace digestpp
{

namespace detail
{

namespace esch_functions
{

template<size_t N>
static inline void sparkle(std::array<uint32_t, N>& H, int rounds, int ns)
{
	for(int s = 0; s < ns; s++) 
	{
		H[1] ^= esch_constants<void>::C[s % 8];
		H[3] ^= s;
		for (int j = 0, px = 0, py = 1; j < rounds; j++, px += 2, py += 2)
		{
			H[px] += rotate_right(H[py], 31);
			H[py] ^= rotate_right(H[px], 24);
			H[px] ^= esch_constants<void>::C[j];
			H[px] += rotate_right(H[py], 17);
			H[py] ^= rotate_right(H[px], 17);
			H[px] ^= esch_constants<void>::C[j];
			H[px] += H[py];
			H[py] ^= rotate_right(H[px], 31);
			H[px] ^= esch_constants<void>::C[j];
			H[px] += rotate_right(H[py], 24);
			H[py] ^= rotate_right(H[px], 16);
			H[px] ^= esch_constants<void>::C[j];
		}
		uint32_t x = H[0] ^ H[2] ^ H[4];
		uint32_t y = H[1] ^ H[3] ^ H[5];
		if (rounds > 6)
		{
			x ^= H[6];
			y ^= H[7];
		}
		x = rotate_right(x ^ (x << 16), 16);
		y = rotate_right(y ^ (y << 16), 16);
		
		for (int i = 0, j = rounds; i < rounds; i+=2, j+=2)
		{
			H[j] ^= H[i] ^ y;
			H[j + 1] ^= H[i + 1] ^ x;
		}
		x = H[rounds];
		y = H[rounds + 1];
		for (int i = 0; i < rounds - 2; i++)
		{
			H[i + rounds] = H[i];
			H[i] = H[i + rounds + 2];
		}
		H[rounds * 2 - 2] = H[rounds - 2];
		H[rounds * 2 - 1] = H[rounds - 1];
		H[rounds - 2] = x;
		H[rounds - 1] = y;
	}
}

}

template<size_t N, bool XOF>
class esch_provider
{
public:
	static const bool is_xof = XOF;

	template<bool xof=XOF, typename std::enable_if<!xof>::type* = nullptr>
	esch_provider(size_t hashsize)
		: hs(hashsize), squeezing(false)
	{
		static_assert(N == 384 || N == 512, "Esch only supports 384 and 512 bits state size");
		validate_hash_size(hashsize, {256, 384});
	}

	template<bool xof=XOF, typename std::enable_if<xof>::type* = nullptr>
	esch_provider() : hs(N - 128), squeezing(false)
	{
		static_assert(N == 384 || N == 512, "Esch only supports 384 and 512 bits state size");
	}

	~esch_provider()
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
	}

	inline void update(const unsigned char* data, size_t len)
	{
		detail::absorb_bytes(data, len, 16, 16 + 1, m.data(), pos, total,
			[this](const unsigned char* data, size_t len) { transform(data, len, false); });
	}

	inline void squeeze(unsigned char* hash, size_t hss)
	{
		size_t processed = 0;
		if (!squeezing)
		{
			total = 1;
			squeezing = true;
			if (pos < 16)
			{
				memset(&m[pos], 0, 16 - pos);
				m[pos] = 0x80;
				H[(hs+128)/64 - 1] ^= (XOF ? 0x5000000 : 0x1000000);
			}
			else
				H[(hs+128)/64 - 1] ^= (XOF ? 0x6000000 : 0x2000000);

			transform(m.data(), 1, true);
		}
		else if (pos < 16)
		{
			size_t to_copy = std::min(hss, 16 - pos);
			memcpy(hash, reinterpret_cast<unsigned char*>(H.data()) + pos, to_copy);
			processed += to_copy;
			pos += to_copy;
			total = 0;
		}

		while (processed < hss)
		{
			if (!total)
				esch_functions::sparkle(H, hs > 256 ? 8 : 6, hs > 256 ? 8 : 7);
			pos = std::min(hss - processed, static_cast<size_t>(16));
			memcpy(hash + processed, H.data(), pos);
			processed += pos;
			total = 0;
		}
	}

	inline void final(unsigned char* hash)
	{
		return squeeze(hash, hs / 8);
	}

	inline void clear()
	{
		zero_memory(H);
		zero_memory(m);
	}

	inline size_t hash_size() const { return hs; }

private:

	inline void transform(const unsigned char* data, size_t num_blks, bool lastBlock)
	{
		for (size_t blk = 0; blk < num_blks; blk++)
		{
			uint32_t M[4];
			for (int i = 0; i < 4; i++)
				M[i] = reinterpret_cast<const uint32_t*>(data)[blk * 4 + i];
			uint32_t x = M[0] ^ M[2];
			uint32_t y = M[1] ^ M[3];
			x = rotate_right(x ^ (x << 16), 16);
			y = rotate_right(y ^ (y << 16), 16);
			H[0] = H[0] ^ M[0] ^ y;
			H[1] = H[1] ^ M[1] ^ x;
			H[2] = H[2] ^ M[2] ^ y;
			H[3] = H[3] ^ M[3] ^ x;
			H[4] ^= y;
			H[5] ^= x;
			if (hs > 256)
			{
				H[6] ^= y;
				H[7] ^= x;
			}	
			int steps = lastBlock ? 11 : 7;
			if (hs > 256)
				steps++;
			esch_functions::sparkle(H, hs > 256 ? 8 : 6, steps);
		}
	}


	std::array<uint32_t, N / 32> H;
	std::array<unsigned char, 128> m;
	size_t pos;
	uint64_t total;
	size_t hs;
	bool squeezing;
};

} // namespace detail

} // namespace digestpp

#endif
