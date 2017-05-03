#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <cstdlib>
#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
    path resource{ "/file1.txt" };
    ydclient client{ std::getenv("YADISK_TOKEN") };
    json meta = "{\"custom_properties\":{\"foo\":\"1\",\"bar\":\"2\"}}"_json;
    std::list<std::string> fields {"custom_properties.foo", "custom_properties.bar"};
    auto answer = client.patch(resource, meta, fields);
    std::cout << answer << std::endl;
}


