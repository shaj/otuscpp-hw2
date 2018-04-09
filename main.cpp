
#include <iostream>
#include <string>

#include "version.h"
#include "ip_filter.h"



int main(int argc, char const *argv[])
{
	if(argc > 1)
	{
		if((std::string(argv[1]) == "-v")
			|| (std::string(argv[1]) == "--version"))
		{
			std::cout << "hw02 ip_filter" << std::endl;
			std::cout << "Version " << PROJECT_VERSION_MAJOR << ".";
			std::cout << PROJECT_VERSION_MINOR << ".";
			std::cout << PROJECT_VERSION_PATCH << std::endl;
		}
		else if((std::string(argv[1]) == "-d")
			|| (std::string(argv[1]) == "--debug"))
		{
			std::cout << "Usage: ...\n";
		}
		else
		{
			std::cout << "Usage: ...\n";
		}
	}
	else
	{
		try
		{

			// std::vector<ip_t> ip_bpool;

			auto ip_bpool = iplist_read(std::cin);
			if(ip_bpool.size() == 0)
			{
				std::cerr << "Empty ip list.\n";
				return 1;
			}
			else
			{
				auto ip_sorted = std::move(iplist_basesort(ip_bpool));
				iplist_print(std::cout, ip_sorted, true);

				iplist_print(std::cout, ip_sorted, [](auto it){return (it.at(0) == 1);});
				iplist_print(std::cout, ip_sorted, 
					[](auto it){return (it.at(0) == 46) && (it.at(1) == 70);});
				iplist_print(std::cout, ip_sorted,
					[](auto it)
					{
						return std::find_if(it.begin(), it.end(), [](auto b){return b == 46;}) != it.end();
					});
			}
		}
		catch(const std::exception &e)
		{
			std::cerr << e.what() << std::endl;
		}

	}

	return 0;
}
