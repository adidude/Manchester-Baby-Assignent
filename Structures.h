#include <fstream>
#include <iostream>
#include <cstring>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

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

/*
Is a symbol table to store the data to be translated.
*/
class SymblTable
{
	vector<string> label;
	vector<int> labelAddress;
	vector<string> operand;
	vector<int> operandAddress;

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
					//If the current position is greater than 11
					if (i > 10)
					{
						//Add the text from before the semicolon to the vector.
						operand.push_back(line.substr(10,i-1));
						//Add the line number to the vector.
						operandAddress.push_back(lineNo);
					}
					//Make i the size to exit current loop.
					i = line.size();
				}
				else if (line[i] == ':')
				{
					//Will add the label and line number to the relevent vectors.
					label.push_back(line.substr(0,i));
					labelAddress.push_back(lineNo);
				}
			}
		}
	}

	//Getter methods
	vector<int> getLabelAddress(){return labelAddress;}
	vector<int> getOperandAddress(){return operandAddress;}
	vector<string> getLabel(){return label;}
	vector<string> getOperand(){return operand;}	
};

class Buffer
{

};