#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Ingredient
{
	int capacity{};
	int durability{};
	int flavor{};
	int texture{};
	int calories{};
};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string line{};
	std::vector<Ingredient> ingredients{};
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			if (c == ' ') args.push_back("");
			else args.back().push_back(c);
		ingredients.push_back({ std::stoi(args[2]), std::stoi(args[4]), std::stoi(args[6]), std::stoi(args[8]), std::stoi(args[10]) });
	}

	uint64_t maxScore{};
	for (int a{}; a <= 100; a++)
		for (int b{}; a + b <= 100; b++)
			for (int c{}; a + b + c <= 100; c++)
			{
				int d{ 100 - (a + b + c) };
				int totalCapacity{ ingredients[0].capacity * a + ingredients[1].capacity * b + ingredients[2].capacity * c + ingredients[3].capacity * d };
				int totalDurability{ ingredients[0].durability * a + ingredients[1].durability * b + ingredients[2].durability * c + ingredients[3].durability * d };
				int totalFlavor{ ingredients[0].flavor * a + ingredients[1].flavor * b + ingredients[2].flavor * c + ingredients[3].flavor * d };
				int totalTexture{ ingredients[0].texture * a + ingredients[1].texture * b + ingredients[2].texture * c + ingredients[3].texture * d };
				if (totalCapacity < 0) totalCapacity = 0;
				if (totalDurability < 0) totalDurability = 0;
				if (totalFlavor < 0) totalFlavor = 0;
				if (totalTexture < 0) totalTexture = 0;
				uint64_t score{ static_cast<uint64_t>(totalCapacity * totalDurability * totalFlavor * totalTexture) };
				if (score > maxScore)
					maxScore = score;
			}

	std::cout << "Part 1: " << maxScore << "\n\n";

	maxScore = 0;
	for (int a{}; a <= 100; a++)
		for (int b{}; a + b <= 100; b++)
			for (int c{}; a + b + c <= 100; c++)
			{
				int d{ 100 - (a + b + c) };
				int totalCapacity{ ingredients[0].capacity * a + ingredients[1].capacity * b + ingredients[2].capacity * c + ingredients[3].capacity * d };
				int totalDurability{ ingredients[0].durability * a + ingredients[1].durability * b + ingredients[2].durability * c + ingredients[3].durability * d };
				int totalFlavor{ ingredients[0].flavor * a + ingredients[1].flavor * b + ingredients[2].flavor * c + ingredients[3].flavor * d };
				int totalTexture{ ingredients[0].texture * a + ingredients[1].texture * b + ingredients[2].texture * c + ingredients[3].texture * d };
				int totalCalories{ ingredients[0].calories * a + ingredients[1].calories * b + ingredients[2].calories * c + ingredients[3].calories * d };
				if (totalCapacity < 0) totalCapacity = 0;
				if (totalDurability < 0) totalDurability = 0;
				if (totalFlavor < 0) totalFlavor = 0;
				if (totalTexture < 0) totalTexture = 0;
				uint64_t score{ static_cast<uint64_t>(totalCapacity * totalDurability * totalFlavor * totalTexture) };
				if (score > maxScore && totalCalories == 500)
					maxScore = score;
			}

	std::cout << "Part 2: " << maxScore << "\n\n";

	return 0;
}