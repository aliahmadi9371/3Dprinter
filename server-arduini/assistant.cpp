#include "assistant.h"

Assistant::Assistant()
{

}

bool Assistant::isFileExists(const string &name)
{
    ifstream f(name.c_str());
    return f.good();
}

double Assistant::getFreeMemorySpaceSizeToMB(const char* path)
{
  #ifdef linux
    struct statvfs stat;

     if (statvfs(path, &stat) != 0) {
        cerr << "Assistant getFreeMemorySpaceSizeToMB can not get data, path: "<< path<<endl;
        return -1;
      }
//      cout<< "stat.f_bsize:"<<stat.f_bsize<<", stat.f_bavail:"<<stat.f_bavail<<endl;
      // the available size is f_bsize * f_bavail
      return stat.f_bsize * stat.f_bavail / 1000000; // divid is for converting num to MB
  #endif

  #ifdef _WIN32
    return 0;
   #endif
}

double Assistant::getFileSizeToMB(string file_path)
{
    struct stat stat_buf;
    int rc = stat(file_path.c_str(), &stat_buf);
    return rc == 0 ? (stat_buf.st_size/1000000) : -1;// divid is for converting num to MB
}

uint64_t Assistant::getFileSizeToByte(string file_path)
{
    ifstream file( file_path, ios::binary | ios::ate);
    uint64_t fileSize = file.tellg();
    file.close();
    return fileSize;
}

void Assistant::sleepMiliSecond(int ms)
{
    std::this_thread::sleep_for(std::chrono::milliseconds(ms));

}

string Assistant::exec(const char *cmd)
{
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        //throw std::runtime_error("popen() failed!");
        cerr << "popen() failed!";
        return "error";
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
         result += buffer.data();
    }
    return result;
}

bool Assistant::isFile(string path)
{
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
         if( s.st_mode & S_IFREG )
        {
             return true;
        }
    } else {
        cerr << "Assistant::isFile error path:"<<path;
    }
    return false;
}

bool Assistant::isDirectory(string path)
{
    struct stat s;
    if( stat(path.c_str(),&s) == 0 )
    {
        if( s.st_mode & S_IFDIR )
        {
            return true;
        }
    } else {
        cerr << "Assistant::isDirectory error path:"<<path;
    }
    return false;
}
