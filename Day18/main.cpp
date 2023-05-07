#include <stack>
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

std::vector<std::vector<int>> lights{};

struct Pair
{
	int x{};
	int y{};
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	while (input >> line)
	{
		lights.push_back({});
		for (const char& c : line)
			lights.back().push_back(c == '#');
	}

	for (int iter{}; iter < 100; iter++)
	{
		std::stack<Pair> toToggle{};
		for (int y{}; y != lights.size(); y++)
			for (int x{}; x != lights[y].size(); x++)
			{
				int sum{};
				for (int i{ y - 1 }; i != y + 2; i++)
					for (int j{ x - 1 }; j != x + 2; j++)
						if (i == y && j == x) continue;
						else try
						{
							sum += lights.at(i).at(j);
						} catch (...) {}

				if (lights[y][x])
				{
					if (sum != 2 && sum != 3)
						toToggle.push({ x, y });
				}
				else if (sum == 3) toToggle.push({ x, y });
			}

		while (toToggle.size())
		{
			lights[toToggle.top().y][toToggle.top().x] ^= 1;
			toToggle.pop();
		}
	}
	
	int count{};
	for (const std::vector<int>& row : lights)
		for (const int& light : row)
			if (light) count++;

	std::cout << "Part 1: " << count << "\n\n";

	lights.clear();
	input.close();
	input.open("input.txt");
	while (input >> line)
	{
		lights.push_back({});
		for (const char& c : line)
			lights.back().push_back(c == '#');
	}

	for (int iter{}; iter < 100; iter++)
	{
		std::stack<Pair> toToggle{};
		for (int y{}; y != lights.size(); y++)
			for (int x{}; x != lights[y].size(); x++)
			{
				int sum{};
				for (int i{ y - 1 }; i != y + 2; i++)
					for (int j{ x - 1 }; j != x + 2; j++)
						if (i == y && j == x) continue;
						else try
						{
							sum += lights.at(i).at(j);
						}
				catch (...) {}

				if (lights[y][x])
				{
					if (sum != 2 && sum != 3)
						toToggle.push({ x, y });
				}
				else if (sum == 3) toToggle.push({ x, y });
			}

		while (toToggle.size())
		{
			lights[toToggle.top().y][toToggle.top().x] ^= 1;
			toToggle.pop();
		}

		lights[0][0] = 1;
		lights[lights.size() - 1][0] = 1;
		lights[0][lights.size() - 1] = 1;
		lights[lights.size() - 1][lights.size() - 1] = 1;
	}

	count = 0;
	for (const std::vector<int>& row : lights)
		for (const int& light : row)
			if (light) count++;

	std::cout << "Part 2: " << count << "\n\n";

	return 0;
}