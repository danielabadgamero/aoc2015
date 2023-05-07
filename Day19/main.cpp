#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>

std::unordered_map<std::string, std::vector<std::string>> replacements{};
std::string molecule{};
std::unordered_set<std::string> molecules{};

int main()
{
	bool replacementsDone{};
	std::ifstream input{ "input.txt" };
	std::string line{};
	while (std::getline(input, line))
	{
		if (line.empty()) replacementsDone = true;
		else if (!replacementsDone)
			replacements[line.substr(0, line.find('=') - 1)].push_back(line.substr(line.find('>') + 2));
		else molecule = line;
	}
	
	for (std::unordered_map<std::string, std::vector<std::string>>::iterator rep{ replacements.begin() }; rep != replacements.end(); rep++)
	{
		size_t pos{};
		while ((pos = molecule.find(rep->first, pos)) != std::string::npos)
		{
			std::string newMolecule{ molecule };
			newMolecule.erase(pos, rep->first.length());
			for (int i{}; i != rep->second.size(); i++)
			{
				std::string tmpMolecule{ newMolecule };
				tmpMolecule.insert(pos, rep->second[i]);
				molecules.emplace(tmpMolecule);
			}
			pos++;
		}
	}

	std::cout << "Part 1: " << molecules.size() << "\n\n";

	return 0;
}