#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <cstdlib>
#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
    ydclient client{ std::getenv("YADISK_TOKEN") };
    auto answer = client.list();
    std::cout << answer << std::endl;
}
