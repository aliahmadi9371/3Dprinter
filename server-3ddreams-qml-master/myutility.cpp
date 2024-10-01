#include "myutility.h"

MyUtility::MyUtility()
{

}

string MyUtility::numberToString(double num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::numberToString(uint8_t num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::numberToString(uint16_t num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::numberToString(uint32_t num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::numberToString(int num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::numberToString(float num)
{
    ostringstream ss;
    ss << num;
    return ss.str();
}

string MyUtility::charArrayToString(char *temp)
{
    size_t i;
    size_t size = sizeof(temp);
    string s = "";
    for (i = 0; i < size; i++) {
            s = s + temp[i];
    }
    return s;
}

bool MyUtility::checkStringContainsNum(string c)
{
    return (
                    c.find('0') != std::string::npos ||
                    c.find('1') != std::string::npos ||
                    c.find('2') != std::string::npos ||
                    c.find('3') != std::string::npos ||
                    c.find('4') != std::string::npos ||
                    c.find('5') != std::string::npos ||
                    c.find('6') != std::string::npos ||
                    c.find('7') != std::string::npos ||
                    c.find('8') != std::string::npos ||
                    c.find('9') != std::string::npos
            );
}

int MyUtility::byteArrayToInt(unsigned char byte1)
{
    unsigned char bytes[4];
    bytes[0] = byte1; bytes[1] = 0x00; bytes[2] = 0x00; bytes[3] = 0x00;
    int value;
    memcpy(&value, bytes, sizeof(int));
    return value;
}

int MyUtility::byteArrayToInt(unsigned char byte1, unsigned char byte2)
{
    unsigned char bytes[4];
    bytes[0] = byte1; bytes[1] = byte2; bytes[2] = 0x00; bytes[3] = 0x00;
    int value;
    memcpy(&value, bytes, sizeof(int));
    return value;
}

int MyUtility::byteArrayToInt(unsigned char byte1, unsigned char byte2, unsigned char byte3)
{
    unsigned char bytes[4];
    bytes[0] = byte1; bytes[1] = byte2; bytes[2] = byte3; bytes[3] = 0x00;
    int value;
    memcpy(&value, bytes, sizeof(int));
    return value;
}

int MyUtility::byteArrayToInt(unsigned char byte1, unsigned char byte2, unsigned char byte3, unsigned char byte4)
{
    unsigned char bytes[4];
    bytes[0] = byte1; bytes[1] = byte2; bytes[2] = byte3; bytes[3] = byte4;
    int value;
    memcpy(&value, bytes, sizeof(int));
    return value;
}
