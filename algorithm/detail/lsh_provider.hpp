/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_LSH_HPP
#define DIGESTPP_PROVIDERS_LSH_HPP

#include "../../detail/functions.hpp"
#include "../../detail/absorb_data.hpp"
#include "../../detail/validate_hash_size.hpp"
#include "constants/lsh_constants.hpp"
#include <array>

namespace digestpp
{

namespace detail
{

namespace lsh_functions
{

	template<typename T>
	inline T step_constant(size_t scidx, size_t idx);

	template<>
	inline uint32_t step_constant(size_t scidx, size_t idx)
	{
		return lsh_constants<void>::SC256[scidx][idx];
	}

	template<>
	inline uint64_t step_constant(size_t scidx, size_t idx)
	{
		return lsh_constants<void>::SC512[scidx][idx];
	}

	template<typename T>
	inline int gamma(size_t idx, T dummy = T());

	template<>
	inline int gamma(size_t idx, uint32_t)
	{
		return lsh_constants<void>::G256[idx];
	}

	template<>
	inline int gamma(size_t idx, uint64_t)
	{
		return lsh_constants<void>::G512[idx];
	}

	template<typename T>
	inline int alphabeta(size_t idx, T dummy = T());

	template<>
	inline int alphabeta(size_t idx, uint32_t)
	{
		return lsh_constants<void>::AB256[idx];
	}

	template<>
	inline int alphabeta(size_t idx, uint64_t)
	{
		return lsh_constants<void>::AB512[idx];
	}
}

template<typename T, size_t HS = 0>
class lsh_provider
{
public:
	static const bool is_xof = false;

	template<size_t hss=HS, typename std::enable_if<hss == 0>::type* = nullptr>
	lsh_provider(size_t hashsize)
		: hs(hashsize)
	{
		static_assert(sizeof(T) == 4 || sizeof(T) == 8, "LSH only supports 4 and 8 bits word size");
		validate_hash_size(hashsize, N);
	}

	template<size_t hss=HS, typename std::enable_if<hss != 0>::type* = nullptr>
	lsh_provider()
		: hs(hss)
	{
		static_assert(sizeof(T) == 4 || sizeof(T) == 8, "LSH only supports 4 and 8 bits word size");
		static_assert(hss <= N && hss > 0 && hss % 8 == 0);
	}

	~lsh_provider()
	{
		clear();
	}

	inline void init()
	{
		pos = 0;
		total = 0;

		cv[0] = N / 8;
		cv[1] = hs;
		memset(&cv[2], 0, sizeof(T) * 14);
		unsigned char msg[N / 2];
		memset(msg, 0, sizeof(msg));
		transform(msg, 1);

		memset(&t[0], 0, sizeof(T) * 16);
		memset(&msgexp, 0, sizeof(msgexp));
	}

	inline void update(const unsigned char* data, size_t len)
	{
		detail::absorb_bytes(data, len, block_bytes(), block_bytes(), m.data(), pos, total,
			[this](const unsigned char* data, size_t len) { transform(data, len); });
	}

	inline void final(unsigned char* hash)
	{
		m[pos++] = 0x80;
		total += pos * 8;
		if (pos != block_bytes())
			memset(&m[pos], 0, block_bytes() - pos);
		transform(m.data(), 1);

		T h[N / 2];
		for (size_t i = 0; i < 8; ++i)
			h[i] = cv[i] ^ cv[i + 8];
		memcpy(hash, h, hash_size() / 8);
	}

	inline void clear()
	{
		zero_memory(cv);
		zero_memory(t);
		zero_memory(m);
		zero_memory(msgexp);
	}

	inline size_t hash_size() const { return hs; }

private:
	inline size_t block_bytes() const { return N / 2; }

	inline void msgexpand(const unsigned char* mp)
	{
		memcpy(msgexp.data(), mp, block_bytes());
		for (size_t i = 2; i < NS + 1; i++)
		{
			msgexp[i][0] = msgexp[i - 1][0] + msgexp[i - 2][3];
			msgexp[i][1] = msgexp[i - 1][1] + msgexp[i - 2][2];
			msgexp[i][2] = msgexp[i - 1][2] + msgexp[i - 2][0];
			msgexp[i][3] = msgexp[i - 1][3] + msgexp[i - 2][1];
			msgexp[i][4] = msgexp[i - 1][4] + msgexp[i - 2][7];
			msgexp[i][5] = msgexp[i - 1][5] + msgexp[i - 2][4];
			msgexp[i][6] = msgexp[i - 1][6] + msgexp[i - 2][5];
			msgexp[i][7] = msgexp[i - 1][7] + msgexp[i - 2][6];
			msgexp[i][8] = msgexp[i - 1][8] + msgexp[i - 2][11];
			msgexp[i][9] = msgexp[i - 1][9] + msgexp[i - 2][10];
			msgexp[i][10] = msgexp[i - 1][10] + msgexp[i - 2][8];
			msgexp[i][11] = msgexp[i - 1][11] + msgexp[i - 2][9];
			msgexp[i][12] = msgexp[i - 1][12] + msgexp[i - 2][15];
			msgexp[i][13] = msgexp[i - 1][13] + msgexp[i - 2][12];
			msgexp[i][14] = msgexp[i - 1][14] + msgexp[i - 2][13];
			msgexp[i][15] = msgexp[i - 1][15] + msgexp[i - 2][14];
		}
	}

	inline void addmix(size_t l, size_t i, T sc, int alpha, int beta, int gamma)
	{
		T x = cv[l] ^ msgexp[i][l];
		T y = cv[l + 8] ^ msgexp[i][l + 8];
		x = rotate_left(x + y, alpha) ^ sc;
		y = rotate_left(x + y, beta);
		t[l] = x + y;
		t[l + 8] = rotate_left(y, gamma);
	}

	inline void step(size_t i, int alpha, int beta)
	{
		addmix(0, i, lsh_functions::step_constant<T>(i, 0), alpha, beta, lsh_functions::gamma<T>(0));
		addmix(1, i, lsh_functions::step_constant<T>(i, 1), alpha, beta, lsh_functions::gamma<T>(1));
		addmix(2, i, lsh_functions::step_constant<T>(i, 2), alpha, beta, lsh_functions::gamma<T>(2));
		addmix(3, i, lsh_functions::step_constant<T>(i, 3), alpha, beta, lsh_functions::gamma<T>(3));
		addmix(4, i, lsh_functions::step_constant<T>(i, 4), alpha, beta, lsh_functions::gamma<T>(4));
		addmix(5, i, lsh_functions::step_constant<T>(i, 5), alpha, beta, lsh_functions::gamma<T>(5));
		addmix(6, i, lsh_functions::step_constant<T>(i, 6), alpha, beta, lsh_functions::gamma<T>(6));
		addmix(7, i, lsh_functions::step_constant<T>(i, 7), alpha, beta, lsh_functions::gamma<T>(7));
		cv[0] = t[6];
		cv[1] = t[4];
		cv[2] = t[5];
		cv[3] = t[7];
		cv[4] = t[12];
		cv[5] = t[15];
		cv[6] = t[14];
		cv[7] = t[13];
		cv[8] = t[2];
		cv[9] = t[0];
		cv[10] = t[1];
		cv[11] = t[3];
		cv[12] = t[8];
		cv[13] = t[11];
		cv[14] = t[10];
		cv[15] = t[9];
	}

	inline void transform(const unsigned char* mp, size_t num_blks)
	{
		for (size_t blk = 0; blk < num_blks; blk++)
		{
			msgexpand(mp + block_bytes() * blk);
			for (size_t i = 0; i < NS; i += 2)
			{
				step(i, lsh_functions::alphabeta<T>(0), lsh_functions::alphabeta<T>(1));
				step(i + 1, lsh_functions::alphabeta<T>(2), lsh_functions::alphabeta<T>(3));
			}
			for (size_t i = 0; i < 16; ++i)
				cv[i] ^= msgexp[NS][i];
		}
	}

	constexpr static size_t N = sizeof(T) == 4 ? 256 : 512;
	constexpr static size_t NS = sizeof(T) == 4 ? 26 : 28;

	std::array<T, 16> cv;
	std::array<T, 16> t;
	std::array<std::array<T, 16>, NS + 1> msgexp;
	std::array<unsigned char, N / 2> m;
	size_t hs;
	size_t pos;
	uint64_t total;
};

} // namespace detail

} // namespace digestpp

#endif
