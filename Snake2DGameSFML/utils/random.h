#pragma once
#include <random>

class Random;
static Random* randomInstance;

class Random
{
private:
	Random()
	{
		gen.seed(randomDevice());
	}

public:

	~Random() = default;

	int getRandomInt(int minInt, int maxNumber)
	{
		const std::uniform_int_distribution<int> dist(minInt, maxNumber);
		return dist(gen);
	}

	static Random* getInstance()
	{
		if (randomInstance == nullptr)
			randomInstance = new Random;
		return randomInstance;
	}

private:
	std::mt19937 gen;
	std::random_device randomDevice;
};
