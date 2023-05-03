#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

struct City
{
	std::string id{};
	std::map<City*, int> dist{};
	bool visited{};

	bool operator==(const std::string& B) const { return id == B; }
};

std::vector<City> cities{};

City* getShortest(City* city)
{
	City* result{};
	int shortest{ INT_MAX };
	for (std::map<City*, int>::iterator dest{ city->dist.begin() }; dest != city->dist.end(); dest++)
		if (dest->second < shortest && !dest->first->visited)
		{
			shortest = dest->second;
			result = dest->first;
		}
	return result;
}

City* getLongest(City* city)
{
	City* result{};
	int longest{};
	for (std::map<City*, int>::iterator dest{ city->dist.begin() }; dest != city->dist.end(); dest++)
		if (dest->second > longest && !dest->first->visited)
		{
			longest = dest->second;
			result = dest->first;
		}
	return result;
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	std::vector<std::vector<std::string>> paths{};
	while (std::getline(input, line))
	{
		paths.push_back({ {} });
		for (const char& c : line)
			if (c == ' ') paths.back().push_back("");
			else paths.back().back().push_back(c);
		if (std::find(cities.begin(), cities.end(), paths.back().front()) == cities.end())
			cities.push_back({ paths.back().front() });
	}
	cities.push_back({ paths.back()[2] });

	for (std::vector<std::string> path : paths)
	{
		std::vector<City>::iterator dep{ std::find(cities.begin(), cities.end(), path[0]) };
		std::vector<City>::iterator arr{ std::find(cities.begin(), cities.end(), path[2]) };
		arr->dist[&(*dep)] = std::stoi(path[4]);
		dep->dist[&(*arr)] = std::stoi(path[4]);
	}

	int minDistance{ INT_MAX };
	for (City& city : cities)
	{
		int distance{};
		City* pos{ &city };
		while (City* dest{ getShortest(pos) })
		{
			pos->visited = true;
			distance += pos->dist[dest];
			if (distance > minDistance) break;
			pos = dest;
		}
		if (distance < minDistance)
			minDistance = distance;
		for (City& cleanCity : cities) cleanCity.visited = false;
	}
	
	std::cout << "Part 1: " << minDistance << "\n\n";

	int maxDistance{};
	for (City& city : cities)
	{
		int distance{};
		City* pos{ &city };
		while (City * dest{ getLongest(pos) })
		{
			pos->visited = true;
			distance += pos->dist[dest];
			pos = dest;
		}
		if (distance > maxDistance)
			maxDistance = distance;
		for (City& cleanCity : cities) cleanCity.visited = false;
	}

	std::cout << "Part 2: " << maxDistance << "\n\n";

	return 0;
}