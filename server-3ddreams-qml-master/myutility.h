#ifndef MYUTILITY_H
#define MYUTILITY_H

#include <iostream>
#include <sstream>      // std::stringstream
#include <cstdint>
#include <cstring>
//#include "csv.h"

using namespace std;

class MyUtility
{
public:
    MyUtility();
    string numberToString(double num);
    string numberToString(uint8_t num);
    string numberToString(uint16_t num);
    string numberToString(uint32_t num);
    string numberToString(int num);
    string numberToString(float num);
    string charArrayToString(char *temp);
    bool checkStringContainsNum(string c);
    int byteArrayToInt(unsigned char byte1);
    int byteArrayToInt(unsigned char byte1, unsigned char byte2);
    int byteArrayToInt(unsigned char byte1, unsigned char byte2, unsigned char byte3);
    int byteArrayToInt(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4);

};

#endif // MYUTILITY_H
