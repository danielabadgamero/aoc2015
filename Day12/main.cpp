#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::string> getElements(const std::string& parent)
{
	std::vector<std::string> elements(1);
	int nestLevel{};
	for (size_t i{}; i != parent.size(); i++)
	{
		switch (parent[i])
		{
		case '[': case '{': nestLevel++; break;
		case ']': case '}': nestLevel--; break;
		}
		if (parent[i] == ',' && nestLevel == 1)
			elements.push_back("");
		else if (i != 0 && i + 1 != parent.size())
			elements.back().push_back(parent[i]);
	}

	return elements;
}

int add(const std::string& obj)
{
	int sum{};
	std::vector<std::string> elements{ getElements(obj) };
	for (const std::string& elem : elements)
	{
		if (elem[0] != '{' && elem[0] != '[')
		{
			if (elem.back() == ']' || elem.back() == '}')
				sum += add(elem.substr(elem.find(':') + 1));
			else if (elem.find(":\"red\"") != std::string::npos)
				return 0;
			try
			{
				sum += std::stoi(elem.substr(elem.find(':') + 1));
			}
			catch (...) {}
		}
		else
			sum += add(elem);
	}

	return sum;
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
	pos = line.find("\"red\"", pos + 1);
	numBuf.clear();

	std::cout << "Part 2: " << add(line) << "\n\n";

	return 0;
}