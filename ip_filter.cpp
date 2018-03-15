#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <map>
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

struct StrInfo
{
    StrInfo(std::string line)
    {
        try
        {
            std::vector<std::string> v = split(line, '\t');
            std::vector<std::string> ip = split(v.at(0), '.');
            b3 = stoi(ip.at(0));
            b2 = stoi(ip.at(1));
            b1 = stoi(ip.at(2));
            b0 = stoi(ip.at(3));
            id = (b0 & 0xff) | ((b1 & 0xff) << 8)
                | ((b2 & 0xff) << 16) | ((b3 & 0xff) << 24);
        }
        catch(const std::exception& e)
        {
            id = b0 = b1 = b2 = b3 = 0;
            std::cerr << e.what() << std::endl;
        }
    }

    int id;
    int b0, b1, b2, b3;
    //std::string

    // bool operator()(StrInfo &a, StrInfo &b)
    // {
    //     return a.id < b.id;
    // }

    // bool operator<(const StrInfo &a) const
    // {
    //     return id < a.id;
    // }

    // StrInfo &operator=(StrInfo &a)
    // {
    //     std::swap(*this, a);

    //     return *this;
    // }

    // StrInfo &operator=(StrInfo &&a)
    // {
    //     return *this;
    // }

};

bool ip_cmp(std::vector<std::string> const &a, std::vector<std::string> const &b)
{
    // if(a.at(0) < b.at(0)) return false;
    // else if(
    return true;
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
        std::cout << "hw02 ip_filter" << std::endl;
        std::cout << "Version " << PROJECT_VERSION_MAJOR << ".";
        std::cout << PROJECT_VERSION_MINOR << ".";
        std::cout << PROJECT_VERSION_PATCH << std::endl;


        std::vector<std::vector<std::string> > ip_pool;
        std::vector<unsigned int> ip_zip;

        std::map<unsigned int, std::vector<std::string> > ip_map;
        
        std::vector<std::vector<unsigned char> > ip_bpool;



        for(std::string line; std::getline(std::cin, line);)
        {
            std::vector<std::string> v = split(line, '\t');
            v = split(v.at(0), '.');
            ip_pool.push_back(v);
            // StrInfo v(line);
            // ip_pool.push_back(v);

            unsigned int id;
            unsigned char b0, b1, b2, b3;

            b3 = stoi(v.at(0));
            b2 = stoi(v.at(1));
            b1 = stoi(v.at(2));
            b0 = stoi(v.at(3));
            id = (b0 & 0xff) | ((b1 & 0xff) << 8)
                | ((b2 & 0xff) << 16) | ((b3 & 0xff) << 24);

            // ip_map.insert(std::pair<unsigned int, std::vector<std::string> >(id, v));
            ip_map[id] = v;

            ip_zip.push_back(id);

            std::vector<unsigned char> vuc(4, 0);
            vuc[3] = b0;
            vuc[2] = b1;
            vuc[1] = b2;
            vuc[0] = b3;

            ip_bpool.push_back(vuc);

        }

        // TODO reverse lexicographically sort
        // std::sort(ip_pool.cbegin(), ip_pool.cend(),
        //         [] (std::vector<std::string> const & a, 
        //             std::vector<std::string> const & b) 
        //         { 
        //             return true; 
        //         }
        //         );

        // std::sort(ip_pool.begin(), ip_pool.end(), ip_cmp);
        // std::sort(ip_pool.begin(), ip_pool.end());

        std::sort(std::begin(ip_pool), std::end(ip_pool), std::greater<decltype(ip_pool)::value_type>());

        std::sort(ip_zip.begin(), ip_zip.end(), std::greater<decltype(ip_zip)::value_type>());
        std::sort(ip_bpool.begin(), ip_bpool.end(), std::greater<decltype(ip_bpool)::value_type>());

        
        // for(auto it: ip_bpool)
        // {
        //     std::cout << int(it[0]) << "." << int(it[1]) << "." << int(it[2]) << "." << int(it[3]);
        //     std::cout << std::endl;
        // }


        int a = 46;

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


        // for(auto it: ip_ex1)
        // {
        //     std::cout << int(it[0]) << "." << int(it[1]) << "." << int(it[2]) << "." << int(it[3]);
        //     std::cout << std::endl;
        // }


        // for(auto it: ip_zip)
        // {
        //     int b0, b1, b2, b3;
        //     b3 = (it & 0xff);
        //     b2 = ((it >> 8) & 0xff);
        //     b1 = ((it >> 16) & 0xff);
        //     b0 = ((it >> 24) & 0xff);
        //     std::cout << b0 << "." << b1
        //             << "." << b2
        //             << "." << b3 << std::endl;
        // }


        // for(std::vector<std::vector<std::string> >::const_iterator ip = ip_pool.cbegin(); ip != ip_pool.cend(); ++ip)
        // {
        //     for(std::vector<std::string>::const_iterator ip_part = ip->cbegin(); ip_part != ip->cend(); ++ip_part)
        //     {
        //         if (ip_part != ip->cbegin())
        //         {
        //             std::cout << ".";

        //         }
        //         std::cout << *ip_part;
        //     }
        //     std::cout << std::endl;
        // }

        // for(auto &ip: ip_pool)
        // {
        //     for(auto ip_part: ip)
        //     {
        //         if (ip_part != *(ip.cbegin()))
        //         {
        //             std::cout << ".";
        //         }
        //         std::cout << ip_part;
        //     }
        //     std::cout << std::endl;
        // }

        // for(auto it: ip_map)
        // for(auto it = ip_map.rbegin(); it != ip_map.rend(); ++it)
        // {
        //     std::cout << it->first << "    ";
        //     for(auto &ip_part: it->second)
        //     {
        //         if (ip_part != it->second.begin())
        //         {
        //             std::cout << ".";
        //         }
        //         std::cout << *ip_part;
        //     }
        //     std::cout << std::endl;
        // }
                                   
/*		
		std::sort(object.begin(), object.end(),
          [] (myclass const& a, myclass const& b) { return a.v < b.v; });
		
*/		
		
        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
