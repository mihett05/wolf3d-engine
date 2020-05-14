#include "utils.h"

using namespace std;

float getSin(float angle, map<float, float> sinTable)
{
	map<float, float>::iterator res = sinTable.find(angle);
	if (res != sinTable.end())
	{
		return res->second;
	}
	else
	{
		float value = sin(angle);
		sinTable.insert(pair<float, float>(angle, value));
		return value;
	}
}

float getCos(float angle, map<float, float> cosTable)
{
	map<float, float>::iterator res = cosTable.find(angle);
	if (res != cosTable.end())
	{
		return res->second;
	}
	else
	{
		float value = cos(angle);
		cosTable.insert(pair<float, float>(angle, value));
		return value;
	}
}