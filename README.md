# CS325 - 400
# TSP Group 8
Anne Harris, Lowell Tyner, Kristen Wollam

# Overview
This program is for Oregon State's CS325-400 course. We are creating a solution to the Traveling Salesman Problem using two algorithms, nearest neighbor and MST. 
This program takes in a text file of the cities to be traveled to, calculates and outputs a file containing the near-optimal path and distance.

# File Format
This program reads in text files representing cities to be traveled to. The input files are defined like so:
Each line defines a city and each line has three numbers separated by white space
The first number is the city identifier
The second number is the city's x-coordinate
The third number is the city's y-coordinate
[city 1] [x-coord 1] [y coord 1]
[city 2] [x-coord 2] [y coord 2]
.
.
.
[city n] [x-coord n] [y coord n]

#Executing the Program
To run this program on flip, have all source code and header code files (.cpp and .h files) in one folder.
Files should include: runTsp.ccp, MST.cpp, MST.h, TSP_NN.cpp, TSP_NN.h, TSPFiles (*this is a folder*)
Within that folder include another folder titled "TSPFiles" and the folder "TSPFiles" will include the text files containing the city information.
`g++ runTsp.cpp TSP_NN.cpp MST.cpp -o prgm` to compile the files
`prgm [name of txt file]` to run the program with a given text file
  Example run: `prgm tsp_example_1.txt`

# Output
The program will output the distance of the tour in the first line, and each following line will represent the tour path. This output file will be name the same as the input file but with ".tour" postfixed.

  Example output file name: "tsp_example_1.txt.tour"
