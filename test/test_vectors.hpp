
#include <regex>
#include <iostream>
#include <fstream>
#include <digestpp/digestpp.hpp>

template<typename T>
class has_customization
{
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().set_customization(std::declval<std::string>()), std::true_type());
	template<typename>
	static std::false_type test(...);
public:
	static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
class has_personalization
{
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().set_personalization(std::declval<std::string>()), std::true_type());
	template<typename>
	static std::false_type test(...);
public:
	static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
class has_salt
{
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().set_salt(std::declval<std::string>()), std::true_type());
	template<typename>
	static std::false_type test(...);
public:
	static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

template<typename T>
class has_key
{
	template<typename U>
	static auto test(int) -> decltype(std::declval<U>().set_key(std::declval<std::string>()), std::true_type());
	template<typename>
	static std::false_type test(...);
public:
	static constexpr bool value = std::is_same<decltype(test<T>(0)), std::true_type>::value;
};

inline std::string hex2string(const std::string& hex)
{
	std::string res;
	res.resize(hex.length() / 2);
	for (size_t i = 0; i < hex.length(); i += 2)
		res[i / 2] = static_cast<char>(strtoul(hex.substr(i, 2).c_str(), nullptr, 16));
	return res;
}

inline void trim_string(std::string& str)
{
	str.erase(str.find_last_not_of("\r\n\t ") + 1);
	str.erase(0, str.find_first_not_of("\r\n\t "));
}

inline std::pair<std::string, std::string> split_vector(const std::string& str)
{
	std::pair<std::string, std::string> res;
	auto sep = str.find("=");
	if (sep == str.npos)
		return res;

	res.first = str.substr(0, sep);
	res.second = str.substr(sep + 1);
	trim_string(res.first);
	trim_string(res.second);
	return res;
}

template<typename H, template<typename> class M, typename std::enable_if<!digestpp::detail::is_xof<H>::value>::type* = nullptr>
std::string compute_vector(const std::string&, digestpp::hasher<H, M>& hasher)
{
	return hasher.hexdigest();
}

template<typename H, template<typename> class M, typename std::enable_if<digestpp::detail::is_xof<H>::value>::type* = nullptr>
std::string compute_vector(const std::string& expected, digestpp::hasher<H, M>& hasher)
{
	return hasher.hexsqueeze(expected.size() / 2);
}

template<typename H, typename std::enable_if<!has_customization<H>::value && !has_personalization<H>::value>::type* = nullptr>
void set_customization(const std::string& customization, H& hasher)
{
}

template<typename H, typename std::enable_if<has_customization<H>::value>::type* = nullptr>
void set_customization(const std::string& customization, H& hasher)
{
	hasher.set_customization(customization);
}

template<typename H, typename std::enable_if<has_personalization<H>::value>::type* = nullptr>
void set_customization(const std::string& customization, H& hasher)
{
	hasher.set_personalization(customization);
}

template<typename H, typename std::enable_if<!has_salt<H>::value>::type* = nullptr>
void set_salt(const std::string& salt, H& hasher)
{
}

template<typename H, typename std::enable_if<has_salt<H>::value>::type* = nullptr>
void set_salt(const std::string& salt, H& hasher)
{
	hasher.set_salt(salt);
}

template<typename H, typename std::enable_if<!has_key<H>::value>::type* = nullptr>
void set_key(const std::string& key, H& hasher)
{
}

template<typename H, typename std::enable_if<has_key<H>::value>::type* = nullptr>
void set_key(const std::string& key, H& hasher)
{
	hasher.set_key(key);
}

template<typename H>
void test_vectors(const H& hasher, const char* name, const char* filename)
{
	H copy(hasher);
	std::ifstream file(filename, std::ios::in);
	std::string line;
	unsigned int count = 0, failed = 0, success = 0;
	std::string::size_type msgbytes = 0;
	while (std::getline(file, line))
	{
		auto splitted = split_vector(line);
		std::string second = splitted.second;
		if (splitted.first == "Bytes")
			msgbytes = std::stol(splitted.second);
		if (splitted.first == "C")
		{
			std::string teststr = hex2string(second);
			set_customization(teststr, copy);
		}
		if (splitted.first == "Salt")
		{
			std::string teststr = hex2string(second);
			set_salt(teststr, copy);
		}
		if (splitted.first == "Key")
		{
			std::string teststr = hex2string(second);
			set_key(teststr, copy);
		}
		if (splitted.first == "Msg")
		{
			std::string teststr = hex2string(second);
			if (!msgbytes)
				copy.absorb(teststr);
			else while (msgbytes)
			{
				auto toabsorb = std::min(teststr.size(), msgbytes);
				copy.absorb(teststr.c_str(), toabsorb);
				msgbytes -= toabsorb;
			}
		}
		if (splitted.first == "MD")
		{
			std::transform(second.begin(), second.end(), second.begin(), [](unsigned char c) { return tolower(c); });
			std::string actual = compute_vector(second, copy);
			if (second != actual)
			{
				std::cerr << "\nError for test " << count << "\nExpected: " << second 
					<< "\nActual: " << actual << std::endl;
				failed++;
			}
			else success++;
			count++;
			copy.reset();
		}
	}
	std::cout << name << ": ";
	if (success)
		std::cout << success << "/" << count << " OK";
	if (failed && success)
		std::cout << ", ";
	if (failed)
		std::cout << failed << "/" << count << " FAILED";
	if (!success && !failed)
		std::cout << "No tests found. Make sure that file " << filename << " exists.";
	std::cout << std::endl;
}

