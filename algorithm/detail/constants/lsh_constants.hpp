/*
This code is written by kerukuro and released into public domain.
*/

#ifndef DIGESTPP_PROVIDERS_LSH_CONSTANTS_HPP
#define DIGESTPP_PROVIDERS_LSH_CONSTANTS_HPP

namespace digestpp
{

namespace detail
{

template<typename V>
struct lsh_constants
{
	static const uint32_t SC256[26][8];
	static const uint64_t SC512[28][8];
	static const int G256[8];
	static const int G512[8];
	static const int AB256[4];
	static const int AB512[4];
};

template<typename V>
const int lsh_constants<V>::AB256[4] = { 29, 1, 5, 17 };

template<typename V>
const int lsh_constants<V>::AB512[4] = { 23, 59, 7, 3 };

template<typename V>
const int lsh_constants<V>::G256[8] = { 0, 8, 16, 24, 24, 16, 8, 0 };

template<typename V>
const int lsh_constants<V>::G512[8] = { 0, 16, 32, 48, 8, 24, 40, 56 };

template<typename V>
const uint32_t lsh_constants<V>::SC256[26][8] = {
	{ 0x917caf90, 0x6c1b10a2, 0x6f352943, 0xcf778243, 0x2ceb7472, 0x29e96ff2, 0x8a9ba428, 0x2eeb2642 },
	{ 0x0e2c4021, 0x872bb30e, 0xa45e6cb2, 0x46f9c612, 0x185fe69e, 0x1359621b, 0x263fccb2, 0x1a116870 },
	{ 0x3a6c612f, 0xb2dec195, 0x02cb1f56, 0x40bfd858, 0x784684b6, 0x6cbb7d2e, 0x660c7ed8, 0x2b79d88a },
	{ 0xa6cd9069, 0x91a05747, 0xcdea7558, 0x00983098, 0xbecb3b2e, 0x2838ab9a, 0x728b573e, 0xa55262b5 },
	{ 0x745dfa0f, 0x31f79ed8, 0xb85fce25, 0x98c8c898, 0x8a0669ec, 0x60e445c2, 0xfde295b0, 0xf7b5185a },
	{ 0xd2580983, 0x29967709, 0x182df3dd, 0x61916130, 0x90705676, 0x452a0822, 0xe07846ad, 0xaccd7351 },
	{ 0x2a618d55, 0xc00d8032, 0x4621d0f5, 0xf2f29191, 0x00c6cd06, 0x6f322a67, 0x58bef48d, 0x7a40c4fd },
	{ 0x8beee27f, 0xcd8db2f2, 0x67f2c63b, 0xe5842383, 0xc793d306, 0xa15c91d6, 0x17b381e5, 0xbb05c277 },
	{ 0x7ad1620a, 0x5b40a5bf, 0x5ab901a2, 0x69a7a768, 0x5b66d9cd, 0xfdee6877, 0xcb3566fc, 0xc0c83a32 },
	{ 0x4c336c84, 0x9be6651a, 0x13baa3fc, 0x114f0fd1, 0xc240a728, 0xec56e074, 0x009c63c7, 0x89026cf2 },
	{ 0x7f9ff0d0, 0x824b7fb5, 0xce5ea00f, 0x605ee0e2, 0x02e7cfea, 0x43375560, 0x9d002ac7, 0x8b6f5f7b },
	{ 0x1f90c14f, 0xcdcb3537, 0x2cfeafdd, 0xbf3fc342, 0xeab7b9ec, 0x7a8cb5a3, 0x9d2af264, 0xfacedb06 },
	{ 0xb052106e, 0x99006d04, 0x2bae8d09, 0xff030601, 0xa271a6d6, 0x0742591d, 0xc81d5701, 0xc9a9e200 },
	{ 0x02627f1e, 0x996d719d, 0xda3b9634, 0x02090800, 0x14187d78, 0x499b7624, 0xe57458c9, 0x738be2c9 },
	{ 0x64e19d20, 0x06df0f36, 0x15d1cb0e, 0x0b110802, 0x2c95f58c, 0xe5119a6d, 0x59cd22ae, 0xff6eac3c },
	{ 0x467ebd84, 0xe5ee453c, 0xe79cd923, 0x1c190a0d, 0xc28b81b8, 0xf6ac0852, 0x26efd107, 0x6e1ae93b },
	{ 0xc53c41ca, 0xd4338221, 0x8475fd0a, 0x35231729, 0x4e0d3a7a, 0xa2b45b48, 0x16c0d82d, 0x890424a9 },
	{ 0x017e0c8f, 0x07b5a3f5, 0xfa73078e, 0x583a405e, 0x5b47b4c8, 0x570fa3ea, 0xd7990543, 0x8d28ce32 },
	{ 0x7f8a9b90, 0xbd5998fc, 0x6d7a9688, 0x927a9eb6, 0xa2fc7d23, 0x66b38e41, 0x709e491a, 0xb5f700bf },
	{ 0x0a262c0f, 0x16f295b9, 0xe8111ef5, 0x0d195548, 0x9f79a0c5, 0x1a41cfa7, 0x0ee7638a, 0xacf7c074 },
	{ 0x30523b19, 0x09884ecf, 0xf93014dd, 0x266e9d55, 0x191a6664, 0x5c1176c1, 0xf64aed98, 0xa4b83520 },
	{ 0x828d5449, 0x91d71dd8, 0x2944f2d6, 0x950bf27b, 0x3380ca7d, 0x6d88381d, 0x4138868e, 0x5ced55c4 },
	{ 0x0fe19dcb, 0x68f4f669, 0x6e37c8ff, 0xa0fe6e10, 0xb44b47b0, 0xf5c0558a, 0x79bf14cf, 0x4a431a20 },
	{ 0xf17f68da, 0x5deb5fd1, 0xa600c86d, 0x9f6c7eb0, 0xff92f864, 0xb615e07f, 0x38d3e448, 0x8d5d3a6a },
	{ 0x70e843cb, 0x494b312e, 0xa6c93613, 0x0beb2f4f, 0x928b5d63, 0xcbf66035, 0x0cb82c80, 0xea97a4f7 },
	{ 0x592c0f3b, 0x947c5f77, 0x6fff49b9, 0xf71a7e5a, 0x1de8c0f5, 0xc2569600, 0xc4e4ac8c, 0x823c9ce1 }
};

template<typename V>
const uint64_t lsh_constants<V>::SC512[28][8] = {
	{
		0x97884283c938982aull, 0xba1fca93533e2355ull, 0xc519a2e87aeb1c03ull, 0x9a0fc95462af17b1ull,
		0xfc3dda8ab019a82bull, 0x02825d079a895407ull, 0x79f2d0a7ee06a6f7ull, 0xd76d15eed9fdf5feull
	},
	{
		0x1fcac64d01d0c2c1ull, 0xd9ea5de69161790full, 0xdebc8b6366071fc8ull, 0xa9d91db711c6c94bull,
		0x3a18653ac9c1d427ull, 0x84df64a223dd5b09ull, 0x6cc37895f4ad9e70ull, 0x448304c8d7f3f4d5ull
	},
	{
		0xea91134ed29383e0ull, 0xc4484477f2da88e8ull, 0x9b47eec96d26e8a6ull, 0x82f6d4c8d89014f4ull,
		0x527da0048b95fb61ull, 0x644406c60138648dull, 0x303c0e8aa24c0edcull, 0xc787cda0cbe8ca19ull
	},
	{
		0x7ba46221661764caull, 0x0c8cbc6acd6371acull, 0xe336b836940f8f41ull, 0x79cb9da168a50976ull,
		0xd01da49021915cb3ull, 0xa84accc7399cf1f1ull, 0x6c4a992cee5aeb0cull, 0x4f556e6cb4b2e3e0ull
	},
	{
		0x200683877d7c2f45ull, 0x9949273830d51db8ull, 0x19eeeecaa39ed124ull, 0x45693f0a0dae7fefull,
		0xedc234b1b2ee1083ull, 0xf3179400d68ee399ull, 0xb6e3c61b4945f778ull, 0xa4c3db216796c42full
	},
	{
		0x268a0b04f9ab7465ull, 0xe2705f6905f2d651ull, 0x08ddb96e426ff53dull, 0xaea84917bc2e6f34ull,
		0xaff6e664a0fe9470ull, 0x0aab94d765727d8cull, 0x9aa9e1648f3d702eull, 0x689efc88fe5af3d3ull
	},
	{
		0xb0950ffea51fd98bull, 0x52cfc86ef8c92833ull, 0xe69727b0b2653245ull, 0x56f160d3ea9da3e2ull,
		0xa6dd4b059f93051full, 0xb6406c3cd7f00996ull, 0x448b45f3ccad9ec8ull, 0x079b8587594ec73bull
	},
	{
		0x45a50ea3c4f9653bull, 0x22983767c1f15b85ull, 0x7dbed8631797782bull, 0x485234be88418638ull,
		0x842850a5329824c5ull, 0xf6aca914c7f9a04cull, 0xcfd139c07a4c670cull, 0xa3210ce0a8160242ull
	},
	{
		0xeab3b268be5ea080ull, 0xbacf9f29b34ce0a7ull, 0x3c973b7aaf0fa3a8ull, 0x9a86f346c9c7be80ull,
		0xac78f5d7cabcea49ull, 0xa355bddcc199ed42ull, 0xa10afa3ac6b373dbull, 0xc42ded88be1844e5ull
	},
	{
		0x9e661b271cff216aull, 0x8a6ec8dd002d8861ull, 0xd3d2b629beb34be4ull, 0x217a3a1091863f1aull,
		0x256ecda287a733f5ull, 0xf9139a9e5b872fe5ull, 0xac0535017a274f7cull, 0xf21b7646d65d2aa9ull
	},
	{
		0x048142441c208c08ull, 0xf937a5dd2db5e9ebull, 0xa688dfe871ff30b7ull, 0x9bb44aa217c5593bull,
		0x943c702a2edb291aull, 0x0cae38f9e2b715deull, 0xb13a367ba176cc28ull, 0x0d91bd1d3387d49bull
	},
	{
		0x85c386603cac940cull, 0x30dd830ae39fd5e4ull, 0x2f68c85a712fe85dull, 0x4ffeecb9dd1e94d6ull,
		0xd0ac9a590a0443aeull, 0xbae732dc99ccf3eaull, 0xeb70b21d1842f4d9ull, 0x9f4eda50bb5c6fa8ull
	},
	{
		0x4949e69ce940a091ull, 0x0e608dee8375ba14ull, 0x983122cba118458cull, 0x4eeba696fbb36b25ull,
		0x7d46f3630e47f27eull, 0xa21a0f7666c0dea4ull, 0x5c22cf355b37cec4ull, 0xee292b0c17cc1847ull
	},
	{
		0x9330838629e131daull, 0x6eee7c71f92fce22ull, 0xc953ee6cb95dd224ull, 0x3a923d92af1e9073ull,
		0xc43a5671563a70fbull, 0xbc2985dd279f8346ull, 0x7ef2049093069320ull, 0x17543723e3e46035ull
	},
	{
		0xc3b409b00b130c6dull, 0x5d6aee6b28fdf090ull, 0x1d425b26172ff6edull, 0xcccfd041cdaf03adull,
		0xfe90c7c790ab6cbfull, 0xe5af6304c722ca02ull, 0x70f695239999b39eull, 0x6b8b5b07c844954cull
	},
	{
		0x77bdb9bb1e1f7a30ull, 0xc859599426ee80edull, 0x5f9d813d4726e40aull, 0x9ca0120f7cb2b179ull,
		0x8f588f583c182cbdull, 0x951267cbe9eccce7ull, 0x678bb8bd334d520eull, 0xf6e662d00cd9e1b7ull
	},
	{
		0x357774d93d99aaa7ull, 0x21b2edbb156f6eb5ull, 0xfd1ebe846e0aee69ull, 0x3cb2218c2f642b15ull,
		0xe7e7e7945444ea4cull, 0xa77a33b5d6b9b47cull, 0xf34475f0809f6075ull, 0xdd4932dce6bb99adull
	},
	{
		0xacec4e16d74451dcull, 0xd4a0a8d084de23d6ull, 0x1bdd42f278f95866ull, 0xeed3adbb938f4051ull,
		0xcfcf7be8992f3733ull, 0x21ade98c906e3123ull, 0x37ba66711fffd668ull, 0x267c0fc3a255478aull
	},
	{
		0x993a64ee1b962e88ull, 0x754979556301faaaull, 0xf920356b7251be81ull, 0xc281694f22cf923full,
		0x9f4b6481c8666b02ull, 0xcf97761cfe9f5444ull, 0xf220d7911fd63e9full, 0xa28bd365f79cd1b0ull
	},
	{
		0xd39f5309b1c4b721ull, 0xbec2ceb864fca51full, 0x1955a0ddc410407aull, 0x43eab871f261d201ull,
		0xeaafe64a2ed16da1ull, 0x670d931b9df39913ull, 0x12f868b0f614de91ull, 0x2e5f395d946e8252ull
	},
	{
		0x72f25cbb767bd8f4ull, 0x8191871d61a1c4ddull, 0x6ef67ea1d450ba93ull, 0x2ea32a645433d344ull,
		0x9a963079003f0f8bull, 0x74a0aeb9918cac7aull, 0x0b6119a70af36fa3ull, 0x8d9896f202f0d480ull
	},
	{
		0x654f1831f254cd66ull, 0x1318a47f0366a25eull, 0x65752076250b4e01ull, 0xd1cd8eb888071772ull,
		0x30c6a9793f4e9b25ull, 0x154f684b1e3926eeull, 0x6c7ac0b1fe6312aeull, 0x262f88f4f3c5550dull
	},
	{
		0xb4674a24472233cbull, 0x2bbd23826a090071ull, 0xda95969b30594f66ull, 0x9f5c47408f1e8a43ull,
		0xf77022b88de9c055ull, 0x64b7b36957601503ull, 0xe73b72b06175c11aull, 0x55b87de8b91a6233ull
	},
	{
		0x1bb16e6b6955ff7full, 0xe8e0a5ec7309719cull, 0x702c31cb89a8b640ull, 0xfba387cfada8cde2ull,
		0x6792db4677aa164cull, 0x1c6b1cc0b7751867ull, 0x22ae2311d736dc01ull, 0x0e3666a1d37c9588ull
	},
	{
		0xcd1fd9d4bf557e9aull, 0xc986925f7c7b0e84ull, 0x9c5dfd55325ef6b0ull, 0x9f2b577d5676b0ddull,
		0xfa6e21be21c062b3ull, 0x8787dd782c8d7f83ull, 0xd0d134e90e12dd23ull, 0x449d087550121d96ull
	},
	{
		0xecf9ae9414d41967ull, 0x5018f1dbf789934dull, 0xfa5b52879155a74cull, 0xca82d4d3cd278e7cull,
		0x688fdfdfe22316adull, 0x0f6555a4ba0d030aull, 0xa2061df720f000f3ull, 0xe1a57dc5622fb3daull
	},
	{
		0xe6a842a8e8ed8153ull, 0x690acdd3811ce09dull, 0x55adda18e6fcf446ull, 0x4d57a8a0f4b60b46ull,
		0xf86fbfc20539c415ull, 0x74bafa5ec7100d19ull, 0xa824151810f0f495ull, 0x8723432791e38ebbull
	},
	{
		0x8eeaeb91d66ed539ull, 0x73d8a1549dfd7e06ull, 0x0387f2ffe3f13a9bull, 0xa5004995aac15193ull,
		0x682f81c73efdda0dull, 0x2fb55925d71d268dull, 0xcc392d2901e58a3dull, 0xaa666ab975724a42ull
	}
};

} // namespace detail

} // namespace digestpp

#endif