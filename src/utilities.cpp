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

bool sort_by_cpu(process_stats &a, process_stats &b) {
	return a.cpu_time < b.cpu_time;
}

bool sort_by_process(process_stats &a, process_stats &b) {
	return a.process_number < b.process_number;
}

bool sort_by_start(process_stats &a, process_stats &b) {
	return a.start_time < b.start_time;
}

bool sort_by_io(process_stats &a, process_stats &b) {
	return a.io_time < b.io_time;
}

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
		int count = 0;
		for (int i = 0; i < line.length(); i++){
			if (line[i] == ','){
				count++;
			}
		}
		if (count == 3){
			process_stats my_stats;
			string process_number, start_time, cpu_time, io_time;

			stringstream ss(line);
			getline(ss, process_number, ',');
			getline(ss, start_time, ',');
			getline(ss, cpu_time, ',');
			getline(ss, io_time, ',');

			stringstream p(process_number);
			stringstream s(start_time);
			stringstream c(cpu_time);
			stringstream i(io_time);

			p >> my_stats.process_number;
			s >> my_stats.start_time;
			c >> my_stats.cpu_time;
			i >> my_stats.io_time;

			if (my_stats.process_number >= 0 && my_stats.start_time >= 0 && my_stats.cpu_time >= 0 && my_stats.io_time >= 0) {
				stats.push_back(my_stats);
			}
		}

	}

	return SUCCESS;
}

//will sort according to user preference
void sortData(SORT_ORDER mySortOrder) {
	if (mySortOrder == CPU_TIME) {
		sort(stats.begin(), stats.end(), sort_by_cpu);
	}
	else if (mySortOrder == PROCESS_NUMBER) {
		sort(stats.begin(), stats.end(), sort_by_process);
	}
	else if (mySortOrder == START_TIME) {
		sort(stats.begin(), stats.end(), sort_by_start);
	}
	else {
		sort(stats.begin(), stats.end(), sort_by_io);
	}
}

process_stats getNext() {
	process_stats myFirst = stats[0];
	stats.erase(stats.begin(), stats.begin() + 1);

	return myFirst;
}

//returns number of process_stats structs in the vector holding them
int getNumbRows(){
	return stats.size();
}


