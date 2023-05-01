#include <iostream>
#include <fstream>

struct Light
{
	bool status{};

	void toggle() { status = !status; }
	void on() { status = true; }
	void off() { status = false; }
};

Light lights[1000][1000]{};

int main()
{
	std::ifstream input{ "input.txt" };
	std::string instruction{};
	while (input >> instruction)
		if (instruction.find("on"))
		{

		}
		else if (instruction.find("off"))
		{

		}
		else
		{

		}

	return 0;
}