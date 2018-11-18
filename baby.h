#ifndef MANCHESTER_BABY
#define MANCHESTER_BABY

#include <stdint.h>
#include <iostream>
#include <math.h>
#include <string>

using namespace std;

class Baby{
  static const int LINE_WIDTH = 32;
  static const int STORE_SIZE = 32;

  bool store[STORE_SIZE][LINE_WIDTH];
  bool ci[LINE_WIDTH];
  bool pi[LINE_WIDTH];
  bool acc[LINE_WIDTH];

public:
  Baby();
  void incrementCI();
  void fetchCI();
  void printCI();
  int binToDec(bool[]);
};

Baby::Baby(){
  for(int i = 0; i < LINE_WIDTH; i++){
    ci[i] = false;
    pi[i] = false;
    acc[i] = false;
    for(int j = 0; j < STORE_SIZE; j++){
      store[j][i] = false;
    }
  }
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

void Baby::printCI(){
  for(int i = 0; i < LINE_WIDTH; i++){
    if(ci[i]){
      cout << "1";
    }
    else{
      cout << "0";
    }
  }
  cout << "  " << to_string(binToDec(ci)) <<  endl;
}

int Baby::binToDec(bool binary[]){
  int sum = 0;

  for(int i = 0; i < LINE_WIDTH; i++){
    if(binary[i]){
      sum += pow(2,i);
    }
  }

  return sum;
}

#endif
