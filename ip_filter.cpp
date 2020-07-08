
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <exception>

#include "version.h"
#include "ip_filter.h"


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
		v = split(v.at(0), '.');

		try
		{
			bv.push_back(ip_t { std::stoi(v.at(0)), 
								std::stoi(v.at(1)), 
								std::stoi(v.at(2)), 
								std::stoi(v.at(3)) });
		}
		catch(const std::invalid_argument &e)
		{
			throw parser_error("Parse error at \"" + line + "\". Cannot parse to int.");
		}
		catch(const std::out_of_range &e)
		{
			throw parser_error("Parse error at \"" + line + "\". Octet out of range.");
		}
		catch(const std::exception &e)
		{
			throw parser_error("Parse error at \"" + line + "\"");
		}
	}
	return bv;
}	


void iplist_basesort(std::vector<ip_t> &v)
{
	std::sort(std::begin(v), std::end(v), std::greater<ip_t>());
	// return v;
}



std::ostream& std::operator <<(std::ostream& os, const ip_t &ip)
{
	os << ip[0] << "." << ip[1] << "." << ip[2] << "." << ip[3];
	return os;
}


void iplist_print(std::ostream &os, const std::vector<ip_t> &v)
{
	iplist_print_if(os, v, [](auto it){return true;});
}


