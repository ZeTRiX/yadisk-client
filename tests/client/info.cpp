#include <catch.hpp>
#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <string>
#include <list>

#include <url/path.hpp>
using url::path;

TEST_CASE("get info with valid token", "[client][info]") {
    std::string token = "AQAAAAATPnx3AAQXOJS1w4zmPUdrsJNR1FATxEM";
    ydclient client{ token };
    auto info = client.info();
    REQUIRE(info.find("trash_size") != info.end());
    REQUIRE(info.find("total_space") != info.end());
    REQUIRE(info.find("used_space") != info.end());
    REQUIRE(info.find("system_folders") != info.end());
}

TEST_CASE("get info with invalid token", "[client][info]") {
    std::string token = "WRONG_TOKEN";
    ydclient client{ token };
    auto info = client.info();
    REQUIRE(info.empty());
}
