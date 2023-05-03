#include <iostream>
#include <fstream>
#include <string>

bool getNextPassword(std::string& old)
{
	for (std::string::iterator c{ old.begin() }; c != old.end(); c++)
		if (*c == 'i' || *c == 'o' || *c == 'l')
		{
			(*c)++;
			if (c + 1 == old.end()) break;
			for (std::string::iterator d{ c + 1 }; d != old.end(); d++)
				*d = 'a';
			break;
		}

	for (std::string::reverse_iterator c{ old.rbegin() }; c != old.rend(); c++)
		if (*c == 'z') *c = 'a';
		else { (*c)++; break; }

	for (std::string::iterator c{ old.begin() }; c + 2 != old.end(); c++)
		if (*c == *(c + 1) - 1 && *c == *(c + 2) - 2) break;
		else if (c + 2 == old.end() - 1) return false;

	if (std::find(old.begin(), old.end(), 'i') != old.end())
		return false;
	if (std::find(old.begin(), old.end(), 'o') != old.end())
		return false;
	if (std::find(old.begin(), old.end(), 'l') != old.end())
		return false;

	char pair{};
	int numPairs{};
	for (std::string::iterator c{ old.begin() }; c + 1 != old.end(); c++)
	{
		if (*c == pair) continue;
		else if (*c == *(c + 1)) { numPairs++; pair = *c; }
	}
	if (numPairs < 2) return false;

	return true;
}

int main()
{
	std::ifstream input{ "input.txt" };
	std::string password{};
	std::getline(input, password);
	
	while (!getNextPassword(password));

	std::cout << "Part 1: " << password << "\n\n";

	while (!getNextPassword(password));

	std::cout << "Part 2: " << password << "\n\n";

	return 0;
}