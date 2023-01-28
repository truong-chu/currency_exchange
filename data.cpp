#include "data.h"

Data::Data()
{
	this->fname = "codes-all.csv";
	this->extract();
}

Data::~Data()
{

}

vector<string> Data::getData()
{
	return this->content;
}

void Data::extract()
{
	
	fstream file (this->fname, ios::in);
	if(file.is_open())
	{
		while(getline(file, this->line))
		{
			this->row = "";
						 
			stringstream str(line);
			 
			while(getline(str, this->word, ',')) 
			{
				this->row += this->word;
				this->row += " - ";
			}
			this->row = this->row.substr(0, row.length() - 3);
            if (this->row[4] == '-') {
			    this->content.push_back(this->row);
            }
		}
	}
	else
	{
		cout<<"Could not open the file\n";
	}
}