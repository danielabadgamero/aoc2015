#include <iostream>
#include <fstream>
#include <string>

std::string lookAndSay(std::string in)
{
	std::string result{};
	char prevChar{};
	int num{};
	for (const char& c : in)
	{
		if (c == prevChar || num == 0)
		{
			prevChar = c;
			num++;
			continue;
		}
		else
		{
			result.append(std::to_string(num));
			result.push_back(prevChar);
			prevChar = c;
			num = 1;
		}
	}
	result.append(std::to_string(num));
	result.push_back(prevChar);

	return result;
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::string str{};
	std::getline(input, str);

	for (int i{}; i != 40; i++)
		str = lookAndSay(str);

	std::cout << "Part 1: " << str.length() << "\n\n";

	input.close();
	input.open("input.txt");
	std::getline(input, str);

	for (int i{}; i != 50; i++)
		str = lookAndSay(str);

	std::cout << "Part 2: " << str.length() << "\n\n";

	return 0;
}