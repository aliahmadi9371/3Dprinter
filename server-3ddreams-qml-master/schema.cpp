#include "schema.h"


Schema::~Schema()
{
}

bool Schema::checkIsNewColumnName(string name)
{
    for(int i=0; i<names.size(); i++) {
        if(names[i] == name) {
            return false;
        }
    }
    return true;
}



bool Schema::addColumn(string name, string type)
{
    if(checkIsNewColumnName(name)) {
        if(names.size() == 0) {
           sqlCommand = name + " " + type;
        } else {
            sqlCommand = sqlCommand + ", " + name + " " + type;
        }
        names.push_back(name);
        return true;
    }
    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
    return false;
}

bool Schema::addColumn(string name, string type, string defaultValue)
{
    if(checkIsNewColumnName(name)) {
        if(names.size() == 0) {
           sqlCommand = name + " " + type + " DEFAULT " + defaultValue;
        } else {
            sqlCommand = sqlCommand + ", " + name + " " + type + " DEFAULT " + defaultValue;
        }
        names.push_back(name);
        return true;
    }
    cout<< "Error: Schema addColumn: this " << name << "was added before please select new Name" << endl;
    return false;
}


