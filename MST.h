/************************************************************************************
* Project Group 8 - Anne Harris, Lowell Tyner, Kristen Wollman
* CS 325 - 400
* Traveling Salesman Problem 
* Implementing MST algorithm and Nearest Neighbor algorithm
* ***********************************************************************************
* This defines the MST algorithm 
*************************************************************************************/
#include<iostream>
#include<vector>
#include<cstring>

using namespace std;

#ifndef MST_H
#define MST_H

/************************************************************************************
* Function that implements the MST algorithm
* Parameters: adjacency matrix of ints representing cities and their distances to 
* other cities, int representing the total number of cities, int representing the 
* starting city and the vector of ints containing the path of cities
*************************************************************************************/
int MST(int ** G, int v, int s, vector<int> &path);

#endif // !MST.h
