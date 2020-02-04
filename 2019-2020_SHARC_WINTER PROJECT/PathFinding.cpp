#include "Setting.h"
#include "Elements.h"
#include "PathFinding.h"

using namespace std;

//Departure Station
string dep;
//Arrival Station
string arr;

typedef struct Dist {
	double dist = 10000000;
};

struct cmp {
	bool operator()(Elements::Stationi a, Elements::Stationi b) {
		if (a.distance == b.distance)
			return a.name >= b.name;
		else
			return a.distance > b.distance;
	}
};

typedef priority_queue<Elements::Stationi, vector<Elements::Stationi>, cmp> AQueue;
AQueue pq;
queue<string> finded;
map<string, string> backtrack;
map<string, Dist> cumDist;

double ndist;

void PathFinding::input_dep(){
	do {
		cout << "출발역 입력: ";
		cin >> dep;
	} while (Elements::mtr.find(dep) == Elements::mtr.end());
}

void PathFinding::input_arr(){
	do {
		cout << "도착역 입력: ";
		cin >> arr;
	} while (Elements::mtr.find(arr) == Elements::mtr.end());
}

void PathFinding::RESET() {
	AQueue init_pq;
	queue<string> init_finded;
	map<string, string> init_backtrack;
	map<string, Dist> init_cumDist;
	swap(init_pq, pq);
	swap(init_finded, finded);
	swap(init_backtrack, backtrack);
	swap(init_cumDist, cumDist);
}

double heuri(Elements::Stationi n) {
	double x = Elements::mtr[n.name].x - Elements::mtr[arr].x;
	x *= 88237;
	x *= x;
	double y = Elements::mtr[n.name].y - Elements::mtr[arr].y;
	y *= 111319;
	y *= y;

	return sqrt(x + y);
}

int PathFinding::A_star(){
	cumDist[dep].dist = 0;
	pq.push({ dep, 0 });
	while (!pq.empty()) {
		Elements::Stationi now = pq.top();
		pq.pop();

		int sibal = 0;
		bool isarrived = false;
		for (auto i : Elements::mtr[now.name].linked_station) {
			sibal++;
			double nxtdist = cumDist[now.name].dist + i.second.distance;
			if (cumDist[i.second.name].dist > nxtdist) {
				if(cumDist[i.second.name].dist == 10000000)
					finded.push(i.second.name);
				cumDist[i.second.name].dist = nxtdist;
				pq.push({ i.second.name, (nxtdist + heuri(i.second)) });
				backtrack[i.second.name] = now.name;
				if (i.second.name == arr)
					return 0;
			}
		}
	}
	cout << "경로를 찾을 수 없습니다.\n";
	return -1;
}

int PathFinding::Dijkstra() {
	cumDist[dep].dist = 0;
	pq.push({ dep, 0 });
	while (!pq.empty()) {
		Elements::Stationi now = pq.top();
		pq.pop();

		int sibal = 0;
		bool isarrived = false;
		for (auto i : Elements::mtr[now.name].linked_station) {
			sibal++;
			double nxtdist = cumDist[now.name].dist + i.second.distance;
			if (cumDist[i.second.name].dist > nxtdist) {
				if (cumDist[i.second.name].dist == 10000000)
					finded.push(i.second.name);
				cumDist[i.second.name].dist = nxtdist;
				pq.push({ i.second.name, (nxtdist) });
				backtrack[i.second.name] = now.name;
				if (i.second.name == arr)
					return 0;
			}
		}
	}
	cout << "경로를 찾을 수 없습니다.\n";
	return -1;
}

void PathFinding::print_route(){
	stack<string> st;
	string a = arr;
	st.push(arr);

	while (a != dep) {
		st.push(backtrack[a]);
		a = backtrack[a];
	}
	cout << st.top();
	st.pop();
	while (!st.empty()) {
		cout << "-" << st.top();
		st.pop();
	}
	cout << endl;
}

void PathFinding::print_findedPath(){
	queue<string> Lq;
	Lq = finded;
	cout << Lq.front();
	Lq.pop();
	while (!Lq.empty()) {
		cout << ", " << Lq.front();
		Lq.pop();
	}
	cout << endl;
}

void PathFinding::print_findedPathN(){
	int Lcnt = 0;
	queue<string> Lq;
	Lq = finded;
	while (!Lq.empty()) {
		Lcnt++;
		Lq.pop();
	}
	cout << Lcnt << endl;
}
