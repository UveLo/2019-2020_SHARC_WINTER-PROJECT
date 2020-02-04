#include "Setting.h"
#include "Elements.h"
#include "LoadData.h"

using namespace std;

vector<string> csv_read_row(istream& file_node, char delimiter)
{
	stringstream ss;
	bool inquotes = false;
	vector<string> row; //relying on RVO

	while (file_node.good())
	{
		char c = file_node.get();
		if (!inquotes && c == '"')
		{
			inquotes = true;
		}
		else if (inquotes && c == '"')
		{
			if (file_node.peek() == '"')
			{
				ss << (char)file_node.get();
			}

			else
			{
				inquotes = false;
			}
		}

		else if (!inquotes && c == delimiter)
		{
			row.push_back(ss.str());
			ss.str("");
		}

		else if (!inquotes && (c == '\r' || c == '\n'))
		{
			if (file_node.peek() == '\n') { file_node.get(); }
			row.push_back(ss.str());
			return row;
		}

		else
		{
			ss << c;
		}
	}
	//?
	return row;
}

void LoadData::Load_Node(){
	ifstream file_node(address_nodeCSVfile);

	if (file_node.fail()) {
		cout << "파일로딩 실패";
		return;
	}

	while (file_node.good()) //eof, bad, fail 함수가 거짓의 참을 반환할 때까지..
	{
		string name;
		double x = 0;
		double y = 0;
		vector<string> row = csv_read_row(file_node, ',');

		if (!row[0].find("#"))
		{
			continue;
		}
		else
		{
			for (double i = 0, leng = row.size(); i < leng; i++)
			{
				if (i == 1)
					name = row[i];
				else if (i == 7 && row[i] != "")
					x = stod(row[i]);
				else if (i == 8 && row[i] != "")
					y = stod(row[i]);

			}
			Elements::mtr[name].name = name;
			if (x)
				Elements::mtr[name].x = x;
			if (y)
				Elements::mtr[name].y = y;
		}

	}
	file_node.close();
}

void LoadData::Load_Edge(){
	ifstream file_edge(address_EdgeCSVfile);

	if (file_edge.fail()) {
		cout << "파일로딩 실패";
		return;
	}

	while (file_edge.good()) //eof, bad, fail 함수가 거짓의 참을 반환할 때까지..
	{
		string a;
		string b;
		double distance = 0;
		vector<string> row = csv_read_row(file_edge, ',');

		if (!row[0].find("#"))
		{
			continue;
		}
		else
		{
			for (double i = 0, leng = row.size() - 1; i < leng; i++)
			{
				if (i == 0)a = row[i];
				else if (i == 1)b = row[i];
				else if (i == 2)distance = stod(row[i]);

			}
			Elements::mtr[a].linked_station[b].name = b;
			Elements::mtr[a].linked_station[b].distance = distance;
			Elements::mtr[b].linked_station[a].name = a;
			Elements::mtr[b].linked_station[a].distance = distance;
		}

	}
	file_edge.close();
}

void LoadData::Print_NodeInfo(){
	for (auto i : Elements::mtr) {
		cout << "역:" << i.second.name << " x좌표:" << i.second.x << " y좌표:" << i.second.y << endl;
	}
}

void LoadData::Print_EdgeInfo() {
	for (auto i : Elements::mtr) {
		cout << "역:" << i.second.name;
		for (auto j : i.second.linked_station) {
			cout << "\n도착지: " << j.second.name << " 거리:" << j.second.distance;
		}
		cout << endl;
	}
}