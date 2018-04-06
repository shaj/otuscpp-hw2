

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <array>
#include <algorithm>


// typedef std::vector<std::size_t> ip_t;
typedef std::array<std::size_t, 4> ip_t;

std::vector<std::string> split(const std::string &str, char d);

void iplist_read(std::istream &is, std::vector<ip_t> &v);
void iplist_basesort(std::vector<ip_t> &v);
void iplist_print(std::ostream &os, std::vector<ip_t> &v);

template< class UnaryPredicate >
void iplist_filter(std::vector<ip_t> &out_v, std::vector<ip_t> &base_v, UnaryPredicate p)
{
	std::copy_if(base_v.begin(), base_v.end(), std::back_inserter(out_v), p);
}

