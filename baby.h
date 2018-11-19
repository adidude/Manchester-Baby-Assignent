#ifndef MANCHESTER_BABY
#define MANCHESTER_BABY

#include <stdint.h>
#include <iostream>
#include <math.h>
#include <string>

#define SUCCESS	(0)					//task succeeded
#define OUT_OF_RANGE (1)			//arithmetical sum went beyond what Baby can store
#define STOP (2)					//stop execution
#define CONTINUE (3)				//continue execution
#define NOT_ENOUGH_MEMORY (4) //Baby ran out of memory for the current program

using namespace std;

class Baby{
  static const int LINE_WIDTH = 32;
  static const int STORE_SIZE = 32;

  bool** store = new bool*[STORE_SIZE];
  bool* ci = new bool[LINE_WIDTH];
  bool* pi = new bool[LINE_WIDTH];
  bool* acc = new bool[LINE_WIDTH];

public:
  Baby();
  void incrementCI();
  void fetchCI();
  bool* fetchLine(int);
  void printCI();
  void printBin(bool[]);
  int binToDec(bool[]);
  bool* decToBin(int);
  void setPi(bool[]);
  void copyBinary(bool[], bool[]);
  void lineToStore(bool[],int);

  bool* addBinary(bool[], bool[]);
  bool* subtractBinary(bool[], bool[]);

  void executeFunct(int, int);
  void decodePI(int*, int*);
  int decode();

  int getCurrentInstructionAddress();

};

Baby::Baby(){
  store = new bool*[STORE_SIZE];
  ci = new bool[LINE_WIDTH];
  pi = new bool[LINE_WIDTH];
  acc = new bool[LINE_WIDTH];
  for(int i = 0; i < STORE_SIZE; i++){
    store[i] = new bool[LINE_WIDTH];
  }

  for(int i = 0; i < LINE_WIDTH; i++){
    ci[i] = false;
    pi[i] = false;
    acc[i] = false;
    for(int j = 0; j < STORE_SIZE; j++){
      store[j][i] = false;
    }
  }
}

int Baby::getCurrentInstructionAddress(){
  return binToDec(ci);
}

void Baby::incrementCI(){
  bool switchBit = true;
  for(int i = 0; i < LINE_WIDTH; i++){
    if(switchBit){
      ci[i] = !ci[i];
      if(!ci[i]){
        switchBit = true;
      }
      else{
        switchBit = false;
      }
    }
  }
}

void Baby::fetchCI(){
  int lineToFetch = binToDec(ci);
  for(int i = 0; i < LINE_WIDTH; i++){
    pi[i] = store[lineToFetch][i];
  }
}

bool* Baby::fetchLine(int lineToFetch){
  return store[lineToFetch];
}

void Baby::printCI(){
  for(int i = 0; i < LINE_WIDTH; i++){
    if(pi[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout << "  " << to_string(binToDec(pi)) << "  ";

  bool* bin = decToBin(binToDec(ci));
  for(int i = 0; i < LINE_WIDTH; i++){
    cout << to_string(bin[i]);
  }

  cout << endl << endl;
}

void Baby::printBin(bool* bin){
  for(int i = 0; i < LINE_WIDTH; i++){
    if(bin[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout << "  " << to_string(binToDec(bin)) << "  ";
}

int Baby::binToDec(bool binary[]){
  int sum = 0;

  for(int i = 0; i < LINE_WIDTH-1; i++){
    if(binary[i]){
      sum += pow(2,i);
    }
  }
  if(binary[LINE_WIDTH-1] == 1){
    sum = -sum;
  }
  return sum;
}

bool* Baby::decToBin(int dec){
  bool* bin = new bool[32];
  if(dec<0){
    bin[LINE_WIDTH-1] = 1;
    dec = -dec;
  }
  for(int i = (LINE_WIDTH-2); i >= 0; i--){
    if(dec%(int)pow(2,i)==dec){
      bin[i] = 0;
    }
    else{
      bin[i] = 1;
      dec -= (int)pow(2,i);
    }
  }
  cout << "qwe" << endl;
  return bin;
}

void Baby::decodePI(int* opCode, int* operand){
  bool opCodeBin[LINE_WIDTH],operandBin[LINE_WIDTH];
  for(int i = 0; i < LINE_WIDTH; i++){
    if(i<=5){
      operandBin[i] = pi[i];
    }
    else{
      operandBin[i] = 0;
    }
    if(i<=3){
      opCodeBin[i] = pi[i+13];
    }
    else{
      opCodeBin[i] = 0;
    }
  }
  *opCode = binToDec(opCodeBin);
  *operand = binToDec(operandBin);
}

void Baby::setPi(bool bin[]){
  for(int i = 0; i < LINE_WIDTH; i++){
    pi[i] = bin[i];
  }
}

bool* Baby::addBinary(bool a[], bool b[]){
  bool carry = false;
  bool* c = new bool[LINE_WIDTH];
  for(int i = 0; i < LINE_WIDTH; i++){
    int count = 0;
    if(a[i]){
      count++;
    }
    if(b[i]){
      count++;
    }
    if(carry){
      count++;
    }

    if(count == 1 || count == 3){
      c[i] = 1;
    }
    else{
      c[i] = 0;
    }
    if(count >= 2){
      carry = true;
    }
    else{
      carry = false;
    }
  }
  return c;
}

bool* Baby::subtractBinary(bool a[], bool b[]){
  bool* c = new bool[LINE_WIDTH];

  for(int i = 0; i < LINE_WIDTH; i++){
    cout << pow(2,i) << endl;
    for(int j = 0; j < LINE_WIDTH; j++){
      cout << a[j];
    }
    cout << endl;
    if(a[i] && !b[i]){
      c[i] = 1;
      cout << "a !b" <<  endl;
    }
    else if(a[i] && b[i]){
      c[i] = 0;
      cout << " a b" << endl;
    }
    else if(!a[i] && b[i]){
      int count = 0;
      cout << "!a b" << endl;
      while(!a[i] && i<LINE_WIDTH){
        i++;
        count++;
      }
      if(a[i]){
        for(int j = count; j >= 0; j--){
          cout << a[i-j] << "  ";
          a[i-j] = !a[i-j];
          cout << a[i-j] << endl;;

        }
        i -= count;
        c[i]=1;
      }
      else{
        throw 1;
      }
    }

  }

  return c;
}

void Baby::copyBinary(bool a[] ,bool b[]){
  for(int i = 0; i < LINE_WIDTH; i++){
    b[i] = a [i];
  }
}

void Baby::executeFunct(int opCode, int operand){
	//std::string history;
	//std::string appender;
	std::string equal = " = ";
	std::string sub = " -= ";
	std::string negative = " = -";
	std::string add = " += ";
	switch(opCode){
		case 0:{
      cout << "CI:" << binToDec(ci) << equal << to_string(operand) << endl;
			copyBinary(decToBin(operand),ci);
			//appender << to_string(ci) << equal << to_string(operand) << "\n";
			//history += appender;
			break;
    }
		case 1:{
      cout << "CI:" << binToDec(ci) << add << to_string(operand) << endl;
			ci = addBinary(ci,decToBin(operand));
			//appender << to_string(CI) << add << to_string(operand) << "\n";
			//history += appender;
			break;
    }
		case 2:{
      cout << "ACC:" << to_string(binToDec(acc)) << negative << "STORE:" << to_string(binToDec(fetchLine(operand))) << endl;
      int operandVal;
      operandVal = binToDec(fetchLine(operand));
      acc = decToBin(-operandVal);
			//appender << to_string(accumulator) << negative << to_string(operand) << "\n";
			//history += appender;
			break;
    }
		case 3:{
      cout << "STORE:" << to_string(operand) << equal << "ACC:" << to_string(binToDec(acc)) << endl;
      copyBinary(acc,store[operand]);
			//appender += to_string(operand) += equal += to_string(accumulator) += "\n";
			//history += appender;
			break;
    }
		case 4:
		case 5:
      cout << "ACC:" << to_string(binToDec(acc)) << sub << "STORE:" << to_string(binToDec(fetchLine(operand))) << endl;
      int operandVal, accumulatorVal;
      operandVal = binToDec(fetchLine(operand));
      accumulatorVal = binToDec(acc) - operandVal;
      acc = decToBin(accumulatorVal);
    //  appender << to_string(binToDec(acc)) << sub << to_string(operand) << "\n";
    //  history += appender;
			break;
		case 6:{
			if(binToDec(acc) < 0){
				incrementCI();
				cout << "if accumulator < 0 then skip next instruction" << endl;
			}
			break;
    }
		case 7:{
			cout << "STOPPED" << endl;
			throw STOP;
			break;
    }
	}
}

int Baby::decode(){
  int* opcode = new int;
  int* operand = new int;
  bool stop = false;
  decodePI(opcode,operand);
  try{
    executeFunct(*opcode,*operand);
  }
  catch(int){
    stop = true;
  }

  if(stop){
    return STOP;
  }
  else{
    return CONTINUE;
  }

}

#endif
