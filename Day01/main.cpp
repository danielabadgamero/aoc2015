#include <iostream>
#include <fstream>

int main()
{
	std::ifstream input{ "input.txt" };
	int floor{};
	bool found{};
	int pos{};
	while (!input.eof())
	{
		if (!found)
			pos++;
		char c{};
		input.read(&c, 1);
		if (c == '(') floor++;
		if (c == ')') floor--;
		if (floor == -1) found = true;
	}

	std::cout << "Part 1: " << floor << "\n\n";
	std::cout << "Part 1: " << pos << "\n\n";

	return 0;
}