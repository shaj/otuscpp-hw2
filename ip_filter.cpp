
#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "version.h"

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



void print_ip_vector(std::ostream &s, std::vector<std::vector<unsigned char> > &v)
{
    for(auto it: v)
    {
        s << int(it[0]) << "." << int(it[1]) << "." << int(it[2]) << "." << int(it[3]);
        s << std::endl;
    }
}


int main(int argc, char const *argv[])
{
    try
    {
        std::cerr << "hw02 ip_filter" << std::endl;
        std::cerr << "Version " << PROJECT_VERSION_MAJOR << ".";
        std::cerr << PROJECT_VERSION_MINOR << ".";
        std::cerr << PROJECT_VERSION_PATCH << std::endl;

        std::vector<std::vector<unsigned char> > ip_bpool;

        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            v = split(v.at(0), '.');

            unsigned int id;
            unsigned char b0, b1, b2, b3;

            b3 = stoi(v.at(0));
            b2 = stoi(v.at(1));
            b1 = stoi(v.at(2));
            b0 = stoi(v.at(3));
            id = (b0 & 0xff) | ((b1 & 0xff) << 8)
                | ((b2 & 0xff) << 16) | ((b3 & 0xff) << 24);


            std::vector<unsigned char> vuc(4, 0);
            vuc[3] = b0;
            vuc[2] = b1;
            vuc[1] = b2;
            vuc[0] = b3;

            ip_bpool.push_back(vuc);

        }

        // TODO reverse lexicographically sort
        std::sort(ip_bpool.begin(), ip_bpool.end(), std::greater<decltype(ip_bpool)::value_type>());

        
        for(auto it: ip_bpool)
        {
            std::cout << int(it[0]) << "." << int(it[1]) << "." << int(it[2]) << "." << int(it[3]);
            std::cout << std::endl;
        }

        std::vector<std::vector<unsigned char> > ip_ex1;
        std::copy_if(ip_bpool.begin(), ip_bpool.end(), std::back_inserter(ip_ex1),
            [](auto it){return (it.at(0) == 1);});
        print_ip_vector(std::cout, ip_ex1);

        std::vector<std::vector<unsigned char> > ip_ex2;
        std::copy_if(ip_bpool.begin(), ip_bpool.end(), std::back_inserter(ip_ex2),
            [](auto it){return (it.at(0) == 46) && (it.at(1) == 70);});
        print_ip_vector(std::cout, ip_ex2);

        std::vector<std::vector<unsigned char> > ip_ex3;
        std::copy_if(ip_bpool.begin(), ip_bpool.end(), std::back_inserter(ip_ex3),
            [](auto it)
            {
                bool retval = (it.at(0) == 46) || (it.at(1) == 46) || (it.at(2) == 46) || (it.at(3) == 46);
                return retval;
            });
        print_ip_vector(std::cout, ip_ex3);

    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
