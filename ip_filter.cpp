
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "version.h"
#include "ip_filter.h"


// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(d);
	while(stop != std::string::npos)
	{
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(d, start);
	}

	r.push_back(str.substr(start));

	return r;
}


std::vector<ip_t> iplist_read(std::istream &is)
{
	std::vector<ip_t> bv;
	for(std::string line; std::getline(is, line);)
	{
		std::vector<std::string> v = split(line, '\t');
		v = std::move(split(v.at(0), '.'));

		// unsigned int id;
		unsigned char b0, b1, b2, b3;

		b3 = stoi(v.at(0));
		b2 = stoi(v.at(1));
		b1 = stoi(v.at(2));
		b0 = stoi(v.at(3));
		// id = (b0 & 0xff) | ((b1 & 0xff) << 8)
		// 		| ((b2 & 0xff) << 16) | ((b3 & 0xff) << 24);

		bv.push_back(ip_t {b3, b2, b1, b0});
	}
	return bv;
}	


std::vector<ip_t> iplist_basesort(std::vector<ip_t> &v)
{
	std::sort(std::begin(v), std::end(v));
	std::reverse(std::begin(v), std::end(v));
	return v;
}



std::ostream& std::operator <<(std::ostream& os, const ip_t &ip)
{
	os << static_cast<int>(ip.at(0))
		<< "."
		<< static_cast<int>(ip.at(1))
		<< "."
		<< static_cast<int>(ip.at(2))
		<< "."
		<< static_cast<int>(ip.at(3));

	return os;
}


