#include <iostream>
#include <fstream>
#include <map>
#include <string>

struct Guest
{
	std::string name{};
	std::map<Guest*, int> happiness{};
};

int main()
{
	std::ifstream input{ "input.txt" };

	return 0;
}