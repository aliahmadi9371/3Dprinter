#ifndef ASSISTANT_H
#define ASSISTANT_H
#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include <thread>
#include <chrono>
#include <string>


#ifdef linux

#include <sys/statvfs.h>
#include <experimental/filesystem> // C++14

#endif

#ifdef _WIN32

#endif

using namespace std;

class Assistant
{
public:
    Assistant();
    static bool isFileExists(const std::string& name);
    static double getFreeMemorySpaceSizeToMB(const char *path);
    static double getFileSizeToMB(string file_path);
    static uint64_t getFileSizeToByte(string file_path);
    static void sleepMiliSecond(int ms);
    static string exec(const char* cmd);
    static bool isDirectory(string path);
    static bool isFile(string path);
};

#endif // ASSISTANT_H
