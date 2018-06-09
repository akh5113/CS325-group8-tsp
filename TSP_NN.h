/************************************************************************************
* Project Group 8 - Anne Harris, Lowell Tyner, Kristen Wollman
* CS 325 - 400
* Traveling Salesman Problem 
* Implementing MST algorithm and Nearest Neighbor algorithm
* ***********************************************************************************
* This file contains the headers for the Nearest Neighbor algorithm, the fuction
* that prints the paths, and the function that tests cities to determine what the
* optimal start city is 
*************************************************************************************/

#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

#ifndef TSP_NN_h
#define TSP_NN_h

/************************************************************************************
* Function that implements nearest neighbor algorithm
* Parameters: adjacency matrix of ints representing cities and their distances to 
* other cities, int representing the total number of cities, int representing the 
* starting city and the vector of ints containing the path of cities
*************************************************************************************/
int nearestNeighborAlgo(int ** cities, int numCities, int start, vector<int> &visited);

/************************************************************************************
* Function for printing path derived from Nearest Neighbor algorithm
* Parameters: string representing the name of the algorithm used to create path
* and vector of ints representing the path
*************************************************************************************/
void printPath(string algo, vector<int> pathIn);

/************************************************************************************
* Function that iterates through each city to determine which starting city yields
* the shortest path
* Parameters: int representing the best city to start at for the mst algo and
* the nn algo, adjacency matrix of ints representing cities and their distances to
* other cities, int representing the total number of cities, int representing the
* starting city and the vector of ints containing the path of cities
*************************************************************************************/
void findBestCity(int &mstBest, int &nnBest, int numCities, int ** cities, vector<int> &visited);


#endif 
