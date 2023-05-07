#include <iostream>
#include <fstream>
#include <algorithm>
#include <string>
#include <vector>
#include <map>

std::vector<int> containers{};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	while (input >> line)
		containers.push_back(std::stoi(line));

	int minContainers{ INT_MAX };
	std::vector<size_t> combs{};
	for (size_t i{}; i != pow(2, containers.size()); i++)
	{
		int sum{};
		int numContainers{};
		for (size_t b{}; b != containers.size(); b++)
		{
			if (i & (1ull << b))
			{
				sum += containers[b];
				numContainers++;
			}
			if (sum == 150)
				if (std::find_if(combs.begin(), combs.end(), [&](size_t comb)
					{
						size_t lastBit{};
						for (size_t bit{}; bit != containers.size(); bit++)
							if (comb & (1ull << bit)) lastBit = bit;
						for (size_t bit{}; bit <= lastBit; bit++)
							if ((i & (1ull << bit)) != (comb & (1ull << bit)))
								return false;
						return true;
					}) == combs.end())
				{
					if (numContainers < minContainers)
						minContainers = numContainers;
					combs.push_back(i);
					break;
				}
		}
	}

	std::cout << "Part 1: " << combs.size() << "\n\n";

	combs.clear();
	for (size_t i{}; i != pow(2, containers.size()); i++)
	{
		int sum{};
		int numContainers{};
		for (size_t b{}; b != containers.size(); b++)
		{
			if (i & (1ull << b))
			{
				numContainers++;
				sum += containers[b];
			}
			if (sum == 150)
				if (std::find_if(combs.begin(), combs.end(), [&](size_t comb)
					{
						size_t lastBit{};
						for (size_t bit{}; bit != containers.size(); bit++)
							if (comb & (1ull << bit)) lastBit = bit;
						for (size_t bit{}; bit <= lastBit; bit++)
							if ((i & (1ull << bit)) != (comb & (1ull << bit)))
								return false;
						return true;
					}) == combs.end())
					if (numContainers == minContainers)
					{
						combs.push_back(i);
						break;
					}
		}
	}

	std::cout << "Part 2: " << combs.size() << "\n\n";

	return 0;
}