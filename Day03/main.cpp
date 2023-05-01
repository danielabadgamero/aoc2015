#include <iostream>
#include <fstream>
#include <unordered_set>
#include <string>

struct Point
{
	int x{};
	int y{};

	bool operator==(const Point& B) const
	{
		return x == B.x && y == B.y;
	}
};

struct HashFunc
{
	size_t operator()(const Point& B) const
	{
		std::string tmp{ std::to_string(B.x) + std::to_string(B.y) };
		return tmp.length();
	}
};

int main()
{
	std::ifstream input{ "input.txt" };
	
	Point currentPos{};
	std::unordered_set<Point, HashFunc> places{};
	while (char c{ static_cast<char>(input.get()) })
		if (c == -1) break;
		else
		{
			places.insert(currentPos);
			switch (c)
			{
			case '^':
				currentPos.y++;
				break;
			case 'v':
				currentPos.y--;
				break;
			case '<':
				currentPos.x--;
				break;
			case '>':
				currentPos.x++;
				break;
			}
		}

	std::cout << "Part 1: " << places.size() << '\n';

	places.clear();
	input.close();
	input.open("input.txt");
	Point posA{};
	Point posB{};
	Point* active{ &posA };
	while (char c{ static_cast<char>(input.get()) })
		if (c == -1) break;
		else
		{
			places.insert(*active);
			if (active == &posA) active = &posB;
			else active = &posA;
			switch (c)
			{
			case '^':
				active->y++;
				break;
			case 'v':
				active->y--;
				break;
			case '<':
				active->x--;
				break;
			case '>':
				active->x++;
				break;
			}
		}

	std::cout << "Part 2: " << places.size() << '\n';

	return 0;
}