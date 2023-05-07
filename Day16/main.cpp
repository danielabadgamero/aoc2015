#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

const std::map<std::string, std::string> sue
{
	{ "children", "3" },
	{ "cats", "7" },
	{ "samoyeds", "2" },
	{ "pomeranians", "3" },
	{ "akitas", "0" },
	{ "vizslas", "0" },
	{ "goldfish", "5" },
	{ "trees", "3" },
	{ "cars", "2" },
	{ "perfumes", "1" }
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	int sueNum{};
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			if (c == ' ') args.push_back("");
			else if (c != ',' && c != ':') args.back().push_back(c);
		for (size_t i{ 3 }; i != 9; i += 2)
			if (args[i] != sue.at(args[i - 1])) break;
			else if (i == 7) sueNum = std::stoi(args[1]);
	}

	std::cout << "Part 1: " << sueNum << "\n\n";

	input.close();
	input.open("input.txt");
	sueNum = 0;
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			if (c == ' ') args.push_back("");
			else if (c != ',' && c != ':') args.back().push_back(c);

		for (size_t i{ 3 }; i != 9; i += 2)
		{
			int realSue{ std::stoi(sue.at(args[i - 1])) };
			int testSue{ std::stoi(args[i]) };
			if (args[i - 1] == "cats" || args[i - 1] == "trees")
			{
				if (realSue >= testSue)
					break;
			}
			else if (args[i - 1] == "pomeranians" || args[i - 1] == "goldfish")
			{
				if (realSue <= testSue)
					break;
			}
			else if (args[i] != sue.at(args[i - 1]))
				break;

			if (i == 7)
				sueNum = std::stoi(args[1]);
		}
	}

	std::cout << "Part 2: " << sueNum << "\n\n";

	return 0;
}