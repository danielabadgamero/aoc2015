#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <unordered_set>
#include <vector>
#include <deque>
#include <queue>

std::unordered_map<std::string, std::vector<std::string>> replacements{};
std::string molecule{};
std::unordered_set<std::string> molecules{};
struct Molecule;
std::deque<Molecule*> queue{};
std::queue<Molecule*> archived{};

void replace(std::unordered_map<std::string, std::vector<std::string>>::iterator rep, std::string change = molecule)
{
	size_t pos{};
	while ((pos = change.find(rep->first, pos)) != std::string::npos)
	{
		std::string newMolecule{ change };
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

Molecule* result{};
struct Molecule
{
	std::string id{};
	Molecule* parent{};

	void createMolecule()
	{
		if (id == molecule)
		{
			queue.clear();
			result = parent;
			return;
		}
		for (std::unordered_map<std::string, std::vector<std::string>>::iterator rep{ replacements.begin() }; rep != replacements.end(); rep++)
		{
			size_t pos{};
			while ((pos = id.find(rep->first, pos)) != std::string::npos)
			{
				std::string newMolecule{ id };
				newMolecule.erase(pos, rep->first.length());
				for (int i{}; i != rep->second.size(); i++)
				{
					std::string tmpMolecule{ newMolecule };
					tmpMolecule.insert(pos, rep->second[i]);
					if (std::find_if(queue.begin(), queue.end(), [&](Molecule* m) { return m->id == tmpMolecule; }) == queue.end())
						queue.push_back(new Molecule{ tmpMolecule, this });
				}
				pos++;
			}
		}

		while (!queue.empty())
		{
			archived.push(queue.front());
			queue.pop_front();
			archived.back()->createMolecule();
		}
	}
};

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
		replace(rep);

	std::cout << "Part 1: " << molecules.size() << "\n\n";

	molecules.clear();
	Molecule start{ "e" };
	start.createMolecule();
	int steps{};
	while (result)
	{
		steps++;
		result = result->parent;
	}

	std::cout << "Part 2: " << steps << "\n\n";

	return 0;
}