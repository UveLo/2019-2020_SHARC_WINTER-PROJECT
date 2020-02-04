#pragma once

#include <sstream>
#include <istream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;


class Elements{

public:
	typedef struct Stationi{
		string name = "";
		double distance = 2147483647;
	};

	typedef struct Station{
		string name = "";
		double x = 0, y = 0;

		map<string, Stationi> linked_station;
	};

	static map<string, Station> mtr;

};

