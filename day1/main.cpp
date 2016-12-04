#include <algorithm>
#include <vector>
#include <iostream>
#include <numeric>
#include <tuple>
#include <cmath>
#include <unordered_set>

//#define PART2

struct Value
{
	int x;
	int y;
	int angle;

	bool intersected;

	bool operator ==(const Value &other) const
	{
		return other.x == x
			&& other.y == y;
	}
};

struct Hash
{
	size_t operator()(const Value &value) const
	{
		return value.x ^ value.y;
	}
};

Value add(const Value &v1, const Value &v2)
{
	return
	{
		v1.x + v2.x,
		v1.y + v2.y,
		v1.angle + v2.angle,
		v1.intersected || v2.intersected
	};
}

Value step(const Value &v1, const Value &v2)
{
	static std::unordered_set<Value, Hash> visited;

#ifdef PART2
	if (v1.intersected)
	{
		return v1;
	}
#endif

	const auto result = add(v1, v2);
	const auto insertion = visited.insert(result);

	if (!insertion.second)
	{
		return { result.x, result.y, result.angle, true };
	}

	return result;
}

class Instruction
{
	public:
		Instruction(int value, int direction)
			: m_value(value)
			, m_direction(direction)
		{

		}

		Value execute(const Value &coordinate) const
		{
			const int angle = coordinate.angle + m_direction;
			const int x = sin(angle * (M_PI / 2));
			const int y = cos(angle * (M_PI / 2));

			const Value addend = { x, y, 0, false };
			const Value direction = { 0, 0, m_direction, false };

			std::vector<Value> range(m_value);
			std::fill(range.begin(), range.end(), addend);

			const auto &accumulated = std::accumulate(range.begin(), range.end(), coordinate, &step);

			return add(accumulated, direction);
		}

	private:
		int m_value;
		int m_direction;
};

Value move(const Value &value, const Instruction *instruction)
{
	return instruction->execute(value);
}

Instruction *resolve(const std::string &input)
{
	const auto number = input.substr(1);
	const auto steps = std::stoi(number);

	if (input[0] == 'L')
	{
		return new Instruction(steps, -1);
	}

	if (input[0] == 'R')
	{
		return new Instruction(steps, 1);
	}

	return nullptr;
}

int main()
{
	const std::vector<std::string> input = { "L2", "L3", "L3", "L4", "R1", "R2", "L3", "R3", "R3", "L1", "L3", "R2", "R3", "L3", "R4", "R3", "R3", "L1", "L4", "R4", "L2", "R5", "R1", "L5", "R1", "R3", "L5", "R2", "L2", "R2", "R1", "L1", "L3", "L3", "R4", "R5", "R4", "L1", "L189", "L2", "R2", "L5", "R5", "R45", "L3", "R4", "R77", "L1", "R1", "R194", "R2", "L5", "L3", "L2", "L1", "R5", "L3", "L3", "L5", "L5", "L5", "R2", "L1", "L2", "L3", "R2", "R5", "R4", "L2", "R3", "R5", "L2", "L2", "R3", "L3", "L2", "L1", "L3", "R5", "R4", "R3", "R2", "L1", "R2", "L5", "R4", "L5", "L4", "R4", "L2", "R5", "L3", "L2", "R4", "L1", "L2", "R2", "R3", "L2", "L5", "R1", "R1", "R3", "R4", "R1", "R2", "R4", "R5", "L3", "L5", "L3", "L3", "R5", "R4", "R1", "L3", "R1", "L3", "R3", "R3", "R3", "L1", "R3", "R4", "L5", "L3", "L1", "L5", "L4", "R4", "R1", "L4", "R3", "R3", "R5", "R4", "R3", "R3", "L1", "L2", "R1", "L4", "L4", "L3", "L4", "L3", "L5", "R2", "R4", "L2" };

	std::vector<Instruction *> instructions(input.size());
	std::transform(input.begin(), input.end(), instructions.begin(), &resolve);

	const Value initial = { 0, 0, 0, false };
	const Value coordinate = std::accumulate(instructions.begin(), instructions.end(), initial, &move);

	std::cout << std::abs(coordinate.x) + std::abs(coordinate.y) << std::endl;
}
