#include <iostream>
#include <fstream>
#include <string>

bool validHash(std::string hash)
{
	for (int i{}; i != 5; i++)
		if (hash[i] != '0') return false;
	return true;
}

std::string md5(std::string input)
{

}

int main()
{
	std::ifstream input{ "input.txt" };
	std::string key{};
	input >> key;

	int solution{};
	for (int i{}; solution == 0; i++)
		if (validHash(md5(key + std::to_string(i))))
			solution = i;

	return 0;
}