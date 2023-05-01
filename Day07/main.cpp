#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Wire
{
	std::string id{};
	std::string gate{};
	Wire* A{};
	Wire* B{};
	unsigned short imm{};

	bool operator==(const std::string& str) const
	{
		return str == id;
	}

	unsigned short in()
	{
		unsigned short inA{ A ? A->in() : imm };
		unsigned short inB{ B ? B->in() : imm };
		if (gate == "AND") return inA & inB;
		if (gate == "OR") return inA | inB;
		if (gate == "NOT") return ~inA;
		if (gate == "LSHIFT") return inA << inB;
		if (gate == "RSHIFT") return inA >> inB;
		return inA;
	}
};

std::string gates[5]{ "AND", "OR", "NOT", "LSHIFT", "RSHIFT" };

int main()
{
	std::vector<std::vector<std::string>> instructions{};
	std::ifstream input{ "input.txt" };
	std::string line{};
	std::vector<Wire> circuit{};
	while (std::getline(input, line))
	{
		std::vector<std::string> args(1);
		for (const char& c : line)
			switch (c)
			{
			case ' ':
				if (!args.back().empty())
					args.push_back("");
				break;
			case '-': case '>': break;
			default:
				args.back().push_back(c);
			}
		instructions.push_back(args);
		circuit.push_back({ args.back() });
		for (const std::string& gate : gates)
			if (std::find(args.begin(), args.end(), gate) != args.end())
			{
				circuit.back().gate = gate;
				break;
			}
	}

	for (std::vector<std::string>& instruction : instructions)
	{
		std::vector<Wire>::iterator wire{ std::find(circuit.begin(), circuit.end(), instruction.back()) };
		for (std::vector<std::string>::iterator arg{ instruction.begin() }; arg != instruction.end(); arg++)
		{
			if (*arg == instruction.back()) break;
			if (std::find(gates, gates + 5, *arg) != gates + 5) continue;
			try
			{
				unsigned short num{ static_cast<unsigned short>(std::stoi(*arg)) };
				wire->imm = num;
			}
			catch (...)
			{
				std::vector<Wire>::iterator pos{ std::find(circuit.begin(), circuit.end(), *arg) };
				if (!wire->A)
					wire->A = &(*pos);
				else
					wire->B = &(*pos);
			}
		}
	}

	std::vector<Wire>::iterator a{ std::find(circuit.begin(), circuit.end(), "i") };
	std::cout << "Part 1: " << a->in() << "\n\n";

	return 0;
}