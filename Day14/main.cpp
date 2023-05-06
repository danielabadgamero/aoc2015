#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

struct Reindeer
{
	std::string name{};
	int speed{};
	int flyTime{};
	int restTime{};
	int distance{};
	int timer{};
	int points{};
	enum Mode
	{
		flying,
		resting,
	} mode{};

	void advance(int time)
	{
		int cycleTime{ flyTime + restTime };
		distance = speed * flyTime * (time / cycleTime);
		distance += std::clamp(time % cycleTime, 0, flyTime) * speed;
	}

	void step()
	{
		timer++;
		if (mode == flying)
		{
			distance += speed;
			if (timer == flyTime)
			{
				timer = 0;
				mode = resting;
			}
		}
		else if (timer == restTime)
		{
			timer = 0;
			mode = flying;
		}
	}
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	std::vector<Reindeer> reindeers{};
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			if (c == ' ') args.push_back("");
			else args.back().push_back(c);
		reindeers.push_back({ args[0], std::stoi(args[3]), std::stoi(args[6]), std::stoi(args[13]) });
	}

	int maxDistance{};
	for (Reindeer& reindeer : reindeers)
	{
		reindeer.advance(2503);
		if (reindeer.distance > maxDistance)
			maxDistance = reindeer.distance;
	}

	std::cout << "Part 1: " << maxDistance << "\n\n";

	for (Reindeer& reindeer : reindeers)
		reindeer.distance = 0;

	for (int t{}; t != 2503; t++)
	{
		for (std::vector<Reindeer>::iterator reindeer{ reindeers.begin() }; reindeer != reindeers.end(); reindeer++)
			reindeer->step();
		std::sort(reindeers.begin(), reindeers.end(), [](Reindeer& A, Reindeer& B) {return A.distance > B.distance; });
		int firstPlace{ reindeers[0].distance };
		for (int i{}; i != reindeers.size(); i++)
			if (reindeers[i].distance < firstPlace) break;
			else reindeers[i].points++;
	}

	int maxPoints{};
	for (const Reindeer& reindeer : reindeers)
		if (reindeer.points > maxPoints)
			maxPoints = reindeer.points;

	std::cout << "Part 2: " << maxPoints << "\n\n";

	return 0;
}