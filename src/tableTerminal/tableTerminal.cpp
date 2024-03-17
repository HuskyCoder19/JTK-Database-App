#include <iostream>

#include "tableTerminal/tableTerminal.hpp"
#include "utils/utils.hpp"

using namespace tableTerminal;
using namespace jtkTable;
using namespace std;
using namespace utils;

TableTerminal::TableTerminal() {} // default constructor

void TableTerminal::enter(Table* pTable, const string& dbName) {

    cout << "Entering shell for table '" << pTable->getName() << "'" << endl;
    showCmds();

    bool val = true;

    while (val) {
        cout << "[jtkDB](" << dbName << ":"<< pTable->getName() << "): ";
        string cmd;
        getline(cin, cmd);
        val = parseCmds(cmd, pTable);
    }

}

void TableTerminal::showCmds() {

    cout << "   View table columns:             view" << endl;
    cout << "   Add column:                     add -c '<column_name>' '<data_type>'" << endl;
    cout << "   Add data to column:             add -d '<column_value>'" << endl;
    cout << "   Add full table row:             add -r " << endl;
    cout << "   Exit table shell:               exit" << endl;

}

bool TableTerminal::parseCmds(const string& cmd, Table* pTable) {

    string addColCmd = "add -c ";
    int pos;

    if (cmd == "view") {
        cout << endl;
        pTable->viewTable();
        cout << endl;
    } else if ((pos = cmd.find(addColCmd)) != string::npos) {

        // add table row
        string colInfo = cmd;
        colInfo.erase(pos, addColCmd.length());

        // find substring for table name and data type
        pos = colInfo.find(' ');
        if (pos != string::npos) {

            string colName = colInfo.substr(0, pos);
            string colType = colInfo.substr(pos+1, colInfo.length());

            // remove from quotes
            if (extractString(colName) && extractString(colType)) {
                if (pTable->addColumn(colName, colType)) {
                    cout << "Column '" << colName << "'added!" << endl;
                }
                else {
                    cerr << "error: Failed to create column." << endl;
                }
            }
        } else {
            cerr << "error: Unable to find column name and data type." << endl;
        }

    } else if (cmd == "exit") {
        return false;
    } else {
        cerr << "error: Command '" << cmd << "' not found" << endl;
    }

    return true;

}