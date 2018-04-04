


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



BOOST_AUTO_TEST_SUITE(stream_reader)

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

    BOOST_CHECK_NO_THROW(iplist_read(in_stream, out_data));

	BOOST_CHECK(out_data == correct_out_data);

}

BOOST_AUTO_TEST_CASE(empty_data)
{
}

BOOST_AUTO_TEST_CASE(broken_data)
{
}

BOOST_AUTO_TEST_SUITE_END()





BOOST_AUTO_TEST_SUITE(base_sort_suite)

BOOST_AUTO_TEST_CASE(good_data)
{
}

BOOST_AUTO_TEST_CASE(empty_data)
{
}

BOOST_AUTO_TEST_SUITE_END()






BOOST_AUTO_TEST_SUITE(print_list_suite)

BOOST_AUTO_TEST_CASE(good_data)
{
}

BOOST_AUTO_TEST_CASE(empty_data)
{
}

BOOST_AUTO_TEST_SUITE_END()




BOOST_AUTO_TEST_SUITE(iplist_filter_suite)

BOOST_AUTO_TEST_CASE(good_data)
{
}

BOOST_AUTO_TEST_CASE(empty_data)
{
}

BOOST_AUTO_TEST_SUITE_END()