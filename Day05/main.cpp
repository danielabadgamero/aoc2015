#include <iostream>
#include <fstream>
#include <string>

char vowels[5]{ 'a', 'e', 'i', 'o', 'u' };
std::string badStrings[4]{ "ab", "cd", "pq", "xy" };

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	int niceStrings{};
	while (input >> line)
	{
		int vowelsCount{};
		for (char& c : vowels)
			vowelsCount += static_cast<int>(std::count(line.begin(), line.end(), c));

		bool repeated{};
		for (std::string::iterator c{line.begin()}; c + 1 != line.end(); c++)
			if (*c == *(c + 1))
			{
				repeated = true;
				break;
			}

		bool containsBadString{};
		for (std::string& badStr : badStrings)
			if (line.find(badStr) != std::string::npos)
			{
				containsBadString = true;
				break;
			}

		if (vowelsCount >= 3 && repeated && !containsBadString)
			niceStrings++;
	}

	std::cout << "Part 1: " << niceStrings << '\n';

	niceStrings = 0;
	input.close();
	input.open("input.txt");
	while (input >> line)
	{
		bool symRepeat{};
		for (std::string::iterator c{line.begin()}; c + 2 != line.end(); c++)
			if (*c == *(c + 2))
			{
				symRepeat = true;
				break;
			}

		bool pairRepeat{};
		for (size_t i{}; i + 1 != line.size(); i++)
		{
			std::string pair{ line.substr(i, 2) };
			if (line.find(pair, i + 2) != std::string::npos)
			{
				pairRepeat = true;
				break;
			}
		}

		if (symRepeat && pairRepeat)
			niceStrings++;
	}

	std::cout << "Part 2: " << niceStrings << '\n';

	return 0;
}