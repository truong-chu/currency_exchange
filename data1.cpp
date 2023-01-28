#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
 
using namespace std;

int main()
{
	string fname = "codes-all.csv", row, line, word;
	 
	vector<string> content;
	 
	fstream file (fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, line))
		{
			row = "";
						 
			stringstream str(line);
			 
			while(getline(str, word, ',')) 
			{
				row += word;
				row += " - ";
			}
			row = row.substr(0, row.length() - 3);
			content.push_back(row);
		}
	}
	else
	{
		cout<<"Could not open the file\n";
	}

	for(int i=0;i<content.size();i++)
	{
		cout << content[i] << "\n";
	}
	 
	return 0;
}
