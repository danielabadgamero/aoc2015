#include <iostream>
#include <fstream>
#include <string>

int main()
{
	std::ifstream input{ "input.txt" };
	int dif{};
	std::string line{};
	while (std::getline(input, line))
	{
		int memorySize{};
		for (std::string::iterator c{ line.begin() }; c != line.end(); c++)
			if (*c == '\\')
			{
				memorySize++;
				if (*(c + 1) == 'x') c += 3;
				else c++;
			}
			else if (c != line.begin() && c + 1 != line.end()) memorySize++;
		dif += static_cast<int>(line.length()) - memorySize;
	}

	std::cout << "Part 1: " << dif << "\n\n";

	input.close();
	input.open("input.txt");
	dif = 0;
	while (std::getline(input, line))
	{
		int numCharacters{};
		for (std::string::iterator c{ line.begin() }; c != line.end(); c++)
			switch (*c)
			{
			case '\\': case '"': numCharacters += 2; break;
			default: numCharacters++;
			}
		numCharacters += 2;
		dif += numCharacters - static_cast<int>(line.length());
	}

	std::cout << "Part 2: " << dif << "\n\n";

	return 0;
}