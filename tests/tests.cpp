
#define CATCH_CONFIG_MAIN
#include "catch.hpp"

#include "ip_filter.h"


TEST_CASE("Split string", "[split]")
{
	REQUIRE(split("",  '.') == std::vector<std::string>({""}));
	REQUIRE(split("11", '.') == std::vector<std::string>({"11"}));
	REQUIRE(split("..", '.') == std::vector<std::string>({"", "", ""}));
	REQUIRE(split("11.", '.') == std::vector<std::string>({"11", ""}));
	REQUIRE(split(".11", '.') == std::vector<std::string>({"", "11"}));
	REQUIRE(split("11.22", '.') == std::vector<std::string>({"11", "22"}));
	REQUIRE(split("a.b.c.d", '.') == std::vector<std::string>({"a", "b", "c", "d"}));
}


TEST_CASE("Read base array", "[read]")
{
	REQUIRE(false);
}
