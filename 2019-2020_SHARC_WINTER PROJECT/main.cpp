#include "LoadData.h"
#include "PathFinding.h"

using namespace std;

int main() {
	LoadData loadData;
	PathFinding pathFinding;

	loadData.Load_Edge();
	loadData.Load_Node();
	
	//loadData.Print_NodeInfo();
	//loadData.Print_EdgeInfo();

	pathFinding.input_dep();
	pathFinding.input_arr();

	pathFinding.RESET();
	if (pathFinding.A_star()) return 0;
	pathFinding.print_route();
	pathFinding.print_findedPath();
	pathFinding.print_findedPathN();

	pathFinding.RESET();
	if (pathFinding.Dijkstra()) return 0;
	pathFinding.print_route();
	pathFinding.print_findedPath();
	pathFinding.print_findedPathN();
}