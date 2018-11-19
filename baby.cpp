#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include "baby.h"


//For file input errors
#define BAD_FILE (1)
#define FILE_NOT_FOUND (2)
#define EXCEEDED_LENGTH (3)

using namespace std;

/*
 *	Checks if the  file is OK
 */
int checkFile(string name, int memorySize)
{
	ifstream input(name);
	//checks if file can be opened
	if (input.is_open())
	{
		string line;
		bool fileOK = true;
		int lineCount = 0;

		//Checks if there are lines in the file
		while (getline(input, line) && fileOK == true)
		{
			int numberCount = 0;
			lineCount++;
			//Checks if there are more lines than what baby can store
			if (lineCount > (memorySize-1))
			{
				fileOK = false;
			}

			for (unsigned i=0; i<line.length(); i++)
			{
				if (line[i] == '0' || line[i] == '1')
				{
					//Used to ensure there are 32 bits per line
					numberCount++;
				}
			}
			//if the line doesn't have 32 bits
			if (numberCount != 32)
			{
				fileOK = false;
			}
			else
			{
				for (unsigned i=0; i<line.length(); i++)
				{
					//Checks if there is any character which is not 0 or 1
					if (line[i] != '0' && line[i] != '1')
					{
						fileOK = false;
					}
				}
			}
		}

		input.close();

		if (lineCount > (memorySize-1))
		{
			return EXCEEDED_LENGTH;
		}

		if (fileOK == false)
		{
			return BAD_FILE;
		}

		return SUCCESS;
	}
	else
	{
		return FILE_NOT_FOUND;
	}
}


int main()
{
	cout << endl << "This is the Manchester Baby!" << endl;

	char input;
	int sizeInput = 32;

	Baby *baby = new Baby();

	//Asks user for the file name to open
	string name;
	cout << endl << "Enter the name of the machine code file for Baby to run." << endl;
	getline(cin, name);

	if (checkFile(name, sizeInput) == FILE_NOT_FOUND)
	{
		cout << name << " could not be found." << endl << endl;
		delete baby;
		return 1;
	}
	else if (checkFile(name, sizeInput) == BAD_FILE)
	{
		cout << name << " did not contain proper machine code." << endl << endl;
		delete baby;
		return 1;
	}
	else if (checkFile(name, sizeInput) == EXCEEDED_LENGTH)
	{
		cout << name << " contained too many instructions for Baby to store." << endl << endl;
		delete baby;
		return 1;
	}
	else
	{
		//Actually inserting the file into the store
		string line;
		ifstream input(name);
		int lineNumber = 0;

		while (getline(input, line))
		{
			baby->insertInstruction(line, lineNumber);
			lineNumber++;
		}

		input.close();

		cout << "Program successfully written to Baby." << endl << endl;

//////////////////////////////////////////////////////////////////////////////////////////
		//PROGRAM LOOP

		bool stop = false;

		do
		{
			//does what it says on the tin. Starts execution of programs from second line of store (this is where they are loaded to)
			baby->incrementCI();
			//retrieve the instruction from that address
			baby->fetchCI();

			//prints the current state of Baby
			baby->printState();

			//decode instruction and execute
			int returnCode = baby->decode();

			if(returnCode == STOP)
			{
				stop = true;
			}
			//Instruction tried to access non-existent part of memory
			else if (returnCode == NOT_ENOUGH_MEMORY)
			{
				cout << "Instruction error! Present instruction refers to line " << baby->getOperand() << ", which is non-existent!" << endl;
			}

			//Reached end of store without finding stop instruction
			if (baby->getCurrentInstructionAddress() > sizeInput -1)
			{
				stop = true;
			}
		}
		while (stop == false);

		if (baby->getCurrentInstructionAddress() > sizeInput-1)
		{
			cout << "Error! Reached end of program without finding STOP." << endl;
		}

		cout << "Terminating." << endl;
	}

	delete baby;
	return 0;
}
