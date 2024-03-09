#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>

#include "jtkDatabase/jtkDatabase.hpp"
#include "dbTerminal/dbTerminal.hpp"
#include "utils/utils.hpp"

using namespace dbTerminal;
using namespace jtkDatabase;
using namespace std;
using namespace utils;

void showCmds();
bool parseMainCmds(const string& cmd, DBTerminal& dbTerm);
int findDB(string dbName);
void generateDBs();

vector<Database> dbs;

int main() {

    generateDBs();

    cout << "Welcome to database builder!" << endl;
    showCmds();

    DBTerminal dbTerm = DBTerminal();

    bool val = true;

    while (val) {

        string cmd;
        cout << "[jtkDB]: ";
        getline(cin, cmd);

        val = parseMainCmds(cmd, dbTerm);
    }

    return 0;
}

// show commands
void showCmds() {
    cout << "   Create new database:       create -db '<database_name>'" << endl;
    cout << "   Enter database shell:      use '<database_name>'" << endl;
    cout << "   Delete database:           delete -db '<database_name>'" << endl;
    cout << "   View all databases:        view -all" << endl;
    cout << "   Exit program:              exit" << endl;
}

// parse commands
bool parseMainCmds(const string& cmd, DBTerminal& dbTerm) {

    string createCmd = "create -db ";
    string useCmd = "use ";
    int pos;

    bool retVal = true;

    if ((pos = cmd.find(createCmd)) != string::npos) {

        string dbName = cmd;
        dbName.erase(pos, createCmd.length());

        if (extractString(dbName)) {

            // check for existing database
            if (findDB(dbName) >= 0) {
                cerr << "error: Database '" << dbName << "' already exists" << endl;
            } else {
                Database db = Database();
                if(db.initialize(dbName)){
                    cout << "database '" << dbName << "'created!" << endl;
                    dbs.push_back(db); // push to database vector
                }
            }
        }

    } else if ((pos = cmd.find(useCmd)) != string::npos) {

        string dbName = cmd;
        dbName.erase(pos, useCmd.length());
        if (extractString(dbName)) {
            int ind = findDB(dbName);
            if (ind >= 0) {
                dbTerm.enter(&dbs[ind]);
            } else {
                cerr << "error: Database '" << dbName << "' not found" << endl;
            }
        
        }
    } else if (cmd == "view -all") {

        for (int i = 0 ; i < dbs.size() ; i++) {
            cout << dbs[i].getName() << endl;
        }

    } else {
        cerr << "error: Command not found" << endl;
    }

    return retVal;

}

int findDB(string dbName) {

    for (int i = 0 ; i < dbs.size() ; i++) {

        if (dbName == dbs[i].getName()) {
            return i;
        } 
    }

    return -1;

}

void generateDBs() {
    // generate database objects from existing database directories in {root}/dbs
    string path = "../dbs";
    DIR* dir = opendir(path.c_str());
    if (dir != nullptr) {
        struct dirent* d;
        while ((d = readdir(dir)) != nullptr) {
            if (d->d_type == DT_DIR && string(d->d_name) != "." && string(d->d_name) != "..") {
                Database db = Database();
                if (db.initialize(d->d_name)) {
                    dbs.push_back(db);
                }
            }
        }
        closedir(dir);
    }
}
