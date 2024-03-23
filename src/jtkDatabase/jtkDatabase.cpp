#include <cstring>
#include <iostream>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>

#include "jtkDatabase/jtkDatabase.hpp"

using namespace jtkDatabase;
using namespace jtkTable;
using namespace std;

Database::Database() {} // default constructor

bool Database::initialize(const string& pDBName) {
    
    m_dbName = pDBName;

    string path = "../dbs/" + m_dbName;

    // Make directory for database if it doesn't exist
    if (!dirExists(path)) {

        //create directory using input path with read/write/execute permission
        int v = mkdir(path.c_str(), 0777);
        if (v != 0) {
            cerr << "error: Failed to create database" << endl;
            return false;
        }
        
    } else {
        initTables(); // build existing tables from existing directory
    }

    return true;
}

bool Database::addTable(const string& pTableName) {
    Table tab = Table();
    if (!tab.initialize(pTableName, m_dbName)) {
        return false;
    }
    m_tables.push_back(tab); // push to table vector
    return true;
}

bool Database::deleteTable(const string& pTableName) {
    cout << pTableName;
    return false;
}

bool Database::addTableRow(const string& tableName, const vector<pair<string, string>>& data) {

    int ind = getTableInd(tableName);

    if (ind >= 0) {
        m_tables[ind].addRow(data);
    }

    return false;
}

bool Database::addTableCol(const string& tableName, const string& colName, const string& colType) {

    int ind = getTableInd(tableName);
   
    if (ind >= 0) {
        return m_tables[ind].addColumn(colName, colType);
    }

    return false;
}

bool Database::getTableCols(const string& tableName, vector<pair<string, string>>& cols) {

    int ind = getTableInd(tableName);

    if (ind >= 0) {
        m_tables[ind].getCols(cols);
        return true;
    }

    return false;
}

bool Database::getTableData(const string& tableName, const vector<string>& cols, vector<vector<string>>& data) {

    int ind = getTableInd(tableName);

    if (ind >= 0) {
        m_tables[ind].getData(cols, data);
        return true;
    }

    return false;

}

vector<string> Database::getTableList() {

    vector<string> tabs;

    for(int i = 0 ; i < m_tables.size() ; i++) {
        tabs.push_back(m_tables[i].getName());
    }

    return tabs;
}

string Database::getName() {
    return m_dbName;
}

bool Database::dirExists(const string& path) {
    struct stat info;
    const char* c_path = path.c_str();
    if (stat(c_path, &info) != 0) {
        return false;
    } 
    return (info.st_mode & S_IFDIR) != 0;
}

int Database::getTableInd(const string& tableName) {

    for (int i = 0 ; i < m_tables.size() ; i++) {
        if (tableName == m_tables[i].getName()) {
            return i;
        }
    }
    return -1;

}

bool Database::getTable(const string& tableName, Table* pTable) {

    for (int i = 0 ; i < m_tables.size() ; i++) {
        if(tableName == m_tables[i].getName()) {
            *pTable = m_tables[i];
            return true;
        }
    }
    return false;

}

void Database::initTables() {

    string path = "../dbs/" + m_dbName; // directory path

    DIR* dir = opendir(path.c_str());
    if (dir == nullptr) {
        return;
    }

    dirent* d;
    // get each file in directory
    while ((d = readdir(dir)) != nullptr) {
        if (string(d->d_name) != "." && string(d->d_name) != "..") {
            string fn = d->d_name;
            //remove extension
            int pos = fn.find_last_of(".");
            if (pos != string::npos && fn.substr(pos) == ".txt") {
                fn = fn.substr(0, pos);
            }
            addTable(fn); // add table from file name
        }
    }

    closedir(dir);

}