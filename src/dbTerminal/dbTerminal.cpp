#include <iostream>
#include <utility>

#include "dbTerminal/dbTerminal.hpp"
#include "tableTerminal/tableTerminal.hpp"
#include "utils/utils.hpp"

using namespace dbTerminal;
using namespace tableTerminal;
using namespace jtkDatabase;
using namespace jtkTable;
using namespace std;
using namespace utils;

DBTerminal::DBTerminal() {} // default constructor

void DBTerminal::enter(Database* pDB) {

    cout << "Entering shell for database '" << pDB->getName() << "'" << endl;
    showCmds();

    bool val = true;

    while (val) {
        cout << "[jtkDB](" + pDB->getName() + "): ";
        string cmd;
        getline(cin, cmd);
        val = parseCmds(cmd, pDB);
    }

}

void DBTerminal::showCmds() {

    cout << "   Create table:           create -t '<table_name>'" << endl;
    cout << "   view tables:            view -all" << endl;
    cout << "   Add row of data:        add -r '<table_name>'" << endl;
    cout << "   Add table column:       add -c '<table_name>' '<column_name>' '<data_type>'" << endl;
    cout << "   Show commands:          view -cmds" << endl;
    cout << "   exit:                   exit" << endl;
}

bool DBTerminal::parseCmds(const string& cmd, Database* pDB) {

    string createCmd = "create -t ";
    string addRowCmd = "add -r ";
    string addColCmd = "add -c ";
    int pos;

    if ((pos = cmd.find(createCmd)) != string::npos) {
        
        string tableName = cmd;
        tableName.erase(pos, createCmd.length());
        if(extractString(tableName)) {
            if (pDB->addTable(tableName)) {
                cout << "Table '" << tableName << "' created!" << endl;
            } else {
                cerr << "error: Failed to create table '" << tableName << "'" << endl;
            }
        }

    } else if ((pos = cmd.find(addRowCmd)) != string::npos) { 
        
        string tableName = cmd;
        tableName.erase(pos, addRowCmd.length());
        if(extractString(tableName)) {
            vector<pair<string, string>> cols;
            pDB->getTableCols(tableName, cols);

            vector<pair<string, string>> colVals;
            for (int i = 0 ; i < cols.size() ; i++) {

                cout << "   " << cols[i].first << " (" << cols[i].second << "): ";
                string colVal;
                getline(cin, colVal);

                pair<string, string> cv(cols[i].first, colVal); // create column value pair

                colVals.push_back(cv);
            }

            pDB->addTableRow(tableName, colVals);

        }

    } else if ((pos = cmd.find(addColCmd)) != string::npos) {

        // add table column
        string str = cmd;
        str.erase(pos, addColCmd.length());
        addColHelper(str, pDB);
        
    } else if (cmd == "view -all") {
        
        cout << endl;
        pDB->viewTables();
        cout << endl;

    } else if (cmd == "exit") {
        return false;
    } else {
        cerr << "error: Command '" << cmd << "' not found" << endl;
    }

    return true;
}

void DBTerminal::addRowHelper(const string& tableName, Database* pDB) {

    // add data column by column 

}

void DBTerminal::addColHelper(const string& str, Database* pDB) {

    // parse table name and column info
    int pos = str.find(' ');
    if (pos != string::npos) {

        string tableName = str.substr(0, pos);
        string colInfo = str.substr(pos+1, str.length());

        // parse column name and data type
        pos = colInfo.find(' ');
        if (pos != string::npos) {
            string colName = colInfo.substr(0, pos);
            string colType = colInfo.substr(pos+1, colInfo.length());
            if (extractString(tableName) && extractString(colName) && extractString(colType)) {
                if (pDB->addTableCol(tableName, colName, colType)) {
                    cout << "Successfully created column!" << endl;
                } else {
                    cerr << "error: failed to create column." << endl;
                }
            }
        } else {
            cerr << "error: Failed to parse column name and data type." << endl;
        }
    } else {
        cerr << "error: Failed to parse table name." << endl;
    }

}

