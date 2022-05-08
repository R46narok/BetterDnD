#pragma once

#include <string>
#include <sstream>
#include <random>

int random_number(int maxValue)
{
	int random = rand() % maxValue + 1;
	return random;
}

int random_numberHardware(int value)
{
	std::random_device rd;
	std::mt19937 eng(rd());
	std::uniform_int_distribution<> distr(1, value);

	return distr(eng);
}

int StatMod;
int StatsTransform(int Stat)
{

	if (Stat == 1)
		StatMod = -5;
	if (Stat == 2 || Stat == 3)
		StatMod = -4;
	if (Stat == 4 || Stat == 5)
		StatMod = -3;
	if (Stat == 6 || Stat == 7)
		StatMod = -2;
	if (Stat == 8 || Stat == 9)
		StatMod = -1;
	if (Stat == 10 || Stat == 11)
		StatMod = 0;
	if (Stat == 12 || Stat == 13)
		StatMod = 1;
	if (Stat == 14 || Stat == 15)
		StatMod = 2;
	if (Stat == 16 || Stat == 17)
		StatMod = 3;
	if (Stat == 18 || Stat == 19)
		StatMod = 4;
	if (Stat == 20 || Stat == 21)
		StatMod = 5;
	if (Stat == 22 || Stat == 23)
		StatMod = 6;
	if (Stat == 24 || Stat == 25)
		StatMod = 7;
	if (Stat == 26 || Stat == 27)
		StatMod = 8;
	if (Stat == 28 || Stat == 29)
		StatMod = 9;
	if (Stat == 30)
		StatMod = 10;
	return StatMod;
}

int dieTransformerSum;

int dieTransformer(std::string Die)
{
	const char* die = Die.c_str();
	int dIndex;

	dieTransformerSum = 0;

	for (int i = 0; i < Die.length(); i++)
	{
		if (die[i] == 'd')
		{
			dIndex = i;
			break;
		}
	}
	
	std::string times;
	for (int i = 0; i < dIndex; i++)
	{
		times += die[i];
	}

	std::string by;
	for (int i = dIndex+1; i < Die.length(); i++)
	{
		by += die[i];
	}

	int Times;
	std::istringstream ss(times);
	ss >> Times;

	int By;
	std::istringstream ss1(by);
	ss1 >> By;

	for (int i = 1; i <= Times; i++)
	{
		dieTransformerSum += random_numberHardware(By);
	}

	return dieTransformerSum;
}

int brIndex;
int monsterDieTransfromer(std::string Hp, bool fixedValue)
{
	const char* hp = Hp.c_str();
	int dIndex;

	dieTransformerSum = 0;

	for (int i = 0; i < Hp.length(); i++)
	{
		if (hp[i] == '(')
		{
			brIndex = i;
			break;
		}
	}

	if (fixedValue)
	{
		int i2;
		std::string str;
		for (int j = 0; j < brIndex; j++)
		{
			str += hp[j];
		}

		std::istringstream ss2(str);
		ss2 >> i2;
		return i2;
	}
	else
	{
		Hp.erase(0, brIndex + 1);
		Hp.erase(Hp.size()-1, 1);


		for (int i = 0; i < Hp.length(); i++)
		{
			if (hp[i] == 'd')
			{
				dIndex = i;
				break;
			}
		}
		std::string times;
		for (int i = 0; i < dIndex; i++)
		{
			times += hp[i];
		}

		std::string by;
		for (int i = dIndex + 1; i < Hp.length(); i++)
		{
			by += hp[i];
		}

		int Times;
		std::istringstream ss(times);
		ss >> Times;

		int By;
		std::istringstream ss1(by);
		ss1 >> By;

		for (int i = 1; i <= Times; i++)
		{
			dieTransformerSum += random_numberHardware(By);
		}


		return dieTransformerSum;
	}
	
}