
#include "../digestpp.hpp"
#include <iostream>

bool compare(const std::string& name, const std::string& actual, const std::string& expected)
{
	if (actual != expected)
	{
		std::cerr << name << " error: expected " << expected << ", actual " << actual << std::endl;
		return false;
	}
	return true;
}

void basic_self_test()
{
	std::string ts = "The quick brown fox jumps over the lazy dog";

	int errors = 0;

	errors += !compare("BLAKE/256", digestpp::blake(256).absorb(ts).hexdigest(), 
		"7576698ee9cad30173080678e5965916adbb11cb5245d386bf1ffda1cb26c9d7");

	errors += !compare("BLAKE2S/256", digestpp::blake2s(256).absorb(ts).hexdigest(), 
		"606beeec743ccbeff6cbcdf5d5302aa855c256c29b88c8ed331ea1a6bf3c8812");

	errors += !compare("BLAKE2B/256", digestpp::blake2b(256).absorb(ts).hexdigest(), 
		"01718cec35cd3d796dd00020e0bfecb473ad23457d063b75eff29c0ffa2e58a9");

	errors += !compare("Groestl/256", digestpp::groestl(256).absorb(ts).hexdigest(), 
		"8c7ad62eb26a21297bc39c2d7293b4bd4d3399fa8afab29e970471739e28b301");

	errors += !compare("JH/256", digestpp::jh(256).absorb(ts).hexdigest(), 
		"6a049fed5fc6874acfdc4a08b568a4f8cbac27de933496f031015b38961608a0");

	errors += !compare("Kupyna/256", digestpp::kupyna(256).absorb(ts).hexdigest(), 
		"996899f2d7422ceaf552475036b2dc120607eff538abf2b8dff471a98a4740c6");

	errors += !compare("SHA-256", digestpp::sha256().absorb(ts).hexdigest(), 
		"d7a8fbb307d7809469ca9abcb0082e4f8d5651e46d3cdb762d02d0bf37c9e592");

	errors += !compare("SHA-512/256", digestpp::sha512(256).absorb(ts).hexdigest(), 
		"dd9d67b371519c339ed8dbd25af90e976a1eeefd4ad3d889005e532fc5bef04d");

	errors += !compare("SHA-3/256", digestpp::sha3(256).absorb(ts).hexdigest(), 
		"69070dda01975c8c120c3aada1b282394e7f032fa9cf32f4cb2259a0897dfc04");

	errors += !compare("SHAKE128/256", digestpp::shake128().absorb(ts).hexsqueeze(32), 
		"f4202e3c5852f9182a0430fd8144f0a74b95e7417ecae17db0f8cfeed0e3e66e");

	errors += !compare("Streebog/256", digestpp::streebog(256).absorb(ts).hexdigest(), 
		"3e7dea7f2384b6c5a3d0e24aaa29c05e89ddd762145030ec22c71a6db8b2c1f4");

	errors += !compare("SM3", digestpp::sm3().absorb(ts).hexdigest(), 
		"5fdfe814b8573ca021983970fc79b2218c9570369b4859684e2e4c3fc76cb8ea");

	errors += !compare("BLAKE2B/512", digestpp::blake2b(512).absorb(ts).hexdigest(), 
		"a8add4bdddfd93e4877d2746e62817b116364a1fa7bc148d95090bc7333b3673"
		"f82401cf7aa2e4cb1ecd90296e3f14cb5413f8ed77be73045b13914cdcd6a918");

	errors += !compare("Groestl/512", digestpp::groestl(512).absorb(ts).hexdigest(),
		"badc1f70ccd69e0cf3760c3f93884289da84ec13c70b3d12a53a7a8a4a513f99"
		"715d46288f55e1dbf926e6d084a0538e4eebfc91cf2b21452921ccde9131718d");

	errors += !compare("JH/512", digestpp::jh(512).absorb(ts).hexdigest(), 
		"043f14e7c0775e7b1ef5ad657b1e858250b21e2e61fd699783f8634cb86f3ff9"
		"38451cabd0c8cdae91d4f659d3f9f6f654f1bfedca117ffba735c15fedda47a3");

	errors += !compare("Kupyna/512", digestpp::kupyna(512).absorb(ts).hexdigest(), 
		"d1b469f43e0963735b6cd08a6e75fc370956d8afa9653b5231614decb1cceb81"
		"62ae5b8ff2dc3b02417f86dc4df621d0ca5b1ff399d494766c93a6d2513cae3a");

	errors += !compare("SHA-512", digestpp::sha512().absorb(ts).hexdigest(), 
		"07e547d9586f6a73f73fbac0435ed76951218fb7d0c8d788a309d785436bbb64"
		"2e93a252a954f23912547d1e8a3b5ed6e1bfd7097821233fa0538f3db854fee6");

	errors += !compare("SHA3/512", digestpp::sha3(512).absorb(ts).hexdigest(),
		"01dedd5de4ef14642445ba5f5b97c15e47b9ad931326e4b0727cd94cefc44fff"
		"23f07bf543139939b49128caf436dc1bdee54fcb24023a08d9403f9b4bf0d450");

	errors += !compare("SHAKE256/512", digestpp::shake256().absorb(ts).hexsqueeze(64),
		"2f671343d9b2e1604dc9dcf0753e5fe15c7c64a0d283cbbf722d411a0e36f6ca"
		"1d01d1369a23539cd80f7c054b6e5daf9c962cad5b8ed5bd11998b40d5734442");

	errors += !compare("Skein256/512", digestpp::skein256(512).absorb(ts).hexdigest(),
		"f8138e72cdd9e11cf09e4be198c234acb0d21a9f75f936e989cf532f1fa9f4fb"
		"21d255811f0f1592fb3617d04704add875ae7bd16ddbbeaed4eca6eb9675d2c6");

	errors += !compare("Skein256-XOF/512", digestpp::skein256_xof().absorb(ts).hexsqueeze(64),
		"217021fbabe331c5753024fe4c17a005a698b037859ca8f4f0fb9112dce5605c"
		"7c9c11b7bdaaeaf7e778488042772ac34c51a7c44c9d3471bb515a506312ded9");

	errors += !compare("Skein512/512", digestpp::skein512(512).absorb(ts).hexdigest(),
		"94c2ae036dba8783d0b3f7d6cc111ff810702f5c77707999be7e1c9486ff238a"
		"7044de734293147359b4ac7e1d09cd247c351d69826b78dcddd951f0ef912713");

	errors += !compare("Skein512/512-personalized", digestpp::skein512(256).set_personalization("Skein").absorb(ts).hexdigest(),
		"89440a0472257aa5a90afe6e9599525dd9d5d2178b287b859b3814fff735f284");

	errors += !compare("Skein512/512-nonce", 
			digestpp::skein512(256).set_personalization("Skein").set_nonce("ABCD").absorb(ts).hexdigest(),
		"d08265088e1c46f6c0a7c295747b21e5c4a7750bee699918db5ac999002a28e4");

	errors += !compare("Skein512/512-params", 
			digestpp::skein512(256).set_personalization("Skein").set_nonce("ABCD").set_key("Key").absorb(ts).hexdigest(),
		"e509a1c002625e84e0edae9c213732b4c57604f06ed78c99248cef05707ecaa5");

	errors += !compare("Skein1024/512", digestpp::skein1024(512).absorb(ts).hexdigest(), 
		"a40ba71fa36a8c1d152bfc68b79782ef206d2e74b9a072b11aa874e6ec2148d9"
		"37e9acd4ca1026ad636fed1a88b740112d782e2ca0e6c3bbe0dd2704a60a10a5");

	errors += !compare("Streebog/512", digestpp::streebog(512).absorb(ts).hexdigest(), 
		"d2b793a0bb6cb5904828b5b6dcfb443bb8f33efc06ad09368878ae4cdc8245b9"
		"7e60802469bed1e7c21a64ff0b179a6a1e0bb74d92965450a0adab69162c00fe");

	errors += !compare("Whirlpool", digestpp::whirlpool().absorb(ts).hexdigest(), 
		"b97de512e91e3828b40d2b0fdce9ceb3c4a71f9bea8d88e75c4fa854df36725f"
		"d2b52eb6544edcacd6f8beddfea403cb55ae31f03ad62a5ef54e42ee82c3fb35");

	errors += !compare("K12/512", digestpp::k12().absorb(ts).hexsqueeze(64), 
		"b4f249b4f77c58df170aa4d1723db1127d82f1d98d25ddda561ada459cd11a48"
		"9242e112dbfb1f99a1de1d7e830d457778a66d1dc2aa44d61a1da91655122fb7");

	errors += !compare("M14/512", digestpp::m14().absorb(ts).hexsqueeze(64), 
		"3611bcaa666347770dbffd4562f137c5adfe2e09f3c4268ef7c7d7c0e6c5d59c"
		"21fa67c4cfdba29e449c944b1a16c4583f2be8a75fb4f7649df6b98698708ecf");

	errors += !compare("BLAKE2XS/512", digestpp::blake2xs(512).absorb(ts).hexdigest(), 
		"e709f8377d21507c166e5dd2279a1f58b290792d65dafcc5647b6e439a974227"
		"503c341341572725709b874e95f13a438677aa6f9648467fd341e0f3e5421840");

	errors += !compare("BLAKE2XS-XOF/512", digestpp::blake2xs_xof().absorb(ts).hexsqueeze(64), 
		"4e13634574b153019520d7e22a84bebc2b344e853df9420d6819dbcb26a6610e"
		"bca3e71aba24f60b0444dbbd6f1bb526a43b87c5e6ac057870d43f8ae1c4890d");

	errors += !compare("BLAKE2XB/512", digestpp::blake2xb().absorb(ts).hexdigest(), 
		"6136549d6849d7386e42a1b7c034a1ddd6527e055a8425db4f3ae3c044aa306d"
		"59c0bc428787d1539c5d13c703bfef01004e22277a84f5b0b093bed8268536b7");

	errors += !compare("BLAKE2XB-XOF/512", digestpp::blake2xb_xof().absorb(ts).hexsqueeze(64), 
		"a4cae634be0d4011ed04d3b8ca60a3616147a201603505c0dd5ade86a50e8964"
		"3f4e03d0aeb3781408b12700fb407080bf907d88bdef47dda63ceefa8b9cc5c6");

	std::cout << "Self-test completed with " << errors << " errors." << std::endl;
}

int main()
{
	basic_self_test();
}


