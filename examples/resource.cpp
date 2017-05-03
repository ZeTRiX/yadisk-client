#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <cstdlib>
#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
    path root { "/" };

    ydclient client{ std::getenv("YADISK_TOKEN") };

    auto answer = client.info(root);
    std::cout << answer << std::endl;
}
