

#pragma once

#include <iostream>
#include <array>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>

using ip_t = std::vector<std::size_t>;

namespace std { // Взято отсюда: https://ru.stackoverflow.com/a/267766

std::ostream& operator<<(std::ostream& os, const ip_t &ip);

}


std::vector<std::string> split(const std::string &str, char d);

std::vector<ip_t> iplist_read(std::istream &is);
std::vector<ip_t> iplist_basesort(std::vector<ip_t> &v);

template<class P>
void iplist_print(std::ostream &os, const std::vector<ip_t> &v, P p)
{
	std::ostream_iterator<ip_t> out_it (os,"\n");	
	std::copy_if(
		std::begin(v), 
		std::end(v), 
		std::ostream_iterator<ip_t> (os,"\n"), 
		p);
}

