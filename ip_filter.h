

#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


typedef std::vector<unsigned int> ip_t;

void iplist_read(std::istream &is, std::vector<ip_t> &v);
void iplist_basesort(std::vector<ip_t> &v);
void iplist_print(std::ostream &os, std::vector<ip_t> &v);

template< class UnaryPredicate >
void iplist_filter(std::vector<ip_t> &out_v, std::vector<ip_t> &base_v, UnaryPredicate p);

