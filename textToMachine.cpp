#include "Structures.h"

string hexToBinary(char e) // Big Endian Hex to Binary converter
{
    switch(e)
    {
        case '0': return "0000";
        case '1': return "1000";
        case '2': return "0100";
        case '3': return "1100";
        case '4': return "0010";
        case '5': return "1010";
        case '6': return "0110";
        case '7': return "1110";
        case '8': return "0001";
        case '9': return "1001";
        case 'A': return "0101";
        case 'B': return "1101";
        case 'C': return "0011";
        case 'D': return "1011";
        case 'E': return "0111";
        case 'F': return "1111";
    }
}

string numToBinary(int number) // used to return the Line Number - 5 bits always - big endian
{
    int binaryArray[5]; // The array to store the binary number
	int temp = 0;
    int numInDecimal = number;
    int numInBinary = 0;
    string numInString;

	while(temp<5)
	{
		binaryArray[temp] = numInDecimal%2;
		numInDecimal /= 2;
		temp++;
	}

    for(int i = 0; i < 5; i++)
        numInBinary = 10 * numInBinary + binaryArray[i];

    numInString = to_string(numInBinary);

    if(numInString.length() < 5)
        numInString.insert(0, 5-(numInString.length()), '0');

    return numInString;
}

string commandToBinary (string const& inputString) // Returns binary string for the specified Manchester Baby function
{
    if(inputString == "JMP") return "000";
    if(inputString == "JRP") return "100";
    if(inputString == "LDN") return "010";
    if(inputString == "STO") return "110";
    if(inputString == "SUB") return "001";
    if(inputString == "CMP") return "101";
    if(inputString == "STP") return "011";
    if(inputString == "VAR") return "111";
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

int main()
{
    // machineCodeLineGenerator("STO 26"); //test 
    return 0;
}

