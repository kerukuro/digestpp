
#include <digestpp/digestpp.hpp>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>

// Calculate SHA-256 digest of a string literal 
void example1()
{
    std::cout << digestpp::sha256().absorb("Hello World").hexdigest() << std::endl;
}

// For algorithms supporting variable output lengths (like BLAKE2, SHA512, SHA-3, etc.),
// the size can be set either at runtime (constructor argument) or at compile-time (template parameter)
void example2()
{
	size_t length = 256;
	std::cout << digestpp::blake2b(length).absorb("data").hexdigest() << std::endl;
	std::cout << digestpp::static_size::blake2b<256>().absorb("data").hexdigest() << std::endl;
}

// The .absorb() method accepts both string literals and std::string objects. Method chaining is supported
void example3()
{
	// Using std::string
	std::string str = "The quick brown fox jumps over the lazy dog";
	std::cout << digestpp::blake2b().absorb(str).hexdigest() << std::endl;

	// Using string literals and chaining
	digestpp::blake2b x;
	x.absorb("The quick brown fox ");
	x.absorb("jumps over the lazy dog");
	std::cout << x.hexdigest() << std::endl;
}

// Absorb data from standard containers (like std::vector) or raw C-arrays
void example4()
{
	// From a vector<unsigned char>
	std::vector<unsigned char> v = {0x01, 0x02, 0x03};
	std::cout << digestpp::sha512(256).absorb(v.begin(), v.end()).hexdigest() << std::endl;

	// From a raw C array
	unsigned char buf[32] = {0};
	std::cout << digestpp::sha512(256).absorb(buf, sizeof(buf)).hexdigest() << std::endl;
}

// Read and hash a file directly using std::ifstream
void example5()
{
	std::ifstream file("filename", std::ios_base::in | std::ios_base::binary);
	std::cout << digestpp::sha256().absorb(file).hexdigest() << std::endl;
}

//  Output to std::vector
void example6()
{
	std::vector<unsigned char> out;
	digestpp::sha3(256).absorb("data").digest(std::back_inserter(out));
}

//  Output to a raw buffer
void example7()
{
	unsigned char buf[32];
	digestpp::sha3(256).absorb("data").digest(buf, sizeof(buf));
}

//  Output to a stream
void example8()
{
	std::stringstream ss;
	digestpp::sha3(256).absorb("data").digest(std::ostream_iterator<char>(ss, ""));
}

// Use squeeze() to generate outputs of arbitrary length
void example9()
{
	std::vector<unsigned char> v;
	digestpp::shake256 xof;
	xof.absorb("data");
	xof.squeeze(10, std::back_inserter(v)); // Get first 10 bytes
	xof.squeeze(10, std::back_inserter(v)); // Get next 10 bytes
}

// cSHAKE-256 with customization
void example10()
{
	digestpp::cshake256 xof;
	xof.set_customization("My Custom Protocol");
	std::cout << xof.absorb("data").hexsqueeze(64) << std::endl; // Get 64 bytes as hex
}

int main()
{
	example1();
	example2();
	example3();
	example4();
	example5();
	example6();
	example7();
	example8();
	example9();
	example10();
}

