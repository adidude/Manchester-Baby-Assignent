/*
	Name: Aditya Kumar Menon
	Matriculation Number: 170025886
	Module: AC21009
*/

#include "Structures.h"

string commandToBinary (string const& inputString) // Returns binary string for the specified Manchester Baby function
{
    if(inputString == "JMP") return "000";
    if(inputString == "JRP") return "100";
    if(inputString == "LDN") return "010";
    if(inputString == "STO") return "110";
    if(inputString == "SUB") return "001";
    if(inputString == "CMP") return "101";
    if(inputString == "STP") return "011";
    if(inputString == "VAR") return "000";
}

void machineCodeLineGenerator (string command) // Example: Converts STO 26 to 01011000000001100000000000000000
{
    string opcode = command.substr(0, 3); // separating the opcode from the command line
    string Soperand = command.substr(4,5); // getting the operand

    opcode = commandToBinary(opcode);
    
    int Ioperand;
    istringstream(Soperand)>>Ioperand;
    string binary = numToBinary(Ioperand);

    string lineToBeWritten;

    lineToBeWritten.append(binary); // Line Number - 01011
    lineToBeWritten.append("00000000",8); // Space between line number and function - 00000000
    lineToBeWritten.append(opcode); // Function - 110
    lineToBeWritten.append("0000000000000000",16); // Remaining 16 bits - 0000000000000000

    int finalNumber[32]; // creating 32 bit array to write to memory
    for(int i=0; i<32; i++)
        {
           char temp = lineToBeWritten[i]; // separating each character of the array
           if (temp == '0')
            finalNumber[i] = 0; 
            else finalNumber [i] = 1;
        }

   /* for(int i=0; i<32; i++)
        cout<<finalNumber[i]; */

        // method to write to file

}

void translate()
{
	SymblTable table;
	table.initTable();

	
}

int main() 
{
	translate();

	return 0;
}