#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

struct Light
{
	bool status{};
	int brightness{};

	void toggle() { status = !status; }
	void on() { status = true; }
	void off() { status = false; }

	void up() { brightness++; }
	void down() { if (brightness > 0) brightness--; }
	void up(int) { brightness += 2; }
};

Light lights[1000][1000]{};

struct Point
{
	int x{};
	int y{};
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string instruction{};
	while (std::getline(input, instruction))
	{
		Point start{};
		Point end{};
		std::vector<std::string> nums{};
		for (const char& c : instruction)
			if (c >= '0' && c <= '9')
				nums.back().push_back(c);
			else if (c == 't' || c == ',')
				nums.push_back("");
		start.x = std::stoi(nums[0]);
		start.y = std::stoi(nums[1]);
		end.x = std::stoi(nums[2]);
		end.y = std::stoi(nums[3]);

		for (int i{ start.x }; i <= end.x; i++)
			for (int j{ start.y }; j <= end.y; j++)
				if (instruction.find("on") != std::string::npos)
					lights[j][i].on();
				else if (instruction.find("off") != std::string::npos)
					lights[j][i].off();
				else lights[j][i].toggle();
	}
	
	int numLights{};
	for (int i{}; i != 1000; i++)
		for (int j{}; j != 1000; j++)
			if (lights[j][i].status)
				numLights++;

	std::cout << "Part 1: " << numLights << "\n\n";

	input.close();
	input.open("input.txt");
	while (std::getline(input, instruction))
	{
		Point start{};
		Point end{};
		std::vector<std::string> nums{};
		for (const char& c : instruction)
			if (c >= '0' && c <= '9')
				nums.back().push_back(c);
			else if (c == 't' || c == ',')
				nums.push_back("");
		start.x = std::stoi(nums[0]);
		start.y = std::stoi(nums[1]);
		end.x = std::stoi(nums[2]);
		end.y = std::stoi(nums[3]);

		for (int i{ start.x }; i <= end.x; i++)
			for (int j{ start.y }; j <= end.y; j++)
				if (instruction.find("on") != std::string::npos)
					lights[j][i].up();
				else if (instruction.find("off") != std::string::npos)
					lights[j][i].down();
				else lights[j][i].up(2);
	}

	int totalBrightness{};
	for (int i{}; i != 1000; i++)
		for (int j{}; j != 1000; j++)
			totalBrightness += lights[j][i].brightness;

	std::cout << "Part 2: " << totalBrightness << "\n\n";

	return 0;
}