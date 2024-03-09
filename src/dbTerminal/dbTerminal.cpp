#include <iostream>

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
    cout << "   Enter table shell:      use '<table_name>'" << endl;
    cout << "   Show commands:          view -cmds" << endl;
    cout << "   exit:                   exit" << endl;
}

bool DBTerminal::parseCmds(const string& cmd, Database* pDB) {

    string createCmd = "create -t ";
    string useCmd = "use ";
    int pos;

    if ((pos = cmd.find(createCmd)) != string::npos) {
        
        string tableName = cmd;
        tableName.erase(pos, createCmd.length());
        if(extractString(tableName)) {
            if (pDB->addTable(tableName)) {
                // enter table's shell after creation
                cout << "Table '" << tableName << "' created!" << endl;
                cout << "   use -t '" << tableName << "' - enter table shell for editing." << endl;
            } else {
                cerr << "error: Failed to create table '" << tableName << "'" << endl;
            }
        }

    } else if (cmd == "view -all") {
        
        cout << endl;
        pDB->viewTables();
        cout << endl;

    } else if ((pos = cmd.find(useCmd)) != string::npos) {
        
        string tableName = cmd;
        tableName.erase(pos, useCmd.length());
        if(extractString(tableName)) {

            Table* pTab = new Table();
            if(pDB->getTable(tableName, pTab)) {
                // enter shell
                TableTerminal tableTerm = TableTerminal();
                tableTerm.enter(pTab, pDB->getName());
            }
            delete pTab; // free pointer memory
        }

    } else if (cmd == "exit") {
        return false;
    } else {
        cerr << "error: Command '" << cmd << "' not found" << endl;
    }

    return true;
}

