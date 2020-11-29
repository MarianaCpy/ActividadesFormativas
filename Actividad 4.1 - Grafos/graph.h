#ifndef GRAPH_H_
#define GRAPH_H_

#include <string>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>
#include <stack>
#include <queue>

using namespace std;

class Graph {
private:
    int nodes;
    int connections;
    vector <int>* adjList;
    int* adjMatrix;
    string fileName;
    void readFile();
    int edjesList;
    int edjesMat;
    string result;
    string res;
    void addEdjeAdjList(int u, int v);
    void addEdjeAdjMat(int u, int v);
    void sortAdjList();
    void ordenaSeleccion(vector<int>& v);
    void swapArray(vector<int>& v, int i, int j);

    string printDFS(bool visited[], int first, int goal, int parent[], vector <int>& path);
    string printBFS(bool visit[], int first, int goal, int parent[], int path[], vector <int> visitedInOrder);
    void DFShelper(int first, int current, int goal, bool visited[], int parent[], stack <int>& stack, vector <int>& path);
    void BFShelper(int first, int current, int goal, bool visited[], int parent[], queue <int>& queue, int path[], vector <int> visitedInOrder);

public:
    void loadGraphMat(string f, int n, int c);
    void loadGraphList(string f, int n, int c);
    string printAdjList();
    string printAdjMat();
    string DFS(int current, int goal);
    string BFS(int current, int goal);
};

void Graph::loadGraphMat(string f, int n, int c) {
    fileName = f;
    nodes = n;
    connections = c;
    edjesMat = 0;
    adjMatrix = new int[nodes * connections];

    for (int i = 0; i < nodes * connections; i++) {
        adjMatrix[i] = 0;
    }

    readFile();
}

void Graph::loadGraphList(string f, int n, int c) {
    fileName = f;
    nodes = n;
    connections = c;
    adjList = new vector <int>[nodes];
    edjesList = 0;
}

void Graph::addEdjeAdjMat(int u, int v) {
    adjMatrix[u * nodes + v] = 1;
    adjMatrix[v * nodes + u] = 1;
    edjesMat++;
}

void Graph::addEdjeAdjList(int u, int v) {
    adjList[u].push_back(v);
    adjList[v].push_back(u);
    edjesList++;
}

void Graph::readFile() {
    string first;
    string second;
    int u;
    int v;
    int iline;
    string line;
    ifstream file(fileName);
    if (file.is_open()) {
        int i = 0;
        while (getline(file, line)) {
            first = line.substr(1);
            second = line.substr(4);
            u = stoi(first);
            v = stoi(second);
            addEdjeAdjMat(u, v);
            addEdjeAdjList(u, v);
            i++;
        }
        file.close();
    }
    sortAdjList();
}

string Graph::printAdjList() {
    string list;
    int number;
    string cadena;
    for (int i = 0; i < nodes; i++) {
        list = list + "vertex ";
        list = list + to_string(i);
        list = list + " : ";
        for (int j = 0; j < adjList[i].size(); j++) {
            int number = adjList[i][j];
            string cadena = to_string(number);
            list = list + cadena;
            list = list + " ";
        }
    }
    return list;
}

string Graph::printAdjMat() {
    string matrix;
    int number;
    string cadena;
    for (int i = 0; i < nodes; i++) {
        for (int j = 0; j < nodes; j++) {
            int number = adjMatrix[i * nodes + j];
            string cadena = to_string(number);
            matrix = matrix + cadena;
            matrix = matrix + " ";
        }
    }
    return matrix;
}

void Graph::sortAdjList() {
    for (int i = 0; i < nodes; i++)
        ordenaSeleccion(adjList[i]);
}

void Graph::ordenaSeleccion(vector<int>& v) {
    for (int i = 0; i < v.size() - 1; i++) {
        int min = i;
        for (int j = i + 1; j < v.size(); j++) {
            if (v[j] < v[min])
                min = j;
        }
        swapArray(v, i, min);
    }
}

void Graph::swapArray(vector<int>& v, int i, int j) {
    int temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}

string Graph::DFS(int current, int goal) {
    int first = current;
    bool* visited = new bool[nodes];
    int* parent = new int[nodes];
    stack <int> stack;
    vector <int> path;
    stack.push(first);
    path.push_back(current);

    for (int i = 0; i < nodes; i++) {
        visited[i] = false;
    }

    for (int i = 0; i < nodes; i++) {
        parent[i] = 0;
    }

    DFShelper(first, current, goal, visited, parent, stack, path);
    return result;
}

void Graph::DFShelper(int first, int current, int goal, bool visited[], int parent[], stack <int>& stack, vector <int>& path) {
    if (current == goal) {
        result = printDFS(visited, first, goal, parent, path);

    }

    else if (stack.empty()) {
        cout << "not found";
    }

    else {
        parent[stack.top()] = current;
        current = stack.top();
        stack.pop();
        visited[current] = true;
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!visited[adjList[current][i]]) {
                stack.push(adjList[current][i]);
                path.push_back(adjList[current][i]);
                DFShelper(first, current, goal, visited, parent, stack, path);
            }


        }
    }


}

string Graph::BFS(int current, int goal) {
    int first = current;
    bool* visit = new bool[nodes];
    int* parent = new int[nodes];
    queue <int> queue;
    int* path = new int[nodes];
    queue.push(first);
    path[0] = current;
    vector <int> visitedInOrder;


    for (int i = 0; i < nodes; i++) {
        visit[i] = false;
    }


    for (int i = 0; i < nodes; i++) {
        parent[i] = false;
    }

    for (int i = 0; i < nodes; i++) {
        path[i] = -1;
    }

    BFShelper(first, current, goal, visit, parent, queue, path, visitedInOrder);
    return res;
}

void Graph::BFShelper(int first, int current, int goal, bool visit[], int parent[], queue <int>& queue, int path[], vector <int> visitedInOrder) {
    if (current == goal)
        res = printBFS(visit, first, goal, parent, path, visitedInOrder);

    else if (queue.empty())
        cout << "not found";

    else {
        current = queue.front();
        queue.pop();
        visit[current] = true;
        visitedInOrder.push_back(current);
        for (int i = 0; i < adjList[current].size(); i++) {
            if (!visit[adjList[current][i]]) {
                queue.push(adjList[current][i]);
                if (path[adjList[current][i]] == -1) {
                    path[adjList[current][i]] = current;
                    parent[adjList[current][i]] = current;
                }
            }
        }
        BFShelper(first, current, goal, visit, parent, queue, path, visitedInOrder);
    }
}

string Graph::printDFS(bool visited[], int first, int goal, int parent[], vector <int>& path) {
    int last = goal;
    string print = "visited: ";
    for (int i = 0; i < path.size() - 1; i++) {
        print = print + to_string(path[i]);
        print = print + " ";
    }
    print = print + "path:";
    vector <int> qu;
    qu.push_back(goal);
    while (goal != first) {
        qu.push_back(parent[goal]);
        goal = parent[goal];
    }

    for (int i = qu.size() - 1; i >= 0; i--) {
        print = print + " ";
        print = print + to_string(qu[i]);
    }
    return print;
}

string Graph::printBFS(bool visit[], int first, int goal, int parent[], int path[], vector <int> visitedInOrder) {
    int last = goal;
    string print = "visited: ";
    for (int i = 0; i < visitedInOrder.size(); i++) {
        print = print + to_string(visitedInOrder[i]);
        print = print + " ";
    }

    print = print + "path:";
    vector <int> qu;
    qu.push_back(goal);
    while (goal != first) {
        qu.push_back(parent[goal]);
        goal = parent[goal];
    }

    for (int i = qu.size() - 1; i >= 0; i--) {
        print = print + " ";
        print = print + to_string(qu[i]);
    }
    return print;
}

#endif