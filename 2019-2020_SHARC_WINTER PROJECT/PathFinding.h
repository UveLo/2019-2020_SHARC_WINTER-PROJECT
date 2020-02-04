#pragma once

#include "Elements.h"
#include <iostream>
#include <string>
#include <stack>
#include <queue>
#include <vector>

class PathFinding{

public:
	//Input departure station
	void input_dep();
	//Input arrival station
	void input_arr();

public:
	void RESET();
	int A_star();
	int Dijkstra();
	

public:
	void print_route();
	void print_findedPath();
	void print_findedPathN();

};

