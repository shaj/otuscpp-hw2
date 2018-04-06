
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


void iplist_read(std::istream &is, std::vector<ip_t> &bv)
{
	for(std::string line; std::getline(is, line);)
	{
		std::vector<std::string> v = split(line, '\t');
		v = split(v.at(0), '.');

//            unsigned int id;
		unsigned char b0, b1, b2, b3;

		b3 = stoi(v.at(0));
		b2 = stoi(v.at(1));
		b1 = stoi(v.at(2));
		b0 = stoi(v.at(3));
//            id = (b0 & 0xff) | ((b1 & 0xff) << 8)
//                | ((b2 & 0xff) << 16) | ((b3 & 0xff) << 24);

		bv.push_back(ip_t {b3, b2, b1, b0});
	}
}	


void iplist_basesort(std::vector<ip_t> &v)
{
	// TODO reverse lexicographically sort
	// std::sort(v.begin(), v.end(), std::greater<decltype(v)::value_type>());
	std::sort(v.begin(), v.end());
	std::reverse(v.begin(), v.end());
}


void iplist_print(std::ostream &os, std::vector<ip_t> &v)
{
	for(auto it: v)
	{
		os << int(it[0]) << "." << int(it[1]) << "." << int(it[2]) << "." << int(it[3]);
		os << std::endl;
	}
}

