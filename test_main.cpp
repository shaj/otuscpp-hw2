


#define BOOST_TEST_MODULE test_main

#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <unistd.h>
#include "ip_filter.h"

#include <boost/test/unit_test.hpp>


// BOOST_TEST_SPECIALIZED_COLLECTION_COMPARE(std::vector<ip_t>)

BOOST_AUTO_TEST_SUITE(test_split_suite)

BOOST_AUTO_TEST_CASE(test_split)
{
	BOOST_CHECK(split("",  '.') == std::vector<std::string>({""}));
	BOOST_CHECK(split("11", '.') == std::vector<std::string>({"11"}));
	BOOST_CHECK(split("..", '.') == std::vector<std::string>({"", "", ""}));
	BOOST_CHECK(split("11.", '.') == std::vector<std::string>({"11", ""}));
	BOOST_CHECK(split(".11", '.') == std::vector<std::string>({"", "11"}));
	BOOST_CHECK(split("11.22", '.') == std::vector<std::string>({"11", "22"}));
}

BOOST_AUTO_TEST_SUITE_END()



BOOST_AUTO_TEST_SUITE(stream_reader_suite)

BOOST_AUTO_TEST_CASE(good_data)
{
	std::string correct_in_data { "219.102.120.135\t486\t0\n"
								  "67.232.81.208\t1\t0\n"
								  "185.46.85.78\t5\t4\n"
								  "1.70.44.170\t4665\t0\n"
								  "85.254.10.197\t0\n"
								  "23.240.215.189\t6\t0\n"
								  "46.70.113.73\t3\t6\n"
								  "1.29.168.152\t17\t0\n"
								  "185.69.186.168\t1\n"
								  "46.70.29.76\t3\6\n"
								  "110.152.103.161\t0\t1\n"
	};

	std::vector<ip_t> correct_out_data {
		{219, 102, 120, 135},
		{67, 232, 81, 208},
		{185, 46, 85, 78},
		{1, 70, 44, 170},
		{85, 254, 10, 197},
		{23, 240, 215, 189},
		{46, 70, 113, 73},
		{1, 29, 168, 152},
		{185, 69, 186, 168},
		{46, 70, 29, 76},
		{110, 152, 103, 161}
	};

	std::stringbuf in_buffer(correct_in_data);
	std::istream in_stream(&in_buffer);

	std::vector<ip_t> out_data;

	BOOST_CHECK_NO_THROW(out_data = iplist_read(in_stream));

	BOOST_CHECK(out_data == correct_out_data);

}

BOOST_AUTO_TEST_CASE(empty_data)
{
	std::string correct_in_data {};


	std::vector<ip_t> correct_out_data {};

	std::stringbuf in_buffer(correct_in_data);
	std::istream in_stream(&in_buffer);
	std::vector<ip_t> out_data {};

	BOOST_CHECK_NO_THROW(out_data = iplist_read(in_stream));

	BOOST_CHECK(out_data == correct_out_data);

}

BOOST_AUTO_TEST_CASE(broken_octet_count)
{
	std::string correct_in_data { "219.102.120.135\t486\t0\n"
								  "67.232.81.208\t1\t0\n"
								  "1.70.44\t1\t0\n"
	};

	std::stringbuf in_buffer(correct_in_data);
	std::istream in_stream(&in_buffer);
	std::vector<ip_t> out_data {};

	BOOST_CHECK_THROW(out_data = iplist_read(in_stream), parser_error);
}

BOOST_AUTO_TEST_CASE(broken_data)
{
	std::string correct_in_data { "219.102.120.135\t486\t0\n"
								  "67.232.81.208\t1\t0\n"
								  "1.a.44.22\t1\t0\n"
	};

	std::stringbuf in_buffer(correct_in_data);
	std::istream in_stream(&in_buffer);
	std::vector<ip_t> out_data {};

	BOOST_CHECK_THROW(out_data = iplist_read(in_stream), parser_error);
}

BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(base_sort_suite)

BOOST_AUTO_TEST_CASE(good_data)
{
	std::vector<ip_t> in_data {
		{219, 102, 120, 135},
		{67, 232, 81, 208},
		{185, 46, 85, 78},
		{1, 70, 44, 170},
		{85, 254, 10, 197},
		{23, 240, 215, 189},
		{46, 70, 113, 73},
		{1, 29, 168, 152},
		{185, 69, 186, 168},
		{46, 70, 29, 76},
		{110, 152, 103, 161}
	};
	std::vector<ip_t> correct_out_data {
		{219, 102, 120, 135},
		{185, 69, 186, 168},
		{185, 46, 85, 78},
		{110, 152, 103, 161},
		{85, 254, 10, 197},
		{67, 232, 81, 208},
		{46, 70, 113, 73},
		{46, 70, 29, 76},
		{23, 240, 215, 189},
		{1, 70, 44, 170},
		{1, 29, 168, 152}
	};

	BOOST_CHECK_NO_THROW(iplist_basesort(in_data));
	BOOST_CHECK(in_data == correct_out_data);
}

BOOST_AUTO_TEST_CASE(empty_data)
{
	std::vector<ip_t> in_data {};
	std::vector<ip_t> correct_out_data {};

	BOOST_CHECK_NO_THROW(iplist_basesort(in_data));
	BOOST_CHECK(in_data == correct_out_data);
}

BOOST_AUTO_TEST_SUITE_END()






BOOST_AUTO_TEST_SUITE(print_list_suite)

BOOST_AUTO_TEST_CASE(print_list_case)
{
	std::vector<ip_t> in_data {
		{219, 102, 120, 135},
		{67, 232, 81, 208},
		{185, 46, 85, 78},
		{1, 70, 44, 170},
		{85, 254, 10, 197},
		{23, 240, 215, 189},
		{46, 70, 113, 73},
		{1, 29, 168, 152},
		{185, 69, 186, 168},
		{46, 70, 29, 76},
		{110, 152, 103, 161}
	};
	std::string correct_out_data { 	"219.102.120.135\n"
									"67.232.81.208\n"
									"185.46.85.78\n"
									"1.70.44.170\n"
									"85.254.10.197\n"
									"23.240.215.189\n"
									"46.70.113.73\n"
									"1.29.168.152\n"
									"185.69.186.168\n"
									"46.70.29.76\n"
									"110.152.103.161\n"

	};

	std::stringbuf out_buffer;
	std::ostream out_stream(&out_buffer);

	BOOST_CHECK_NO_THROW(iplist_print(out_stream, in_data));
	BOOST_CHECK(out_buffer.str() == correct_out_data);
}


BOOST_AUTO_TEST_CASE(print_list_if_case)
{
	std::vector<ip_t> in_data {
		{219, 102, 120, 135},
		{67, 232, 81, 208},
		{185, 46, 85, 78},
		{1, 70, 44, 170},
		{85, 254, 10, 197},
		{23, 240, 215, 189},
		{46, 70, 113, 73},
		{1, 29, 168, 152},
		{185, 69, 186, 168},
		{46, 70, 29, 76},
		{110, 152, 103, 161}
	};
	std::string correct_out_data { "185.46.85.78\n"
								   "46.70.113.73\n"
								   "46.70.29.76\n"
	};

	std::stringbuf out_buffer;
	std::ostream out_stream(&out_buffer);

	BOOST_CHECK_NO_THROW(iplist_print_if(out_stream, in_data, 
					[](auto it)
					{
						return std::any_of(it.begin(), it.end(), [](auto b){return b == 46;});
					}));
	BOOST_CHECK(out_buffer.str() == correct_out_data);
}


#include "openssl/md5.h"

std::string getMD5(const std::string & value)
{
    unsigned char result[MD5_DIGEST_LENGTH];
    std::ostringstream os_result;
    MD5((const unsigned char*)value.c_str(), value.size(), result);

    os_result << std::hex << std::setfill('0');
    for(long long c: result)
    {
        os_result << std::setw(2) << (long long)c;
    }
    return os_result.str();
}


BOOST_AUTO_TEST_CASE(final_result_case)
{
    std::ifstream file {"./ip_filter.tsv"};
	std::ostringstream os;

	if(file)
	{
		auto ip_bpool = iplist_read(file);

		iplist_basesort(ip_bpool);
		iplist_print(os, ip_bpool);
		iplist_print_if(os, ip_bpool, [](auto it){return (it.at(0) == 1);});
		iplist_print_if(os, ip_bpool, 
			[](auto it){return (it.at(0) == 46) && (it.at(1) == 70);});
		iplist_print_if(os, ip_bpool,
			[](auto it)
			{
				return std::any_of(it.begin(), it.end(), [](auto b){return b == 46;});
			});

	    auto md5 = getMD5(os.str());
	    BOOST_CHECK(md5 == "24e7a7b2270daee89c64d3ca5fb3da1a");
	}
	else
	{
		BOOST_FAIL("No data file for test");
	}
}

BOOST_AUTO_TEST_SUITE_END()


