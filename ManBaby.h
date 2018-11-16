#include <string>
#include <iostream>
#include <cstdlib>

/*Title: ExecutionFunct
Author: Ben Morrison
Date Created: 08/11/18
Date Modified: 14/11/18
Purpose: Execute the basic instuction set and prints
Desc: */

using namespace std;

string executeFunct(int opCode, int operand){
	std::string history; 
	std::string appender;
	std::string equal = " = ";
	std::string sub = " -= ";
	std::string negative = " = -";
	std::string add = " += ";
	switch(opCode){
		case 0:
			CI = operand;
			appender << to_string(CI) << equal << to_string(operand) << "\n";
			history += appender;
			break;
		case 1:
			CI += operand;
			appender << to_string(CI) << add << to_string(operand) << "\n";
			history += appender;
			break;
		case 2:
			accumulator = -operand;
			appender << to_string(accumulator) << negative << to_string(operand) << "\n";
			history += appender;
			break;
		case 3:
			operand = accumulator;
			appender += to_string(operand) += equal += to_string(accumulator) += "\n";
			history += appender;
			break;
		case 4:
			accumulator -= operand;
			appender << to_string(accumulator) << sub << to_string(operand) << "\n";
			history += appender;
			break;
		case 5:
			accumulator -= operand;
			appender << to_string(accumulator) << sub << to_string(operand) << "\n";
			history += appender;
			break;
		case 6:
			if(accumulator < 0){
				CI++;
				history += "if accumulator < 0 then skip next instruction \n";
			}
			break;
		case 7:
			history += "STOPPED \n";
			return history;
			break;
	}
}

void printFunct(string history){
	std::cout << history << std::endl;
}