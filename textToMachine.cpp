#include<iostream>
#include<cstring>
#include<sstream>
#include<vector>
#include<fstream>

using namespace std;

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

string varNumGenerator (int number)
{
    int binaryArray[16]; // The array to store the binary number
	int temp = 0;
    int numInDecimal = number;
    unsigned long long numInBinary = 0;
    string numInString;

	while(numInDecimal != 0)
	{
		binaryArray[temp] = numInDecimal%2;
		numInDecimal /= 2;
		temp++;
	}

    for(int i = 0; i < temp; i++)
        numInBinary = 10 * numInBinary + binaryArray[i];

    numInString = to_string(numInBinary);

    if(numInString.length() < 16)
        numInString.append(16-(numInString.length()), '0');

    return numInString;
}

string commandToBinary (string const& inputString) // Returns binary string for the specified Manchester Baby function
{
    if(inputString == "JMP") return "000";
    if(inputString == "JRP") return "110";
    if(inputString == "LDN") return "010";
    if(inputString == "STO") return "110";
    if(inputString == "SUB") return "001";
    if(inputString == "CMP") return "011";
    if(inputString == "STP") return "111";
    if(inputString == "VAR") return NULL;
}

int characterCount(std::string in)
{
    int count = 0;
    for(unsigned int i = 0; i < in.size(); ++i) {
        if (!isspace(in[i]))
            ++count;
    }
    return count;
}

void machineCodeLineGenerator (string command) // Example: Converts STO 26 to 01011000000001100000000000000000
{
    int commandLength = characterCount(command);
    int Ioperand;
    int finalNumber[32]; // creating 32 bit array to write to memory
    string lineToBeWritten;
    ofstream myFile;
    
    myFile.open("Compiled Code.txt");

    string opcode, Soperand;

    if (commandLength == 4)
    {
        opcode = command.substr(0,3);
        Soperand = command.substr(4,4);
    }

    else if (commandLength == 5)
    {
    opcode = command.substr(0, 3); // separating the opcode from the command line
    Soperand = command.substr(4,5); // getting the operand
    }

    else if (commandLength == 6)
    {
        opcode = command.substr(0, 3); // separating the opcode from the command line
        Soperand = command.substr(4,6); // getting the operand
    }

    else if (commandLength == 7)
    {
        opcode = command.substr(0, 3); // separating the opcode from the command line
        Soperand = command.substr(4,7); // getting the operand
    }

    else if (commandLength == 8)
    {
        opcode = command.substr(0, 3); // separating the opcode from the command line
        Soperand = command.substr(4,8); // getting the operand
    }

    else
    {
        cout<<"The command "<<command<<" isn't declared properly"<<endl;
    }

    if (opcode == "VAR")
    {
        istringstream(Soperand)>>Ioperand;
        string binary = varNumGenerator(Ioperand);
        
        lineToBeWritten = binary;

        lineToBeWritten.append("0000000000000000",16);

        for(int i=0; i<32; i++)
        {
           char temp = lineToBeWritten[i]; // separating each character of the array
           if (temp == '1')
            finalNumber[i] = 1; 
            else finalNumber [i] = 0;
        }

        for(int i=0; i<32; i++)
            myFile<<finalNumber[i];

        return;
    }


        opcode = commandToBinary(opcode);
    
        istringstream(Soperand)>>Ioperand;
        string binary = numToBinary(Ioperand);


        lineToBeWritten.append(binary); // Line Number - 01011
        lineToBeWritten.append("00000000",8); // Space between line number and function - 00000000
        lineToBeWritten.append(opcode); // Function - 110
        lineToBeWritten.append("0000000000000000",16); // Remaining 16 bits - 0000000000000000


         for(int i=0; i<32; i++)
        {
           char temp = lineToBeWritten[i]; // separating each character of the array
           if (temp == '1')
            finalNumber[i] = 1; 
            else finalNumber [i] = 0;
        }

        for(int i=0; i<32; i++)
            myFile<<finalNumber[i];

    myFile<<endl;
        // method to write to file

}

int main()
{
  machineCodeGenerator("LDN 08");
    return 0;
}

