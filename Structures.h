#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

ifstream getFile();

class SymblTable
{
	vector<string> label;
	vector<int> address;
	vector<string> operand;

public:
	//Will pass through assembly language once and initialise symbol table.
	void initTable()
	{
		//Allow user to select file being used for assembly language.
		ifstream file = getFile();
		//Will store the current line and the line number.
		string line;
		int lineNo = 0;

		//While there are lines in the file.
		while(getline(file, line))
		{
			lineNo++;
			//For the number of characters in a line
			for (unsigned int i = 0; i < line.size(); ++i)
			{
				//If current char is ; will exit current loop.
				if (line[i] == ';')
				{
					i = line.size();
					operand.push_back(line.substr(11,i-1));
				}
				else if (line[i] == ':')
				{
					//Will add the label and line number to the relevent vectors.
					label.push_back(line.substr(0,i-1));
					address.push_back(lineNo);
				}
			}
		}
	}

};

class Buffer
{

};

ifstream getFile()
{	
	string filename;
	cout << "Enter file name" << endl;
	cin >> filename;
	ifstream fileStream(filename);
	if (fileStream.is_open())
	{
		return fileStream;
	}
	else
	{
		cerr << "File not found." << endl;
	}
	return fileStream;
}