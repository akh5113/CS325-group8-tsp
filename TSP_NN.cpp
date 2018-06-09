/************************************************************************************
* Project Group 8 - Anne Harris, Lowell Tyner, Kristen Wollman
* CS 325 - 400
* Traveling Salesman Problem 
* Implementing MST algorithm and Nearest Neighbor algorithm
* ***********************************************************************************
* This file contains the implemnation for the Nearest Neighbor algorithm, the fuction
* that prints the paths, and the function that tests cities to determine what the
* optimal start city is 
*************************************************************************************/

#include<iostream>
#include<vector>
#include<cstring>
#include<string>
#include"TSP_NN.h"
#define INF 99999999

using namespace std;


/************************************************************************************
* Function for printing path derived from Nearest Neighbor algorithm
* Parameters: string representing the name of the algorithm used to create path
* and vector of ints representing the path
*************************************************************************************/
void printPath(string algo, vector<int> pathIn) {
	cout << algo << " Path: " << endl;
	for (int i = 0; i < pathIn.size(); i++) {
		cout << pathIn.at(i);
		if (i < (pathIn.size() - 1)) {
			cout << ", ";
		}
	}
	cout << endl;
}

/************************************************************************************
* Function that implements nearest neighbor algorithm
* Parameters: adjacency matrix of ints representing cities and their distances to
* other cities, int representing the total number of cities, int representing the
* starting city and the vector of ints containing the path of cities
* Returns: int representing the total distance travled
*************************************************************************************/
int nearestNeighborAlgo(int ** cities, int numCities, int start, vector<int> &path) {
	//create visited list
	int *visited = NULL;
	visited = new int[numCities];
	memset(visited, 0, numCities * sizeof(int));

	//initalize current city to start city
	int currentCity = start;
	//initalize true in visited
	visited[start] = true;
	//clear path
	path.clear();
	//add start city to path
	path.push_back(start);

	//city that is closest to the current city, starts undefined
	int closestCity;

	//int total distance
	int totalDistance = 0;

	//number of cities visited
	int count = 0;

	//initalize minimum distance to infinity 
	int minDistance = INF;

	//while the count is less than the number of ciies, iterate through each city
	while (count < numCities - 1) {
		//reset minimum distance to infinity
		minDistance = INF;
		
		//loop through distances from current city
		for (int j = 0; j < numCities; j++) {
			//if the city has not been visited
			if (!visited[j]) {
				//if the city at j's distance is less than the minimum distance
				if (cities[currentCity][j] < minDistance) {
					// set minmum distance to j's distance
					minDistance = cities[currentCity][j];
					//set closest city to j
					closestCity = j;
				}
			}
		}
		if(!visited[closestCity]){
			//add closest city to path vector
			path.push_back(closestCity);
			//add distance to total distance
			totalDistance += minDistance;
			//set to true in visited matrix
			visited[closestCity] = true;
			//set current city to the latest added
			currentCity = closestCity;
			//increase count
			count++;
		}		
	}
	//add final path back to start
	minDistance = cities[currentCity][start];
	path.push_back(start);
	totalDistance += minDistance;

	//deleted visted array
	delete[] visited;

	//return total distance
	return totalDistance;
}

/************************************************************************************
* Function that iterates through each city to determine which starting city yields
* the shortest path
* Parameters: int representing the best city to start at for the mst algo and
* the nn algo, adjacency matrix of ints representing cities and their distances to
* other cities, int representing the total number of cities, int representing the
* starting city and the vector of ints containing the path of cities
*************************************************************************************/
void findBestCity(int &mstBest, int &nnBest, int numCities, int ** cities, vector<int> &path) {
	//set the current lengths to equal infinity
	int mstCurrent = INF;
	int nnCurrent = INF;

	//set the best lenghts to equal infinity
	int mstBestLen = INF;
	int nnBestLen = INF;

	//loop through each city to find fastest solution
	for (int i = 0; i < numCities; i++) {
		//mst
		//call mst functino for city i and save it in mstCurrent
		/*
		mstCurrent = MST(cities, numCities, i, path);
		cout << "the MST length starting at city " << i << " is " << mstCurrent << endl;
		//if i's path is less than the best path so far
		if (mstCurrent < mstBestLen) {
			mstBest = i;
		}
		//set mstBest to equal city i
		*/


		//nearest neighbor
		//call nearest neighbor function for city i and save it in nnCurrent
		nnCurrent = nearestNeighborAlgo(cities, numCities, i, path);
		cout << "the NN length starting at city " << i << " is " << nnCurrent << endl;
		//if i's path is less than the best path so far
		if (nnCurrent < nnBest) {
			//set nnBest to equal city i
			nnBest = i;
		}
	}
}
