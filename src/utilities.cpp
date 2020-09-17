/***
 * KP Utils
 */
#include <numeric>
#include <math.h>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "utilities.h"
#include "stdlib.h"
#include <cctype>

using namespace std;

vector<process_stats> stats;

//********************** private to this compilation unit **********************

//if myString does not contain a string rep of number returns o
//if int not large enough has undefined behaviour, very fragile
int stringToInt(const char *myString) {
	return atoi(myString);
}

int loadData(const char* filename, bool ignoreFirstRow) {
	stats.clear();

	ifstream myfile;
	myfile.open(filename);
	if (!myfile.is_open()) {return COULD_NOT_OPEN_FILE;}

	string line, dummy_line;
	if (ignoreFirstRow){
		getline(myfile, dummy_line);
	}
	while(getline(myfile, line)) {
		process_stats my_stats;
		string process_number, start_time, cpu_time, io_time;

		stringstream ss(line);

		getline(ss, process_number, ',');
		getline(ss, start_time, ',');
		getline(ss, cpu_time, ',');
		getline(ss, io_time, ',');

		try {
			stringstream p(process_number);
			stringstream s(start_time);
			stringstream c(cpu_time);
			stringstream i(io_time);

			p >> my_stats.process_number;
			s >> my_stats.start_time;
			c >> my_stats.cpu_time;
			i >> my_stats.io_time;

			stats.push_back(my_stats);
		}
		catch (int e) {
			cout << "Exception occurred: " << e << endl;
		}

	}

	return SUCCESS;
}


//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {

}

process_stats getNext() {
	process_stats myFirst = stats[0];
	vector<process_stats> new_stats;
	if (stats.size() > 1) {
		for (int i = 1; i <= stats.size(); i++) {
			new_stats.push_back(stats[i]);
		}
	}
	else {
		stats.clear();
	}

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


