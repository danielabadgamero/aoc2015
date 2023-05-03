#include <iostream>
#include <fstream>
#include <string>
#include <vector>

static bool insideArray(size_t pos, std::string& obj)
{

}

int main()
{
	std::ifstream input{ "input.txt" };
	char c{};
	std::string numBuf{};
	int sum{};
	while (!input.eof())
	{
		input.read(&c, 1);
		if (c >= '0' && c <= '9' || c == '-') numBuf.push_back(c);
		else if (!numBuf.empty())
		{
			sum += std::stoi(numBuf);
			numBuf.clear();
		}
	}

	std::cout << "Part 1: " << sum << "\n\n";

	input.close();
	input.open("input.txt");
	std::string line{};
	input >> line;

	size_t pos{};
	while (pos != std::string::npos)
	{
		int nestLevel{};
		pos = line.find("\"red\"", pos + 1);
		if (insideArray(pos, line))
	}

	std::cout << "Part 2: " << sum << "\n\n";

	return 0;
}