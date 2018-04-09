

#pragma once

#include <iostream>
#include <iterator>
#include <string>
#include <vector>
#include <array>
#include <algorithm>


// typedef std::vector<std::size_t> ip_t;
typedef std::array<std::size_t, 4> ip_t;

std::vector<std::string> split(const std::string &str, char d);

void iplist_read(std::istream &is, std::vector<ip_t> &v);
void iplist_basesort(std::vector<ip_t> &v);


template< class UnaryPredicate >
void iplist_print(std::ostream &os, std::vector<ip_t> &v, UnaryPredicate p)
{
	std::ostream_iterator<decltype(v)> out_it (os,"\n");	
	std::copy_if(std::begin(v), std::end(v), out_it, p);
}


