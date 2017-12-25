#include <rsa.hpp>
#include <catch.hpp>

SCENARIO("check every uniCODE")
{
	std::vector<long> char_codes;
	for (unsigned int i = 0; i < 15000; ++i)
	{
		char_codes.push_back(i);
	}
	
	Rsa rsa;
	Key keys = rsa.getKeys();

	std::vector<long> crypted_codes;
	for (unsigned int i = 0; i < char_codes.size(); ++i)
	{
		crypted_codes.push_back(rsa.endecrypt(char_codes.at(i),keys.exp,keys.pub));
	}
	
	for (auto &it: crypted_codes)
	{
		it = rsa.endecrypt(it,keys.dkey,keys.pub);
	}
	
	bool check = false;
	if (char_codes == crypted_codes)
	{
		check = true;
	}
	
	REQUIRE (check == true);
}