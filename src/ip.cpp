#include "ip.hpp"

IPv4::IPv4(const std::string r) {
	uint32_t a, b, c, d;
	int res = sscanf(r.c_str(), "%u.%u.%u.%u", &a, &b, &c, &d);
	if (res != SIZE) {
		fprintf(stderr, "Ip::Ip sscanf return %d r=%s\n", res, r.c_str());
		return;
	}
	ip_ = (a << 24) bitor (b << 16) bitor (c << 8) bitor d;
}

IPv4::operator std::string() const {
	std::string str;
	std::stringstream ss;
	const int bitmask = 0x000000ff;
	int i;

	for(i = 24; i > 0; i -= 8) ss << std::dec << ((int)(ip_ >> i) bitand bitmask) << '.';
	ss << std::dec << (ip_ bitand bitmask);
	
	return ss.str();
}

#ifdef GTEST
#include <gtest/gtest.h>

TEST(Ip, ctorTest) {
	Ip ip1; // Ip()

	Ip ip2(0x7F000001); // Ip(const uint32_t r)

	Ip ip3("127.0.0.1"); // Ip(const std::string r);

	EXPECT_EQ(ip2, ip3);
}

TEST(Ip, castingTest) {
	Ip ip("127.0.0.1");

	uint32_t ui = ip; // operator uint32_t() const
	EXPECT_EQ(ui, 0x7F000001);

	std::string s = std::string(ip); // explicit operator std::string()

	EXPECT_EQ(s, "127.0.0.1");
}

#endif // GTEST
