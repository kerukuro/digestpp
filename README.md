# digestpp
Experimental C++11 header-only message digest library.

Derived from cppcrypto, this library aims to provide a more modern, flexible, and versatile C++ API for cryptographic hash functions.

Tested with g++ 6.4.0, clang 4.0.1 and Visual C++ 2017.

## Quick Start / Installation
Just copy the `digestpp` folder to your project or include path and `#include <digestpp/digestpp.hpp>`.

## Examples
### Quick Start
Calculate SHA-256 digest of a string literal:
````cpp
#include <digestpp/digestpp.hpp>
#include <iostream>

int main() {
    std::cout << digestpp::sha256().absorb("Hello World").hexdigest() << std::endl;
    return 0;
}
````
### Specifying Output Size (Runtime vs Compile-time)
For algorithms supporting variable output lengths (like BLAKE2, SHA512, SHA-3, etc.), the size can be set either at runtime (constructor argument) or at compile-time (template parameter).

**Runtime size** (more flexible, allows values determined at runtime):
````cpp
size_t length = 256;
std::cout << digestpp::blake2b(length).absorb("data").hexdigest() << std::endl;
````
**Compile-time** size (static checking):
````cpp
std::cout << digestpp::static_size::blake2b<256>().absorb("data").hexdigest() << std::endl;
````
### Working with Strings
The .absorb() method accepts both string literals and `std::string` objects. Method chaining is supported:
````cpp
// Using std::string
std::string str = "The quick brown fox jumps over the lazy dog";
std::cout << digestpp::blake2b().absorb(str).hexdigest() << std::endl;

// Using string literals and chaining
digestpp::blake2b x;
x.absorb("The quick brown fox ");
x.absorb("jumps over the lazy dog");
std::cout << x.hexdigest() << std::endl;
````
### Hashing Binary Data
Absorb data from standard containers (like `std::vector`) or raw C-arrays:
````cpp
// From a vector<unsigned char>
std::vector<unsigned char> v = {0x01, 0x02, 0x03};
std::cout << digestpp::sha512(256).absorb(v.begin(), v.end()).hexdigest() << std::endl;

// From a raw C array
unsigned char buf[32] = {0};
std::cout << digestpp::sha512(256).absorb(buf, sizeof(buf)).hexdigest() << std::endl;
````
### Hashing Files
Read and hash a file directly using `std::ifstream`:
````cpp
std::ifstream file("filename", std::ios_base::in | std::ios_base::binary);
std::cout << digestpp::sha256().absorb(file).hexdigest() << std::endl;
````
### Output Options
Retrieve the result as a hex string, raw bytes, or write directly to a stream.
#### Output to std::vector:
````cpp
std::vector<unsigned char> out;
digestpp::sha3(256).absorb("data").digest(std::back_inserter(out));
````
#### Output to a raw buffer:
````cpp
unsigned char buf[32];
digestpp::sha3(256).absorb("data").digest(buf, sizeof(buf));
````
#### Output to a stream:
````cpp
std::stringstream ss;
digestpp::sha3(256).absorb("data").digest(std::ostream_iterator<char>(ss, ""));
````
### Extendable Output Functions (XOF)
Use squeeze() to generate outputs of arbitrary length.
#### SHAKE-256:
````cpp
std::vector<unsigned char> v;
digestpp::shake256 xof;
xof.absorb("data");
xof.squeeze(10, std::back_inserter(v)); // Get first 10 bytes
xof.squeeze(10, std::back_inserter(v)); // Get next 10 bytes
````
#### cSHAKE-256 with customization:
````cpp
digestpp::cshake256 xof;
xof.set_customization("My Custom Protocol");
std::cout << xof.absorb("data").hexsqueeze(64) << std::endl; // Get 64 bytes as hex
````

## Hasher class

Hasher is the main class template implementing the public API for hashing.

It has two template parameters:
- HashProvider is a class implementing the algorithm via the traditional init/update/final interface. We provide our own implementations of hash functions listed in the next section, but using the traditional interface allows anyone to trivially implement the providers as wrappers around popular libraries, such as OpenSSL, Crypto++, or Botan.
- Mixin is a class template which can be used to inject additional functions into the public API of the hasher, for example for setting the customization string for cSHAKE, the salt for BLAKE, etc.

````cpp
template<class HashProvider, template <class> class Mixin = detail::null_mixin>
class hasher : public Mixin<HashProvider>
{
public:
    // Default constructor
    // Used for hash functions with fixed output size, for hash functions with sensible
    // default output size, and for extendable output functions (XOFs).
    template<typename H=HashProvider,
        typename std::enable_if<std::is_default_constructible<H>::value>::type* = nullptr>
    hasher();

    // Constructor with hashsize parameter
    // Used with hash functions which can produce hashes of different lengths with length specified at runtime.
    // If the requested output size is not supported by the algorithm, std::runtime_error will be thrown.
    template<typename H=HashProvider, typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
    hasher(size_t hashsize);

    // Absorbs bytes from a C-style pointer to a character buffer
    template<typename T, typename std::enable_if<detail::is_byte<T>::value>::type* = nullptr>
    inline hasher& absorb(const T* data, size_t len);

    // Absorbs bytes from std::basic_string
    template<typename T,
        typename std::enable_if<detail::is_byte<T>::value
            && !std::is_same<T, std::string::value_type>::value>::type* = nullptr>
    inline hasher& absorb(const std::basic_string<T>& str);

    // Absorbs bytes from std::string
    inline hasher& absorb(const std::string& str);

    // Absorbs bytes from std::istream
    template<typename T, typename std::enable_if<detail::is_byte<T>::value>::type* = nullptr>;
    inline hasher& absorb(std::basic_istream<T>& istr);

    // Absorbs bytes from an iterator sequence
    template<typename IT>
    inline hasher& absorb(IT begin, IT end);

    // In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data
    // into a user-provided preallocated buffer.
    template<typename T, typename H=HashProvider,
        typename std::enable_if<detail::is_byte<T>::value && detail::is_xof<H>::value>::type* = nullptr>
    inline void squeeze(T* buf, size_t len);

    // In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data
    // and write them to the output iterator.
    template<typename OI, typename H=HashProvider,
        typename std::enable_if<detail::is_xof<H>::value>::type* = nullptr>
    inline void squeeze(size_t len, OI it);

    // In case HashProvider is an extendable output function, squeeze <len> bytes from absorbed data
    // and return them as a hex string.
    template<typename H=HashProvider, typename std::enable_if<detail::is_xof<H>::value>::type* = nullptr>
    inline std::string hexsqueeze(size_t len);

    // In case HashProvider is a hash function, output binary digest to a user-provided preallocated buffer.
    template<typename T, typename H=HashProvider,
        typename std::enable_if<detail::is_byte<T>::value && !detail::is_xof<H>::value>::type* = nullptr>
    inline void digest(T* buf, size_t len) const;

    // In case HashProvider is a hash function, generate binary digest from absorbed data
    // and write it to an output iterator.
    template<typename OI, typename H=HashProvider,
        typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
    inline void digest(OI it) const;

    // In case HashProvider is a hash function, return hex digest of absorbed data.
    template<typename H=HashProvider, typename std::enable_if<!detail::is_xof<H>::value>::type* = nullptr>
    inline std::string hexdigest() const;

    // Resets the state to start new digest computation.
    // If resetParameters is true, all customization parameters such as salt will also be cleared.
    inline void reset(bool resetParameters = false);
};
````

Individual hash algorithms are defined by typedefs, e.g.
````cpp
    typedef hasher<detail::sha3_provider> sha3;

    typedef hasher<detail::blake_provider, detail::blake_mixin> blake;

    // ...
````

## Supported algorithms

### Hash functions

Typedef|Description|Security|Supported output sizes|Optional parameters
-------|-----------|--------|----------------------|-------------------
ascon_hash|Ascon (NIST SP 800-232)|✅Secure|256|-
blake|Original BLAKE algorithm|✅Secure|224, 256, 384, 512|salt
blake2b|BLAKE2b|✅Secure|8-512|salt, personalization, key
blake2s|BLAKE2s|✅Secure|8-256|salt, personalization, key
blake2bp|BLAKE2bp|✅Secure|8-512|salt, personalization, key
blake2sp|BLAKE2sp|✅Secure|8-256|salt, personalization, key
blake2xb|BLAKE2xb|✅Secure|arbitrary|salt, personalization, key
blake2xs|BLAKE2xs|✅Secure|arbitrary|salt, personalization, key
echo|Echo|✅Secure|8-512|salt
esch|Esch|✅Secure|256, 384|-
groestl|Grøstl|✅Secure|8-512|-
jh|JH|✅Secure|8-512|-
kmac128|KMAC128|✅Secure|arbitrary|key, customization
kmac256|KMAC256|✅Secure|arbitrary|key, customization
kupyna|Kupyna|✅Secure|256, 512|-
lsh256|LSH-256|✅Secure|8-256|-
lsh512|LSH-512|✅Secure|8-512|-
md5|MD5|❌Broken|128|-
sha1|SHA-1|❌Broken|160|-
sha224|SHA-224|✅Secure|224|-
sha256|SHA-256|✅Secure|256|-
sha384|SHA-384|✅Secure|384|-
sha512|SHA-512|✅Secure|8-512|-
sha3|SHA-3|✅Secure|224, 256, 384, 512|-
skein256|Skein256|✅Secure|arbitrary|personalization, key, nonce
skein512|Skein512|✅Secure|arbitrary|personalization, key, nonce
skein1024|Skein1024|✅Secure|arbitrary|personalization, key, nonce
sm3|SM3|✅Secure|256|-
streebog|Streebog|⚠️Backdoored|256, 512|-
whirlpool|Whirlpool|✅Secure|512|-

### Extendable output functions

Typedef|Description|Security|Optional parameters
-------|-----------|-|------------------
ascon_xof|Ascon-XOF128|✅Secure|-
ascon_cxof|Ascon-CXOF128|✅Secure|customization
blake2xb_xof|BLAKE2xb in XOF mode|✅Secure|salt, personalization, key
blake2xs_xof|BLAKE2xs in XOF mode|✅Secure|salt, personalization, key
esch256_xof|XOEsch256|✅Secure|-
esch384_xof|XOEsch384|✅Secure|-
k12|KangarooTwelve|✅Secure|customization
kt128|KangarooTwelve (alias for k12)|✅Secure|customization
kt256|256bit KangarooTwelve|✅Secure|customization
m14|MarsupilamiFourteen|✅Secure|customization
shake128|SHAKE-128|✅Secure|-
shake256|SHAKE-256|✅Secure|-
cshake128|cSHAKE-128|✅Secure|function name, customization
cshake256|cSHAKE-256|✅Secure|function name, customization
kmac128_xof|KMAC128 in XOF mode|✅Secure|key, customization
kmac256_xof|KMAC256 in XOF mode|✅Secure|key, customization
skein256_xof|Skein256 in XOF mode|✅Secure|personalization, key, nonce
skein512_xof|Skein512 in XOF mode|✅Secure|personalization, key, nonce
skein1024_xof|Skein1024 in XOF mode|✅Secure|personalization, key, nonce

## Design rationale in questions and answers

Q: What is the difference between a hash function with variable output size and an extendable output function (XOF)?

A: Hash functions require the digest size to be known at the moment of initialization and normally produce unrelated outputs for different digest sizes. For example, `blake2b(256)` and `blake2b(512)` produce completely different digests. XOFs are functions that do not need to know the output size in advance and can produce outputs of arbitrary length. Bytes generated by XOFs depend only on the input data, not on the digest size. It is generally recommended to use hash functions instead of XOFs when the output size is known in advance.


Q: What is the difference between `digest()` and `squeeze()`?

A. `digest()` is used with hash functions; it retrieves a digest of a certain length (defined by the algorithm or specified in the constructor). Calling `digest()` or `hexdigest()` does not change the internal state, so these functions can be called more than once and will produce the same output. `squeeze()` is used with XOF functions; it can be called multiple times to squeeze an arbitrary number of output bytes. After each invocation of `squeeze()`, the internal state changes so that the next call to `squeeze()` will generate different (additional) output bytes.


Q: For hash functions with variable output size, why do you provide two options: with output size as a template parameter, e.g. `digestpp::static_size::sha3<256>()`, and with output size specified at runtime, e.g. `digestpp::sha3(256)`?

A: In some usage scenarios, the required digest size is not known at compile time. One simple example is the Argon2 password hashing algorithm, which requires us to hash its state using BLAKE2b with a dynamically calculated digest size. We can't just use the largest digest size and truncate the result because most hash functions (unlike XOFs) produce completely different digests depending on the requested output size.


Q: Why does `hasher` not support hashing non-byte types?

A: Cryptographic hash functions are always defined for a sequence of bytes. We support only those data types that can be unambiguously converted to bytes (sequences of `char`, `signed char`, or `unsigned char`). Other data types should be converted to a sequence of bytes in a non-ambiguous way before they can be hashed (e.g., wide strings could be encoded using UTF-8 or another encoding), which is beyond the scope of the library.


Q: Since the output size has to be provided to the constructor, why are there separate typedefs for `sha256` and `sha512` instead of one hasher with an output size parameter: `sha2(256)` / `sha2(512)`?

A: The SHA-2 family of hash functions is special because SHA-512 can produce an output of any size up to 512 bits (SHA-512/t); e.g., `sha512(256)` will calculate SHA-512/256. The resulting hash is different from SHA-256 but has the same length. Thus SHA-512 is an independent hash function supporting variable output sizes. On the other hand, the 32-bit version of SHA-2 is only defined for 224-bit and 256-bit outputs, and they are widely known as SHA-224 and SHA-256. We decided to use different typedefs for SHA-224 and SHA-256 because requiring users to use `sha256(224)` for getting SHA-224 digests would be confusing. Internally all SHA-2 functions are implemented using one template class.


Q: Why are there separate typedefs for `skein256`, `skein512` and `skein1024` instead of one hasher with an output size parameter: `skein(256)` / `skein(512)` / `skein(1024)`?

A: Skein256, Skein512, and Skein1024 are different algorithms. Each of them can produce digests of any size. The outputs are unrelated, e.g., `skein256(256)` != `skein512(256)` != `skein1024(256)`. Internally all Skein variants are implemented using one template class.


Q: Why are there so many typedefs for the BLAKE2 hash function?

A: BLAKE2 has many variants that produce incompatible digests for the same output sizes. We support different variants via different typedefs. For the 512-bit version, `blake2b` is the oldest algorithm, which can produce digests of any size up to 512 bits. `blake2xb` can be used to produce larger digests but requires the output size to be known in advance; it can't be merged with `blake2b` because their outputs are different for the same digest sizes. `blake2xb_xof` can be used in XOF mode when the output size is not known in advance. Then there is a 256-bit version `blake2s` which supports all these variants as well. Internally all BLAKE2 variants are implemented using one template class.

## Known limitations

* Included providers are written in standard C++ and may be slower than SIMD optimized implementations.
* Only complete bytes are supported for input and output.
* Big endian systems are not supported.
* No attempts were made to make the implementation of every algorithm constant time.

## Thread Safety

The library follows standard C++ thread safety guarantees:

*   **Distinct objects:** It is safe to use distinct `hasher` instances from multiple threads simultaneously. No global mutable state is shared between instances.
*   **Shared objects:** It is **not** safe to modify a single `hasher` instance from multiple threads concurrently. Methods that modify the internal state (such as `absorb`, `squeeze`, `reset`) require external synchronization (e.g., using `std::mutex`) if called from different threads on the same object.
*   **Const methods:** It is safe to call `const` methods (such as `digest`, `hexdigest`) from multiple threads, provided the object is not being modified by another thread at the same time.

## Reference documentation

Reference documentation is here: https://kerukuro.github.io/digestpp/



