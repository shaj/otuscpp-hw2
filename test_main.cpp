


#define BOOST_TEST_MODULE test_main


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

	// std::string correct_out_data { "219.102.120.135\n"
	//                                "185.69.186.168\n"
	//                                "185.46.85.78\n"
	//                                "110.152.103.161\n"
	//                                "85.254.10.197\n"
	//                                "67.232.81.208\n"
	//                                "46.70.113.73\n"
	//                                "46.70.29.76\n"
	//                                "23.240.215.189\n"
	//                                "1.70.44.170\n"
	//                                "1.29.168.152\n"
	//                                "1.70.44.170\n"
	//                                "1.29.168.152\n"
	//                                "46.70.113.73\n"
	//                                "46.70.29.76\n"
	//                                "185.46.85.78\n"
	//                                "46.70.113.73\n"
	//                                "46.70.29.76\n"
	// };


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
	// std::stringbuf out_buffer;
	std::istream in_stream(&in_buffer);
	// std::ostream out_stream(&out_buffer);
	std::vector<ip_t> out_data {};


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

BOOST_AUTO_TEST_CASE(broken_data)
{
	std::string correct_in_data { "219.102.120.135\t486\t0\n"
								  "67.232.81.208\t1\t0\n"
								  "185.46.85.78\n"
								  "1.70.44.\n"
								  "85.254.\n"
								  "a.b.c.189\t6\t0\n"
								  "46.70.113.73\t3\t6\n"
								  "1.29.168.152\t17\t0\n"
								  "185.69.186.168\t1\n"
								  "46.70.29.76\t3\6\n"
								  "110.152.103.161\t0\t1\n"
	};

	std::stringbuf in_buffer(correct_in_data);
	std::istream in_stream(&in_buffer);
	std::vector<ip_t> out_data {};

	BOOST_CHECK_THROW(out_data = iplist_read(in_stream), std::exception);
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
	std::string correct_out_data { "185.46.85.78\n"
								   "46.70.113.73\n"
								   "46.70.29.76\n"
	};

	std::stringbuf out_buffer;
	std::ostream out_stream(&out_buffer);

	BOOST_CHECK_NO_THROW(iplist_print(out_stream, in_data, 
					[](auto it)
					{
						return std::find_if(it.begin(), it.end(), [](auto b){return b == 46;}) != it.end();
					}));
	BOOST_CHECK(out_buffer.str() == correct_out_data);
}

BOOST_AUTO_TEST_SUITE_END()


