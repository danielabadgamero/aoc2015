#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

int main()
{
	std::ifstream input{ "input.txt" };

	int totalSurface{};
	std::string line{};
	while (input >> line)
	{
		int selBuf{};
		std::string buf[3]{};
		int dimensions[3]{};
		for (const char& c : line)
			switch (c)
			{
			case 'x':
				dimensions[selBuf] = std::stoi(buf[selBuf]);
				buf[selBuf].clear();
				selBuf++;
				break;
			default:
				buf[selBuf].push_back(c);
			}
		dimensions[selBuf] = std::stoi(buf[selBuf]);
		int sideA{ 2 * dimensions[0] * dimensions[1] };
		int sideB{ 2 * dimensions[1] * dimensions[2] };
		int sideC{ 2 * dimensions[2] * dimensions[0] };
		totalSurface += sideA + sideB + sideC + std::min(sideA, std::min(sideB, sideC)) / 2;
	}

	std::cout << "Part 1: " << totalSurface << "\n\n";

	input.close();
	input.open("input.txt");
	int totalLength{};
	while (input >> line)
	{
		int selBuf{};
		std::string buf[3]{};
		int dimensions[3]{};
		for (const char& c : line)
			switch (c)
			{
			case 'x':
				dimensions[selBuf] = std::stoi(buf[selBuf]);
				buf[selBuf].clear();
				selBuf++;
				break;
			default:
				buf[selBuf].push_back(c);
			}
		dimensions[selBuf] = std::stoi(buf[selBuf]);
		
		std::sort(dimensions, dimensions + 3);
		totalLength += 2 * dimensions[0] + 2 * dimensions[1] + dimensions[0] * dimensions[1] * dimensions[2];
	}

	std::cout << "Part 2: " << totalLength << "\n\n";

	return 0;
}