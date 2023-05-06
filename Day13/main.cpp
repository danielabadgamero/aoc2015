#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

struct Guest
{
	std::string name{};
	std::map<std::string, int> happiness{};

	bool operator==(const std::string& B) const { return name == B; }
};

int getHappiness(std::vector<Guest>& table)
{
	int happiness{};
	for (std::vector<Guest>::iterator guest{ table.begin() + 1 }; guest + 1 != table.end(); guest++)
	{
		happiness += guest->happiness[(guest - 1)->name];
		happiness += guest->happiness[(guest + 1)->name];
	}
	happiness += table.front().happiness[table[1].name];
	happiness += table.front().happiness[table.back().name];
	happiness += table.back().happiness[table.front().name];
	happiness += table.back().happiness[table[table.size() - 2].name];

	return happiness;
}

int main()
{
	std::vector<Guest> guests{};

	std::ifstream input{ "input.txt" };
	std::string line{};
	while (std::getline(input, line))
		if (std::find(guests.begin(), guests.end(), line.substr(0, line.find(' '))) == guests.end())
			guests.push_back({ line.substr(0, line.find(' ')) });
	input.close();
	input.open("input.txt");
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			if (c == ' ') args.push_back("");
			else if (c != '.') args.back().push_back(c);
		int happiness{ std::stoi(args[3]) };
		if (args[2] == "lose") happiness *= -1;
		std::find(guests.begin(), guests.end(), args[0])->happiness.emplace(args[10], happiness);
	}

	int maxHappiness{};
	for (int i{}; i != 10000; i++)
	{
		std::shuffle(guests.begin(), guests.end(), std::mt19937{ (uint32_t)std::chrono::system_clock::now().time_since_epoch().count() });
		if (getHappiness(guests) > maxHappiness)
		{
			maxHappiness = getHappiness(guests);
			i = 0;
		}
	}

	std::cout << "Part 1: " << maxHappiness << "\n\n";

	maxHappiness = 0;
	guests.push_back({ "I" });
	for (int i{}; i != 100000; i++)
	{
		std::shuffle(guests.begin(), guests.end(), std::mt19937{ (uint32_t)std::chrono::system_clock::now().time_since_epoch().count() });
		if (getHappiness(guests) > maxHappiness)
		{
			maxHappiness = getHappiness(guests);
			i = 0;
		}
	}

	std::cout << "Part 2: " << maxHappiness << "\n\n";

	return 0;
}