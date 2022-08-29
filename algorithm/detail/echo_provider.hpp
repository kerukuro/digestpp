/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_ECHO_HPP
#define DIGESTPP_PROVIDERS_ECHO_HPP

#include "../../detail/functions.hpp"
#include "../../detail/absorb_data.hpp"
#include "../../detail/validate_hash_size.hpp"
#include "constants/echo_constants.hpp"
#include <array>

namespace digestpp
{

namespace detail
{

namespace echo_functions
{
	static inline void shift_rows(uint64_t* w)
	{
		std::swap(w[2], w[10]);
		std::swap(w[3], w[11]);
		std::swap(w[4], w[20]);
		std::swap(w[5], w[21]);
		std::swap(w[6], w[30]);
		std::swap(w[7], w[31]);
		std::swap(w[12], w[28]);
		std::swap(w[13], w[29]);
		std::swap(w[22], w[14]);
		std::swap(w[23], w[15]);
		std::swap(w[30], w[14]);
		std::swap(w[31], w[15]);
		std::swap(w[26], w[18]);
		std::swap(w[27], w[19]);
		std::swap(w[26], w[10]);
		std::swap(w[27], w[11]);
	}

	static inline void mix_columns(uint64_t* w)
	{
		for (int i = 0; i < 4; i++)
		{
			for (int j = 0; j < 2; j++)
			{
				const uint64_t firstbits = 0xfefefefefefefefeull;
				const uint64_t lastbit = 0x0101010101010101ull;
				size_t idx = i * 4 * 2 + j;
				uint64_t a = w[idx];
				uint64_t b = w[idx + 2];
				uint64_t c = w[idx + 4];
				uint64_t d = w[idx + 6];

				uint64_t dblA = ((a << 1) & firstbits) ^ (((a >> 7) & lastbit) * 0x1b);
				uint64_t dblB = ((b << 1) & firstbits) ^ (((b >> 7) & lastbit) * 0x1b);
				uint64_t dblC = ((c << 1) & firstbits) ^ (((c >> 7) & lastbit) * 0x1b);
				uint64_t dblD = ((d << 1) & firstbits) ^ (((d >> 7) & lastbit) * 0x1b);

				uint64_t WT4 = w[idx] ^ w[idx + 2] ^ w[idx + 4] ^ w[idx + 6];

				w[idx] = dblA ^ dblB ^ b ^ c ^ d;
				w[idx + 2] = dblB ^ dblC ^ c ^ d ^ a;
				w[idx + 4] = dblC ^ dblD ^ d ^ a ^ b;
				w[idx + 6] = dblD ^ dblA ^ a ^ b ^ c;
			}
		}
	}

	static inline void sub_words(uint64_t* w, uint64_t* salt, uint64_t& counter)
	{
		for (int r = 0; r < 16; r++)
		{
			size_t idx = r * 2;
			size_t idx1 = r * 2 + 1;
			uint32_t t0 = static_cast<uint32_t>(counter)
				^ echo_constants<void>::T[0][(unsigned char)(w[idx])]
				^ echo_constants<void>::T[1][(unsigned char)(w[idx] >> 40)]
				^ echo_constants<void>::T[2][(unsigned char)(w[idx1] >> 16)]
				^ echo_constants<void>::T[3][(unsigned char)(w[idx1] >> 56)];
			uint32_t t1 = (counter >> 32)
				^ echo_constants<void>::T[0][(unsigned char)(w[idx] >> 32)]
				^ echo_constants<void>::T[1][(unsigned char)(w[idx1] >> 8)]
				^ echo_constants<void>::T[2][(unsigned char)(w[idx1] >> 48)]
				^ echo_constants<void>::T[3][(unsigned char)(w[idx] >> 24)];
			uint32_t t2 = echo_constants<void>::T[0][(unsigned char)(w[idx1])]
				^ echo_constants<void>::T[1][(unsigned char)(w[idx1] >> 40)]
				^ echo_constants<void>::T[2][(unsigned char)(w[idx] >> 16)]
				^ echo_constants<void>::T[3][(unsigned char)(w[idx] >> 56)];
			uint32_t t3 = echo_constants<void>::T[0][(unsigned char)(w[idx1] >> 32)]
				^ echo_constants<void>::T[1][(unsigned char)(w[idx] >> 8)]
				^ echo_constants<void>::T[2][(unsigned char)(w[idx] >> 48)]
				^ echo_constants<void>::T[3][(unsigned char)(w[idx1] >> 24)];

			++counter;

			w[idx] = static_cast<uint64_t>(echo_constants<void>::T[0][(unsigned char)(t0)]
				^ echo_constants<void>::T[1][(unsigned char)(t1 >> 8)]
				^ echo_constants<void>::T[2][(unsigned char)(t2 >> 16)]
				^ echo_constants<void>::T[3][(unsigned char)(t3 >> 24)])
				^ (
					static_cast<uint64_t>(echo_constants<void>::T[0][(unsigned char)(t1)]
						^ echo_constants<void>::T[1][(unsigned char)(t2 >> 8)]
						^ echo_constants<void>::T[2][(unsigned char)(t3 >> 16)]
						^ echo_constants<void>::T[3][(unsigned char)(t0 >> 24)])
					<< 32)
				^ salt[0];
			w[idx + 1] = static_cast<uint64_t>(echo_constants<void>::T[0][(unsigned char)(t2)]
				^ echo_constants<void>::T[1][(unsigned char)(t3 >> 8)]
				^ echo_constants<void>::T[2][(unsigned char)(t0 >> 16)]
				^ echo_constants<void>::T[3][(unsigned char)(t1 >> 24)])
				^ (
					static_cast<uint64_t>(echo_constants<void>::T[0][(unsigned char)(t3)]
						^ echo_constants<void>::T[1][(unsigned char)(t0 >> 8)]
						^ echo_constants<void>::T[2][(unsigned char)(t1 >> 16)]
						^ echo_constants<void>::T[3][(unsigned char)(t2 >> 24)])
					<< 32)
				^ salt[1];
		}
	}


	static inline void final256(uint64_t* h, uint64_t* w)
	{
		h[0] = h[0] ^ h[8] ^ h[16] ^ h[24] ^ w[0] ^ w[8] ^ w[16] ^ w[24];
		h[1] = h[1] ^ h[9] ^ h[17] ^ h[25] ^ w[1] ^ w[9] ^ w[17] ^ w[25];
		h[2] = h[2] ^ h[10] ^ h[18] ^ h[26] ^ w[2] ^ w[10] ^ w[18] ^ w[26];
		h[3] = h[3] ^ h[11] ^ h[19] ^ h[27] ^ w[3] ^ w[11] ^ w[19] ^ w[27];
		h[4] = h[4] ^ h[12] ^ h[20] ^ h[28] ^ w[4] ^ w[12] ^ w[20] ^ w[28];
		h[5] = h[5] ^ h[13] ^ h[21] ^ h[29] ^ w[5] ^ w[13] ^ w[21] ^ w[29];
		h[6] = h[6] ^ h[14] ^ h[22] ^ h[30] ^ w[6] ^ w[14] ^ w[22] ^ w[30];
		h[7] = h[7] ^ h[15] ^ h[23] ^ h[31] ^ w[7] ^ w[15] ^ w[23] ^ w[31];
	}

	static inline void final512(uint64_t* h, uint64_t* w)
	{
		h[0] = h[0] ^ h[16] ^ w[0] ^ w[16];
		h[1] = h[1] ^ h[17] ^ w[1] ^ w[17];
		h[2] = h[2] ^ h[18] ^ w[2] ^ w[18];
		h[3] = h[3] ^ h[19] ^ w[3] ^ w[19];
		h[4] = h[4] ^ h[20] ^ w[4] ^ w[20];
		h[5] = h[5] ^ h[21] ^ w[5] ^ w[21];
		h[6] = h[6] ^ h[22] ^ w[6] ^ w[22];
		h[7] = h[7] ^ h[23] ^ w[7] ^ w[23];
		h[8] = h[8] ^ h[24] ^ w[8] ^ w[24];
		h[9] = h[9] ^ h[25] ^ w[9] ^ w[25];
		h[10] = h[10] ^ h[26] ^ w[10] ^ w[26];
		h[11] = h[11] ^ h[27] ^ w[11] ^ w[27];
		h[12] = h[12] ^ h[28] ^ w[12] ^ w[28];
		h[13] = h[13] ^ h[29] ^ w[13] ^ w[29];
		h[14] = h[14] ^ h[30] ^ w[14] ^ w[30];
		h[15] = h[15] ^ h[31] ^ w[15] ^ w[31];
	}

}

class echo_provider
{
public:
	static const bool is_xof = false;

	echo_provider(size_t hashsize)
		: hs(hashsize)
	{
		validate_hash_size(hashsize, 512);
		zero_memory(salt);
	}

	~echo_provider()
	{
		clear();
	}

	inline void init()
	{
		pos = 0;
		total = 0;
		memset(&h[0], 0, sizeof(uint64_t)*32);

		for (int i = 0; i < (hs > 256 ? 8 : 4); i++) 
		{
			h[2 * i] = hs;
			h[2 * i + 1] = 0;
		}
	}

	inline void set_salt(const unsigned char* salt, size_t salt_len)
	{
		if (salt_len && salt_len != 16)
			throw std::runtime_error("invalid salt length");

		if (salt_len)
			memcpy(this->salt.data(), salt, salt_len);
		else
			memset(this->salt.data(), 0, 16);
	}

	inline void update(const unsigned char* data, size_t len)
	{
		detail::absorb_bytes(data, len, block_bytes(), block_bytes(), reinterpret_cast<unsigned char*>(h.data()) + 256 - block_bytes(), pos, total,
			[this](const unsigned char* data, size_t num_blks) { transform(data, num_blks, true, block_bytes() * num_blks); });
	}

	inline void final(unsigned char* hash)
	{
		unsigned char* m = reinterpret_cast<unsigned char*>(h.data()) + 256 - block_bytes();
		total += pos * 8;
		m[pos++] = 0x80;
		size_t limit = block_bytes();
		if (pos > limit - 18)
		{
			if (limit != pos)
				memset(&m[pos], 0, limit - pos);
			transform(m, 1, true, 0);
			pos = 0;
		}
		memset(&m[pos], 0, limit - 18 - pos);
		uint16_t hsize = static_cast<uint16_t>(hs);
		memcpy(&m[limit - 18], &hsize, sizeof(hsize));
		memcpy(&m[limit - 16], &total, sizeof(total));
		memset(&m[limit - 8], 0, 8);
		transform(m, 1, pos > 1, 0);

		memcpy(hash, reinterpret_cast<unsigned char*>(h.data()), hash_size() / 8);
	}

	inline void clear()
	{
		zero_memory(h);
		zero_memory(salt);
	}

	inline size_t hash_size() const { return hs; }

private:
	inline size_t block_bytes() const { return (hs > 256 ? 1024 : 1536) / 8; }

	inline void transform(const unsigned char* mp, size_t num_blks, bool addedbits, uint64_t addtototal)
	{
		unsigned char* m = reinterpret_cast<unsigned char*>(h.data()) + 256 - block_bytes();
		for (size_t blk = 0; blk < num_blks; blk++)
		{
			uint64_t w[32];

			uint64_t counter = 0;
			if (addedbits)
			{
				uint64_t delta = std::min(addtototal, static_cast<uint64_t>(block_bytes()));
				counter = total + (blk * block_bytes() + delta) * 8;
				addtototal -= delta;

				if (m != mp)
					memcpy(m, mp + block_bytes() * blk, delta);
			}
			memcpy(w, h.data(), sizeof(w));
			int rounds = hs > 256 ? 10 : 8;
			for (int l = 0; l < rounds; l++)
			{
				echo_functions::sub_words(w, salt.data(), counter);
				echo_functions::shift_rows(w);
				echo_functions::mix_columns(w);
			}

			if (hs <= 256)
				echo_functions::final256(h.data(), w);
			else
				echo_functions::final512(h.data(), w);
		}
	}

	std::array<uint64_t, 32> h;
	std::array<uint64_t, 2> salt;
	size_t hs;
	size_t pos;
	uint64_t total;

};

} // namespace detail

} // namespace digestpp

#endif
