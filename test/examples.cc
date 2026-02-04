
#include <digestpp/digestpp.hpp>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>

// Calculate BLAKE2b digest from a double quoted string and output it in hex format
void example1()
{
	std::cout << digestpp::blake2b().absorb("The quick brown fox jumps over the lazy dog").hexdigest();
}

// Calculate BLAKE2b-256 digest from an std::string and output it in hex format
void example2()
{
	std::string str = "The quick brown fox jumps over the lazy dog";
	// with digest length specified at runtime
	std::cout << digestpp::blake2b(256).absorb(str).hexdigest();
	// OR with digest length specified at compile-time
	std::cout << digestpp::static_length::blake2b<256>().absorb(str).hexdigest();
}

// Calculate SHA-512 digest of a vector and output it in hex format
void example3()
{
	std::vector<unsigned char> v;
	// ...fill the vector
	std::cout << digestpp::sha512().absorb(v.begin(), v.end()).hexdigest();
}

// Calculate SHA-512/256 digest of a C array and output it in hex format
void example4()
{
	unsigned char c[32];
	// ...fill the array
	// with digest length specified at runtime
	std::cout << digestpp::sha512(256).absorb(c, sizeof(c)).hexdigest();
	// OR with digest length specified at compile-time
	std::cout << digestpp::static_length::sha512<256>().absorb(c, sizeof(c)).hexdigest();
}

// Calculate SHA-256 digest of a file and output it in hex format
void example5()
{
	std::ifstream file("filename", std::ios_base::in|std::ios_base::binary);
	std::cout << digestpp::sha256().absorb(file).hexdigest();
}

// Generate SHA3-224 digest using multiple calls to absorb()
void example6()
{
	// with digest length specified at runtime
	std::cout << digestpp::sha3(224).absorb("The quick brown fox ").absorb("jumps over the lazy dog").hexdigest();
	// OR with digest length specified at compile-time
	std::cout << digestpp::static_length::sha3<224>().absorb("The quick brown fox ").absorb("jumps over the lazy dog").hexdigest();
}

// Output binary digest to a vector
void example7()
{
	std::vector<unsigned char> v;
	// with digest length specified at runtime
	digestpp::sha3(256).absorb("The quick brown fox jumps over the lazy dog").digest(std::back_inserter(v));
	// OR with digest length specified at compile-time
	digestpp::static_length::sha3<256>().absorb("The quick brown fox jumps over the lazy dog").digest(std::back_inserter(v));
}

// Output binary digest to a raw C array
void example8()
{
	unsigned char buf[32];
	// with digest length specified at runtime
	digestpp::sha3(256).absorb("The quick brown fox jumps over the lazy dog").digest(buf, sizeof(buf));
	// OR with digest length specified at compile-time
	digestpp::static_length::sha3<256>().absorb("The quick brown fox jumps over the lazy dog").digest(buf, sizeof(buf));
}

// Output binary digest to a stream
void example9()
{
	std::string str = "The quick brown fox jumps over the lazy dog";
	std::string output;
	std::ostringstream os(output);
	// with digest length specified at runtime
	digestpp::sha3(256).absorb(str).digest(std::ostream_iterator<char>(os, ""));
	// OR with digest length specified at compile-time
	digestpp::static_length::sha3<256>().absorb(str).digest(std::ostream_iterator<char>(os, ""));
}

// Generate long output using SHAKE-256 extendable output function using multiple calls to squeeze()
void example10()
{
	std::vector<unsigned char> v;
	digestpp::shake256 xof;
	xof.absorb("The quick brown fox jumps over the lazy dog");
	xof.squeeze(1000, std::back_inserter(v));
	xof.squeeze(1000, std::back_inserter(v));
	xof.squeeze(1000, std::back_inserter(v));
	std::cout << "Squeezed " << v.size() << " bytes." << std::endl;
}

// Generate 64-byte digest using customizable cSHAKE-256 algorithm and print it in hex format
void example11()
{
	digestpp::cshake256 xof;
	xof.set_customization("Customization");
	std::cout << xof.absorb("The quick brown fox jumps over the lazy dog").hexsqueeze(64);
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
	example11();
}
