#ifndef DATA_H
#define DATA_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;

class Data{
	private:
		vector<string> content;
		string fname;
		string row;
		string line;
		string word;
		
	public:
		//constructors & destructors
		Data();
		~Data();
		
		//accessors
		vector<string> getData();
		void extract();
};

#endif