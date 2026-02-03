#include "test_vectors.hpp"
#include <numeric>

int main()
{
	test_vectors(digestpp::ascon_hash(), "ascon_hash", "testvectors/ascon_hash256.txt");
	test_vectors(digestpp::blake(224), "blake/224", "testvectors/blake224.txt");
	test_vectors(digestpp::blake(256), "blake/256", "testvectors/blake256.txt");
	test_vectors(digestpp::blake(384), "blake/384", "testvectors/blake384.txt");
	test_vectors(digestpp::blake(512), "blake/512", "testvectors/blake512.txt");
	test_vectors(digestpp::blake(256), "blake/256-salt", "testvectors/blake256salt.txt");
	test_vectors(digestpp::blake(384), "blake/384-salt", "testvectors/blake384salt.txt");
	test_vectors(digestpp::blake2s(128), "blake2s/128", "testvectors/blake2s_128.txt");
	test_vectors(digestpp::blake2s(160), "blake2s/160", "testvectors/blake2s_160.txt");
	test_vectors(digestpp::blake2s(224), "blake2s/224", "testvectors/blake2s_224.txt");
	test_vectors(digestpp::blake2s(256), "blake2s/256", "testvectors/blake2s_256.txt");
	test_vectors(digestpp::blake2b(128), "blake2b/128", "testvectors/blake2b_128.txt");
	test_vectors(digestpp::blake2b(160), "blake2b/160", "testvectors/blake2b_160.txt");
	test_vectors(digestpp::blake2b(224), "blake2b/224", "testvectors/blake2b_224.txt");
	test_vectors(digestpp::blake2b(256), "blake2b/256", "testvectors/blake2b_256.txt");
	test_vectors(digestpp::blake2b(384), "blake2b/384", "testvectors/blake2b_384.txt");
	test_vectors(digestpp::blake2b(512), "blake2b/512", "testvectors/blake2b_512.txt");
	test_vectors(digestpp::blake2xb(256), "blake2xb/256", "testvectors/blake2xb_256.txt");
	test_vectors(digestpp::blake2xb(512), "blake2xb/512", "testvectors/blake2xb_512.txt");
	test_vectors(digestpp::blake2xb(2040), "blake2xb/2040", "testvectors/blake2xb_2040.txt");
	test_vectors(digestpp::blake2xb(2056), "blake2xb/2056", "testvectors/blake2xb_2056.txt");
	test_vectors(digestpp::blake2xb(2056), "blake2xb/2056-param", "testvectors/blake2xb_2056param.txt");
	test_vectors(digestpp::blake2xs(256), "blake2xs/256", "testvectors/blake2xs_256.txt");
	test_vectors(digestpp::blake2xs(2056), "blake2xs/2056", "testvectors/blake2xs_2056.txt");
	test_vectors(digestpp::blake2xs(2056), "blake2xs/2056-param", "testvectors/blake2xs_2056param.txt");
	test_vectors(digestpp::echo(224), "echo/224", "testvectors/echo224.txt");
	test_vectors(digestpp::echo(256), "echo/256", "testvectors/echo256.txt");
	test_vectors(digestpp::echo(384), "echo/384", "testvectors/echo384.txt");
	test_vectors(digestpp::echo(512), "echo/512", "testvectors/echo512.txt");
	test_vectors(digestpp::esch(256), "esch/256", "testvectors/esch256.txt");
	test_vectors(digestpp::esch(384), "esch/384", "testvectors/esch384.txt");
	test_vectors(digestpp::groestl(224), "groestl/224", "testvectors/groestl224.txt");
	test_vectors(digestpp::groestl(256), "groestl/256", "testvectors/groestl256.txt");
	test_vectors(digestpp::groestl(384), "groestl/384", "testvectors/groestl384.txt");
	test_vectors(digestpp::groestl(512), "groestl/512", "testvectors/groestl512.txt");
	test_vectors(digestpp::jh(224), "jh/224", "testvectors/jh224.txt");
	test_vectors(digestpp::jh(256), "jh/256", "testvectors/jh256.txt");
	test_vectors(digestpp::jh(384), "jh/384", "testvectors/jh384.txt");
	test_vectors(digestpp::jh(512), "jh/512", "testvectors/jh512.txt");
	test_vectors(digestpp::kupyna(256), "kupyna/256", "testvectors/kupyna256.txt");
	test_vectors(digestpp::kupyna(512), "kupyna/512", "testvectors/kupyna512.txt");
	test_vectors(digestpp::lsh256(224), "lsh256/224", "testvectors/lsh256_224.txt");
	test_vectors(digestpp::lsh256(256), "lsh256/256", "testvectors/lsh256_256.txt");
	test_vectors(digestpp::lsh512(224), "lsh512/224", "testvectors/lsh512_224.txt");
	test_vectors(digestpp::lsh512(256), "lsh512/256", "testvectors/lsh512_256.txt");
	test_vectors(digestpp::lsh512(384), "lsh512/384", "testvectors/lsh512_384.txt");
	test_vectors(digestpp::lsh512(512), "lsh512/512", "testvectors/lsh512_512.txt");
	test_vectors(digestpp::md5(), "md5", "testvectors/md5.txt");
	test_vectors(digestpp::sha1(), "sha1", "testvectors/sha1.txt");
	test_vectors(digestpp::sha224(), "sha224", "testvectors/sha224.txt");
	test_vectors(digestpp::sha256(), "sha256", "testvectors/sha256.txt");
	test_vectors(digestpp::sha384(), "sha384", "testvectors/sha384.txt");
	test_vectors(digestpp::sha512(), "sha512", "testvectors/sha512.txt");
	test_vectors(digestpp::sha512(224), "sha512/224", "testvectors/sha512_224.txt");
	test_vectors(digestpp::sha512(256), "sha512/256", "testvectors/sha512_256.txt");
	test_vectors(digestpp::sha3(224), "sha3/224", "testvectors/sha3_224.txt");
	test_vectors(digestpp::sha3(256), "sha3/256", "testvectors/sha3_256.txt");
	test_vectors(digestpp::sha3(384), "sha3/384", "testvectors/sha3_384.txt");
	test_vectors(digestpp::sha3(512), "sha3/512", "testvectors/sha3_512.txt");
	test_vectors(digestpp::skein256(128), "skein256/128", "testvectors/skein256_128.txt");
	test_vectors(digestpp::skein256(160), "skein256/160", "testvectors/skein256_160.txt");
	test_vectors(digestpp::skein256(224), "skein256/224", "testvectors/skein256_224.txt");
	test_vectors(digestpp::skein256(256), "skein256/256", "testvectors/skein256_256.txt");
	test_vectors(digestpp::skein256(2056), "skein256/2056", "testvectors/skein256_2056.txt");
	test_vectors(digestpp::skein512(128), "skein512/128", "testvectors/skein512_128.txt");
	test_vectors(digestpp::skein512(160), "skein512/160", "testvectors/skein512_160.txt");
	test_vectors(digestpp::skein512(224), "skein512/224", "testvectors/skein512_224.txt");
	test_vectors(digestpp::skein512(256), "skein512/256", "testvectors/skein512_256.txt");
	test_vectors(digestpp::skein512(384), "skein512/384", "testvectors/skein512_384.txt");
	test_vectors(digestpp::skein512(512), "skein512/512", "testvectors/skein512_512.txt");
	test_vectors(digestpp::skein512(2056), "skein512/2056", "testvectors/skein512_2056.txt");
	test_vectors(digestpp::skein1024(256), "skein1024/256", "testvectors/skein1024_256.txt");
	test_vectors(digestpp::skein1024(384), "skein1024/384", "testvectors/skein1024_384.txt");
	test_vectors(digestpp::skein1024(512), "skein1024/512", "testvectors/skein1024_512.txt");
	test_vectors(digestpp::skein1024(1024), "skein1024/1024", "testvectors/skein1024_1024.txt");
	test_vectors(digestpp::skein1024(2056), "skein1024/2056", "testvectors/skein1024_2056.txt");
	test_vectors(digestpp::sm3(), "sm3", "testvectors/sm3.txt");
	test_vectors(digestpp::streebog(256), "streebog/256", "testvectors/streebog256.txt");
	test_vectors(digestpp::streebog(512), "streebog/512", "testvectors/streebog512.txt");
	test_vectors(digestpp::whirlpool(), "whirlpool", "testvectors/whirlpool.txt");

	// XOFs
	test_vectors(digestpp::ascon_xof128(), "ascon_xof", "testvectors/ascon_xof128.txt");
	test_vectors(digestpp::ascon_cxof128(), "ascon_cxof", "testvectors/ascon_cxof128.txt");
	test_vectors(digestpp::blake2xb_xof(), "blake2xb_xof", "testvectors/blake2xb_xof.txt");
	test_vectors(digestpp::blake2xs_xof(), "blake2xs_xof", "testvectors/blake2xs_xof.txt");
	test_vectors(digestpp::shake128(), "shake128", "testvectors/shake128.txt");
	test_vectors(digestpp::shake256(), "shake256", "testvectors/shake256.txt");
	test_vectors(digestpp::cshake256(), "cshake256", "testvectors/cshake256.txt");
	test_vectors(digestpp::k12(), "k12", "testvectors/k12.txt");
	test_vectors(digestpp::kt256(), "kt256", "testvectors/kt256.txt");
	test_vectors(digestpp::kmac128(256), "kmac128", "testvectors/kmac128.txt");
	test_vectors(digestpp::kmac256(512), "kmac256", "testvectors/kmac256.txt");
	test_vectors(digestpp::skein256_xof(), "skein256-XOF", "testvectors/skein256_xof.txt");
	test_vectors(digestpp::skein512_xof(), "skein512-XOF", "testvectors/skein512_xof.txt");

}

