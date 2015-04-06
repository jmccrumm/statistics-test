/*
*	John McCrummen
*	CS 3060
*	3/31/15
*	Group (Nate & Luke)
*/

#include <iostream>
#include <vector>
#include <dlib/statistics.h>
#include <fstream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <cstdlib>
#include <sstream>
#include <cmath>

using namespace std;
using namespace dlib;

// prototypes
int countData(char[]);
void printStats(running_stats<double>);


int main(){

	// create running_stats object
	running_stats<double> rs;
	running_stats<double> refrs;

	// create variable to count how many points are within radius
	int refcount = 0;

	// request data file from user
	char dataPath[80];
	cout << "Enter the full path of the data file you wish to use:" << endl;
	cin >> dataPath;

	// calculate size needed for array based on file
	const int NUM_DATA_POINTS = countData(dataPath);

	// arrays used to hold data values read from file
	double array[NUM_DATA_POINTS];
	double refinedarray[NUM_DATA_POINTS];

	cout << endl << "Number of data points in file: " << NUM_DATA_POINTS << endl << endl;

	// read data from file
	ifstream inputFile;
	inputFile.open(dataPath);
	string line, strxData, stryData, strLabel;
	double xData = 0, yData = 0, label = 0;

	// check if file opens correctly
	if (inputFile)
	{
		// extract x and y values
		int count = 0;
		while(getline(inputFile, line))
		{
			stringstream linestream(line);
			
			getline(linestream, strLabel, ',' );
			getline(linestream, strxData, ',' );
			getline(linestream, stryData, ',' );
			// convert x and y values to doubles
			xData = atof(strxData.c_str());
			yData = atof(stryData.c_str());
			label = atoi(strLabel.c_str());
			
			// calculate distance and input into array
			array[count] = sqrt((xData*xData) + (yData*yData));
			// only input +1 values into refined array
			if (label == 1)
			{
				refinedarray[count] = array[count];
				refcount++;
			} // end if
			// display distances
			cout << "Distance from origin for data point (" 
				<< xData << "," << yData << "):" << endl;
			cout << array[count] << endl;
			count++;
		} // end while	
	inputFile.close();
	} // end if
	else // did not open
		cout << "Cannot open file. Try running program again with a different file." << endl;
	

	// input data into rs object from array
	for (int i = 0; i < NUM_DATA_POINTS; i++)
		rs.add(array[i]);	

	// do same for refined array
	for (int i = 0; i < NUM_DATA_POINTS; i++)
	{
		// disregard zeros
		if (refinedarray[i] != 0)		
			refrs.add(refinedarray[i]);
	} // end for


	cout << endl << endl;

	// compute and print mean, variance, skewness, and excess kurtosis
	cout << "Using all points:" << endl << endl;
	printStats(rs);

	cout << endl << endl;	

	// repeat for refined array
	cout << "While disregarding points outside radius:" << endl;
	cout << "(using the " << refcount << " data points inside)" << endl << endl;
	printStats(refrs);
	
return 0;
} // end main


int countData(char file[])
{
	string line;
	int count = 0;

	ifstream inputFile;
	inputFile.open(file);
	// check if file opens correctly
	if (inputFile)
	{
		// count number of lines, ie. number of data points
		while(getline(inputFile, line))	
			count++;
	inputFile.close();
	} // end if
	else // did not open
		cout << "Cannot open file. Try running program again with a different file." << endl;

	return count;
} // end countData


void printStats(running_stats<double> runStats)
{
	cout << "Mean:            " << runStats.mean() << endl;
    	cout << "Variance:        " << runStats.variance() << endl;
    	cout << "Skewness:        " << runStats.skewness() << endl;
    	cout << "Excess Kurtosis: " << runStats.ex_kurtosis() << endl;

} // end printStats

Displaying stats.cpp.
