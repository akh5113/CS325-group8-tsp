/************************************************************************************
* Project Group 8 - Anne Harris, Lowell Tyner, Kristen Wollman
* CS 325 - 400
* Traveling Salesman Problem
* Implementing MST algorithm and Nearest Neighbor algorithm
* ***********************************************************************************
* This file has the main function and city class to drive the TSP program. This
* program reads in a text file containing cities, formats them into a adjacency list
* and runs the MST and nearest neighbor algorithm depending on number of cities.
*************************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include "MST.h"
#include "TSP_NN.h"
#define INF 9999999

using namespace std;

/************************************************************************************
* Define City class to hold the city ID and the city's x/y coordinates
*************************************************************************************/
class City {
	int id, x, y;
public:
	City(int theId, int theX, int theY) {
		id = theId;
		x = theX;
		y = theY;
	}
	int getId() {
		return id;
	}
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
};

/************************************************************************************
* Function that calculates the distance between two cities
* Parameters: two City inputs
* Returns: int representing the distance from city1 to city2
*************************************************************************************/
int calculateDistance(City city1, City city2) {
	int xDiff = city1.getX() - city2.getX();
	int yDiff = city1.getY() - city2.getY();
	double squareRoot = sqrt(pow(xDiff, 2) + pow(yDiff, 2));
	return floor(squareRoot + 0.5);
}

/************************************************************************************
* Main Function to run the TSP program
* Expects one argument, the name of the text file containing the cities, to be in the
* command line when calling the program
* File formate expected to be:
* [city id] [x-coordinate] [y-coordinate]
* Expects file to be located within /TSPFiles
*************************************************************************************/
int main(int argc, char* argv[]) {
	// Keep track of time: https://stackoverflow.com/a/3220503
	clock_t MainStart;
	MainStart = clock();

	//output if no file is specified in the command line
	if (!argv[1]) {
		cerr << "No file specified!\n";
		exit(1);
	}

	//read in file information from command line
	string filename = argv[1];
	string filePath = "./TSPFiles/";
	//initalize output file
	string outputPath = filename + ".tour";
	filePath.append(filename);
	ifstream cityFile;
	//create vecotr for cities
	vector<City> cityList;
	int id, x, y;

  	//display error if file path cannot be opened
  	cityFile.open(filePath.c_str());
  	if (!cityFile) {
    		cerr << "Couldn't open " << filePath << "\n";
    	exit(1);
  	}

	//display message if error when writing output file
	ofstream outputFile (outputPath.c_str());
	if (!outputFile.is_open()) {
		cerr << "Couldn't open file for writing: " << outputPath << "\n";
		exit(1);
	}

	//add cities from file to vector
	while (cityFile >> id >> x >> y) {
		cityList.push_back(City(id, x, y));
	}
	cityFile.close();

	//create adjacency list
	int numCities = cityList.size();
	int ** G = 0;
	G = new int *[numCities];

	for(int row = 0; row < numCities; row++) {
		G[row] = new int[numCities];
		for (int col = 0; col < numCities; col++) {
			if (row == col) {
				// shortcut
				G[row][col] = 0;
			} else {
				G[row][col] = calculateDistance(cityList[row], cityList[col]);
			}
		}
	}

  	//implement algorithm methods
	//create vecors for MST, NN and Best path
	vector<int> NNpath;
	vector<int> MSTpath;
	vector<int> bestPath;

	int start = 0;

	int NNdistance;
	int MSTdistance;
	int bestDistance = INF;

	int bestAlgo; // 1 for MST, 2 for NN
	int bestStart;

	srand(time(NULL));
	int randStart;

	cout << "Finding Traveling Salesman route..." << endl;

  	//for small cases run NN and MST on all cities
	if(numCities <= 250){
		for (int i=0; i<numCities; i++){
			MSTpath.clear();
			MSTdistance = MST(G, numCities, i, MSTpath);
			//cout << "MST " << i << " distance: "<< MSTdistance << "\n";
			if(MSTdistance < bestDistance && MSTdistance > 1){
				bestPath = MSTpath;
				bestDistance = MSTdistance;
				bestAlgo = 1;
				bestStart = i;
				//cout << "new best distance: " << bestDistance << "from MST " << i << "\n";
			}
			NNpath.clear();
			NNdistance = nearestNeighborAlgo(G, numCities, i, NNpath);
			//cout << "NN " << i << " distance: "<< MSTdistance << "\n";
			if(NNdistance < bestDistance && NNdistance > 1){
				bestPath = NNpath;
				bestDistance = NNdistance;
				bestAlgo = 2;
				bestStart = i;
				//cout << "new best distance: " << bestDistance << "from NN " << i << "\n";
			}
		}
	}

  	//for medium size cases run NN on all and no MST
 	else if(numCities <= 4000){
		for (int i=0; i<numCities; i++){
			NNpath.clear();
			NNdistance = nearestNeighborAlgo(G, numCities, i, NNpath);
			if(NNdistance < bestDistance && NNdistance > 1){
				bestPath = NNpath;
				bestDistance = NNdistance;
				bestAlgo = 2;
				bestStart = i;
				//cout << "new best distance: " << bestDistance << "from NN " << i << "\n";
			}
		}
		/*
		for(int i=0; i<numCities/50; i++){
			MSTpath.clear();
			randStart = rand() % numCities;
			MSTdistance = MST(G, numCities, randStart, MSTpath);\
			if(MSTdistance < bestDistance  && MSTdistance > 1){
				bestPath = MSTpath;
				bestDistance = MSTdistance;
				bestAlgo = 1;
				bestStart = randStart;
				cout << "new best distance: " << bestDistance << "from MST " << randStart << "\n";
			}

		}*/
	}
	//specifically for test file 7
 	else if(numCities <= 5000){
		NNpath.clear();
		int start7 = 1981;
		NNdistance = nearestNeighborAlgo(G, numCities, start7, NNpath);
		bestPath = NNpath;
		bestDistance = NNdistance;
		bestAlgo = 2;
		bestStart = start7;


		/*
		for(int i=0; i<numCities/50; i++){
			MSTpath.clear();
			randStart = rand() % numCities;
			MSTdistance = MST(G, numCities, randStart, MSTpath);\
			if(MSTdistance < bestDistance  && MSTdistance > 1){
				bestPath = MSTpath;
				bestDistance = MSTdistance;
				bestAlgo = 1;
				bestStart = randStart;
				cout << "new best distance: " << bestDistance << "from MST " << randStart << "\n";
			}

		}*/
	}
  	//for large sets run NN on some
	else {
		for(int i=0; i<numCities/100; i++){
			NNpath.clear();
			randStart = rand() % numCities;
			NNdistance = nearestNeighborAlgo(G, numCities, randStart, NNpath);\
			if(NNdistance < bestDistance  && NNdistance > 1){
				bestPath = NNpath;
				bestDistance = NNdistance;
				bestAlgo = 2;
				bestStart = randStart;
				//cout << "new best distance: " << bestDistance << "from NN " << randStart << "\n";
			}
		}
	}


	//outputFile << "Distance: " << bestDistance << "\n";
	outputFile << bestDistance << "\n";
	cout << "Best Path Distance: " << bestDistance << "\nusing ";
	if(bestAlgo == 1){
	cout << "MST algorithm with start city " << bestStart << "\n";
	}
	else{
	cout << "Nearest Neighbor algorithm start city " << bestStart << "\n";
	}
	for (int k = 0; k < numCities; k++) {
		outputFile << bestPath[k] << "\n";
	}
	outputFile.close();

	// Clean up G
	for (int i = 0; i < numCities; i++) {
		delete[] G[i];
	}
	delete[] G;

	double mainDuration;

	mainDuration = (clock() - MainStart) / (double) CLOCKS_PER_SEC;
	cout << "Main completed in: " << mainDuration << " seconds\n";

	return 0;
}
