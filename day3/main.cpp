#include <iostream>
#include <fstream>

bool isValidTriangle(int a, int b, int c)
{
	return (a + b) > c
		&& (b + c) > a
		&& (a + c) > b;
}

int part1()
{
	std::ifstream input("input.txt");

	int a, b, c, count = 0;

	while (input >> a >> b >> c)
	{
		if (isValidTriangle(a, b, c))
		{
			count++;
		}
	}

	return count;
}

int part2()
{
	std::ifstream input("input.txt");

	int values[3][3];
	int count = 0;

	while (true)
	{
		for (int i = 0; i < 3; i++)
		{
			if (!(input >> values[i][0] >> values[i][1] >> values[i][2]))
			{
				return count;
			}
		}

		for (int i = 0; i < 3; i++)
		{
			if (isValidTriangle(values[0][i], values[1][i], values[2][i]))
			{
				count++;
			}
		}
	}

	return count;
}

int main()
{
	std::cout << part1() << std::endl;
	std::cout << part2() << std::endl;
}
