#include <yadisk/client.hpp>
using ydclient = yadisk::Client;

#include <cstdlib>
#include <iostream>
#include <string>

#include <url/path.hpp>
using url::path;

int main() {
	path old_path { "file1.txt" };
	path new_path { "file2.txt" };
	ydclient client{ std::getenv("YADISK_TOKEN") };

	auto answer = client.move(old_path, new_path, true);
	std::cout << answer << std::endl;
}
