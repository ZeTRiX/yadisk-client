#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <cstdlib>
#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
    path resource { "file2.txt" };
    ydclient client{ std::getenv("YADISK_TOKEN") };

    auto answer = client.remove(resource, true);
    std::cout << answer << std::endl;
}
