#include <cstring>
#include <iostream>
#include <fstream>
#include <string>
#include <string.h>

#include "jtkTable/jtkTable.hpp"

using namespace jtkTable;
using namespace std;

Table::Table() {} // default constructor

bool Table::initialize(const string& tableName, const string& dbName) {
    
    m_tableName = tableName;
    m_dbName = dbName;

    string path = "../dbs/" + m_dbName + "/" + m_tableName + ".txt";

    fstream tabFile;

    // open file for read/wrie, create if it doesn't exist
    tabFile.open(path, fstream::in | fstream::out | fstream::app);

    if (!tabFile.is_open()) {
        cerr << "error: Failed to open table '" << m_tableName << "'" << endl;
        return false;
    }

    // construct table from file
    buildTable(&tabFile);

    tabFile.close(); // close the table's file 

    return true;
}

bool Table::addColumn(const string& field, const string& type) {
    return true;
}

bool Table::addRow(const string& field, const string& data) {
    return true;
}

void Table::viewTable() {

    cout << "   " << m_tableName << ": ";

    if (!m_tableCols.size()) {
        cout << "none" << endl;
        return;
    }

    for (int i = 0 ; i < m_tableCols.size() ; i++) {

        if(i > 0) {
            cout << "; ";
        }

        cout << m_tableCols[i].name << " ";
        switch(m_tableCols[i].type) {
            case DataType::STRING:
                cout << "(string)";
                break;
            case DataType::FLOAT:
                cout << "(float)";
                break;
            case DataType::DOUBLE:
                cout << "(double)";
                break;
            case DataType::INT:
                cout << "(int)";
                break;
            case DataType::CHAR:
                cout << "(char)";
                break;
            default:
                cout << "(NULL)";
                break;
        }
    }
    cout << endl;
}

string Table::getName() {
    return m_tableName;
}

void Table::buildTable(fstream* tabFile) {

    tabFile->seekg(0); // set position to start of file

    // check if file has contents
    if (tabFile->peek() != ifstream::traits_type::eof()) {
        
        tabFile->seekg(0);

        string ln;
        bool firstIt = true;

        while (getline(*tabFile, ln)) {
            
            vector<string> row = parseCSV(ln); // save columns to vector

            if (firstIt) {

                // construct new table column for each column read in
                for (int i = 0 ; i < row.size() ; i++) {
                    string name = row[i];
                    string type = extractType(name); //remove data type
            
                    if (type.empty()) {
                        type = "string"; // default to type string if none found
                    }

                    // add table column
                    TableCol col;
                    col.name = name;
                    DataType dt = m_typeMap[type]; // map to data type
                    col.type = dt;

                    m_tableCols.push_back(col);
                }
                firstIt = false;

            } else {

                if (row.size()){
                    // add table row data to table columns
                    for (int i = 0 ; i < m_tableCols.size() ; i++) {
                        if (i < row.size()) {
                            m_tableCols[i].data.push_back(row[i]); // add to table column data vector
                        } else {
                            m_tableCols[i].data.push_back("NULL"); // fill in missing table row data
                        }
                    }
                }

            }
        }

    }

}

vector<string> Table::parseCSV(const string& ln) {
    
    vector<string> vals;

    int start = 0;
    int strSz = 0;

    for (int i = 0 ; i < ln.length() ; i++) {
        if (ln[i] == ',') {
            
            if (strSz > 0) {
                string str = ln.substr(start, strSz);
                vals.push_back(str);
            } else {
                vals.push_back("NULL");
            }
            strSz = 0;
            start = i + 1;
        } else if (i == ln.length()-1) {
            string str = ln.substr(start, strSz+1);
            vals.push_back(str);
        } else {
            strSz++;
        }
    }

    return vals;
}

string Table::extractType(string& str) {

    int start = str.find('(');
    int end = str.find(')');

    string type = "";

    if (start != string::npos && end != string::npos) {
        type = str.substr(start+1, end-start-1); // remove string between parantheses
        str.erase(start, end-start+1); // remove from original string
    }

    return type;

}