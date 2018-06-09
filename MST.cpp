/************************************************************************************
* Project Group 8 - Anne Harris, Lowell Tyner, Kristen Wollman
* CS 325 - 400
* Traveling Salesman Problem 
* Implementing MST algorithm and Nearest Neighbor algorithm
* ***********************************************************************************
* This file has the implemenation for the MST algorithm
*************************************************************************************/
#include <stack>
#define INF 9999999
#include <iostream>
#include <vector>
#include "MST.h"

using namespace std;

/************************************************************************************
* Function that implements MST algorithm
* Parameters: adjacency matrix of ints representing cities and their distances to 
* other cities, int representing the total number of cities, int representing the 
* starting city and the vector of ints containing the path of cities
*************************************************************************************/
int MST(int ** G, int v, int s, vector<int> &path) {
	//adjacency matrix to represent MST, all values set to 0
	int **T = 0;
	T = new int *[v];
	for (int n = 0; n < v; n++) {
		T[n] = new int[v];
		memset(T[n], 0, v * sizeof(int));
	}
	int edgeCount = 0;       // number of edges added, starts at 0

	// create an array to track selected vertex and set to false
	int *selected = NULL;
	selected = new int[v];
	memset(selected, 0, v * sizeof(int));
	

	// choose 0th vertex (or any vertex to start at) and make it true
	selected[s] = true;

	int x, y;            //  row number, col number

	//run till edgeCount < v -1 to make complete MST via Prim’s
	while (edgeCount < v - 1) {
		//For every vertex in selected find the minimum distance to any vertex not in selected
		int min = INF;
		x, y = 0;
		for (int i = 0; i < v; i++) {
			if (selected[i]==1) {
				for (int j = 0; j < v; j++) {
					if (selected[j]==0) { // not in selected
						if (min > G[i][j]) {
							min = G[i][j];
							x = i;
							y = j;
						}
					}
				}
			}					
		}
		T[x][y] = G[x][y];
		T[y][x] = G[x][y];
		selected[y] = true;
		edgeCount++;
	}
	// run depth first search to create pre-order walk
	int length = 0; 	// to hold cumulative walk length
	stack<int> S;	// to hold vertices in work
	int u = s;
	int prev = s;	//or any starting index
	//Set selected back to false for all values
	memset(selected, 0, v * sizeof(int));
		S.push(u);
	//cycle through all vertices pushing unvisited ones to the stack

	while (S.empty() == false) {
		u = S.top(); // get top vertex off stack
		length += G[u][prev];
		//cout << "added to walk: " << u <<" leg length: " << G[u][prev] << " path: " << length << "\n";
		S.pop();
		path.push_back(u);
		selected[u] = 1;
		for (int k = 0; k < v; k++) {
			if (!selected[k] && T[u][k]) {
				S.push(k);
				// << "stack top: " << S.top() << "\n";
			}
		}
		prev = u;
	}
	length += G[s][u];
	for (int p = 0; p < v; p++) {
		delete[] T[p];
	}
	delete[] T;
	delete[] selected;
	return length;
}
