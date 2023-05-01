#include <iostream>
#include <fstream>
#include <string>

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
		totalSurface +=
			2 * dimensions[0] * dimensions[1] +
			2 * dimensions[1] * dimensions[2] +
			2 * dimensions[2] * dimensions[0];
	}

	std::cout << "Part 1: " << totalSurface << "\n\n";

	return 0;
}