#ifndef SCHEMA_H
#define SCHEMA_H

#include <iostream>
#include <vector>
//#include <QVector>

using namespace std;

class Schema
{
public:
    ~Schema();
    string tableName;
    Schema(string tableName) : tableName(tableName) {
    }
    vector<string> names;
    string sqlCommand;

    bool addColumn(string name, string type);
    bool addColumn(string name, string type, string defaultValue);
    bool checkIsNewColumnName(string name);

};

#endif // SCHEMA_H
