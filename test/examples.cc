
#include <digestpp/digestpp.hpp>
#include <numeric>
#include <iostream>
#include <iomanip>
#include <fstream>

using namespace std;
using namespace digestpp;


// Calculate BLAKE2b digest from a double quoted string and output it in hex format
void example1()
{
	cout << blake2b().absorb("The quick brown fox jumps over the lazy dog").hexdigest() << endl;
}

// Calculate BLAKE2b-256 digest from an std::string and output it in hex format
void example2()
{
	string str = "The quick brown fox jumps over the lazy dog";
	cout << blake2b(256).absorb(str).hexdigest() << endl;
}

// Calculate SHA-512 digest of a vector and output it in hex format
void example3()
{
	vector<unsigned char> v(100);
	iota(v.begin(), v.end(), 0);

	cout << sha512().absorb(v.begin(), v.end()).hexdigest() << endl;
}

// Calculate SHA-512/256 digest of a C array and output it in hex format
void example4()
{
	unsigned char c[32];
	iota(c, c + sizeof(c), 0);

	cout << sha512(256).absorb(c, sizeof(c)).hexdigest() << endl;
}

// Calculate SHA-256 digest of a file and output it in hex format
void example5()
{
	ifstream file("filename", ios_base::in|ios_base::binary);
	cout << sha256().absorb(file).hexdigest() << endl;
}

// Generate SHA3-224 digest using multiple calls to absorb()
void example6()
{
	cout << sha3(224).absorb("The quick brown fox ").absorb("jumps over the lazy dog").hexdigest() << endl;
}

// Output binary digest to a vector
void example7()
{
	vector<unsigned char> v;
	sha3(256).absorb("The quick brown fox jumps over the lazy dog").digest(back_inserter(v));
}

// Output binary digest to a raw C array
void example8()
{
	unsigned char buf[32];
	sha3(256).absorb("The quick brown fox jumps over the lazy dog").digest(buf, sizeof(buf));
}

// Output binary digest to a stream
void example9()
{
	string str = "The quick brown fox jumps over the lazy dog";
	string output;
	ostringstream os(output);
	sha3(256).absorb(str).digest(ostream_iterator<char>(os, ""));
}

// Generate long output using SHAKE-256 extendable output function using multiple calls to squeeze()
void example10()
{
	vector<unsigned char> v;
	shake256 xof;
	xof.absorb("The quick brown fox jumps over the lazy dog");
	xof.squeeze(1000, back_inserter(v));
	xof.squeeze(1000, back_inserter(v));
	xof.squeeze(1000, back_inserter(v));
	cout << "Squeezed " << v.size() << " bytes." << endl;
}

// Generate 64-byte digest using customizable cSHAKE-256 algorithm and print it in hex format
void example11()
{
	cshake256 xof;
	xof.set_customization("Customization");
	cout << xof.absorb("The quick brown fox jumps over the lazy dog").hexsqueeze(64) << endl;
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
