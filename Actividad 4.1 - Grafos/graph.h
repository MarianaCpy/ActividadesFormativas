#ifndef GRAPH_H_
#define	GRAPH_H_

#include <stack>
#include <queue>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <iterator>

using namespace std;

class Graph {
private:
	int n;
	int m;
	int eList;
	int eMat;
	string resp;
	string r;
	string fname;
	int* AdjMat;
	vector <int>* AdjList;

	void getData();
	void swap(vector<int>& vect, int i, int j);
	void sortList();
	void selectionSort(vector<int>& vect);
	void addEadjList(int, int);
	void addEadjMat(int, int);
	string printDFS(bool visited[], int f, int m, int parent[], vector <int>& cam);
	string printBFS(bool visit[], int f, int m, int parent[], int cam[], vector <int> VIO);
	void DFShel(int f, int initial, int m, bool visited[], int parent[], stack <int>& s, vector <int>& cam);
	void BFShel(int f, int initial, int m, bool visited[], int parent[], queue <int>& q, int cam[], vector <int> VIO);

public:
	void loadGraphMat(string, int, int);
	void loadGraphList(string, int, int);
	string BFS(int, int);
	string DFS(int, int);
	string printAdjMat();
	string printAdjList();
};

void Graph::swap(vector<int>& vect, int i, int j) {
	int sus = vect[i];
	vect[i] = vect[j];
	vect[j] = sus;
}

void Graph::selectionSort(vector<int>& vect) {
	int band;

	for (int i = vect.size() - 1; i > 0; i--) {
		band = 0;
		for (int j = 1; j <= i; j++) {
			if (vect[j] > vect[band]) {
				band = j;
			}
		}

		if (band != i) {
			swap(vect, i, band);
		}
	}
}

void Graph::sortList() {
	for (int i = 0; i < n; i++)
		selectionSort(AdjList[i]);
}

void Graph::addEadjMat(int vertex, int arch) {
	AdjMat[arch * n + vertex] = 1;
	AdjMat[vertex * n + arch] = 1;
	eMat++;
}

void Graph::addEadjList(int n, int m) {
	AdjList[n].push_back(m);
	AdjList[m].push_back(n);
	eList++;
}

void Graph::getData() {
	string begin;
	string after;
	int m;
	int n;
	string word;

	ifstream infile(fname);
	if (infile.is_open()) {
		int i = 0;
		while (getline(infile, word)) {
			begin = word.substr(1);
			after = word.substr(4);
			m = stoi(begin);
			n = stoi(after);
			addEadjMat(m, n);
			addEadjList(m, n);
			i++;
		}
		infile.close();
	}
	sortList();
}

void Graph::loadGraphMat(string f, int vertex, int arch) {
	fname = f;
	n = vertex;
	m = arch;
	eMat = 0;
	AdjMat = new int[n * m];

	for (int i = 0; i < n * m;i++) {
		AdjMat[i] = 0;
	}

	getData();
}

void Graph::loadGraphList(string f, int nodes, int vertex) {
	fname = f;
	n = nodes;
	m = vertex;
	AdjList = new vector<int>[nodes];
	eList = 0;
}

string Graph::printBFS(bool visit[], int f, int m, int parent[], int cam[], vector <int> VIO) {
	string pBFS = "visited: ";
	for (int i = 0; i < VIO.size();i++) {
		pBFS = pBFS + to_string(VIO[i]);
		pBFS = pBFS + " ";
	}
	pBFS = pBFS + "path:";
	vector <int> a;
	a.push_back(m);
	while (m != f) {
		a.push_back(parent[m]);
		m = parent[m];
	}

	for (int i = a.size() - 1; i >= 0; i--) {
		pBFS = pBFS + " ";
		pBFS = pBFS + to_string(a[i]);
	}
	return pBFS;
}

string Graph::printDFS(bool visited[], int f, int m, int parent[], vector <int>& cam) {
	string pDFS = "visited: ";
	for (int i = 0; i < cam.size() - 1;i++) {
		pDFS = pDFS + to_string(cam[i]);
		pDFS = pDFS + " ";
	}
	pDFS = pDFS + "path:";
	vector <int> a;
	a.push_back(m);
	while (m != f) {
		a.push_back(parent[m]);
		m = parent[m];
	}

	for (int i = a.size() - 1; i >= 0; i--) {
		pDFS = pDFS + " ";
		pDFS = pDFS + to_string(a[i]);
	}
	return pDFS;
}

void Graph::BFShel(int f, int initial, int m, bool visit[], int parent[], queue <int>& q, int cam[], vector <int> VIO) {
	if (initial == m)
		r = printBFS(visit, f, m, parent, cam, VIO);

	else if (q.empty())

		cout << "BSF Not Found";

	else {
		initial = q.front();
		q.pop();
		visit[initial] = true;
		VIO.push_back(initial);
		for (int i = 0; i < AdjList[initial].size();i++) {
			if (!visit[AdjList[initial][i]]) {
				q.push(AdjList[initial][i]);
				if (cam[AdjList[initial][i]] == -1) {
					cam[AdjList[initial][i]] = initial;
					parent[AdjList[initial][i]] = initial;
				}
			}
		}
		BFShel(f, initial, m, visit, parent, q, cam, VIO);
	}
}

void Graph::DFShel(int f, int initial, int m, bool visited[], int parent[], stack <int>& s, vector <int>& cam) {
	if (initial == m) {
		resp = printDFS(visited, f, m, parent, cam);
	}

	else if (s.empty()) {
		cout << "DFS Not Found";
	}

	else {
		parent[s.top()] = initial;
		initial = s.top();
		s.pop();
		visited[initial] = true;
		for (int i = 0; i < AdjList[initial].size();i++) {
			if (!visited[AdjList[initial][i]]) {
				s.push(AdjList[initial][i]);
				cam.push_back(AdjList[initial][i]);
				DFShel(f, initial, m, visited, parent, s, cam);
			}
		}
	}
}

string Graph::BFS(int inicial, int meta) {
	vector <int> VIO;
	queue <int> q;
	bool* visit = new bool[n];
	int* cam = new int[n];
	int* parent = new int[n];
	int f = inicial;
	cam[0] = inicial;
	q.push(f);

	for (int i = 0; i < n; i++) {
		visit[i] = false;
	}

	for (int i = 0; i < n; i++) {
		parent[i] = false;
	}

	for (int i = 0; i < n; i++) {
		cam[i] = -1;
	}

	BFShel(f, inicial, meta, visit, parent, q, cam, VIO);
	return r;
}

string Graph::DFS(int inicial, int meta) {
	vector <int> cam;
	stack <int> s;
	bool* visited = new bool[n];
	int* parent = new int[n];
	int f = inicial;
	s.push(f);
	cam.push_back(inicial);

	for (int i = 0; i < n; i++) {
		visited[i] = false;
	}

	for (int i = 0; i < n; i++) {
		parent[i] = false;
	}

	DFShel(f, inicial, meta, visited, parent, s, cam);
	return resp;
}

string Graph::printAdjList() {
	int num;
	string AdjL;
	string str;

	for (int i = 0;i < n;i++) {
		AdjL = AdjL + "vertex ";
		AdjL = AdjL + to_string(i);
		AdjL = AdjL + " : ";
		for (int k = 0; k < AdjList[i].size();k++) {
			int num = AdjList[i][k];
			string str = to_string(num);
			AdjL = AdjL + str;
			AdjL = AdjL + " ";
		}
	}
	return AdjL;
}

string Graph::printAdjMat() {
	string pAdjM;
	int num;
	string str;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			int num = AdjMat[i * n + j];
			string str = to_string(num);
			pAdjM = pAdjM + str;
			pAdjM = pAdjM + " ";
		}
	}
	return pAdjM;
}

#endif
