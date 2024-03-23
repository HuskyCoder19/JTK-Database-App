#ifndef _DB_TERMINAL_HPP
#define _DB_TERMINAL_HPP
#include <iostream>

#include "jtkDatabase/jtkDatabase.hpp"

namespace dbTerminal {

    class DBTerminal {

        public:
            
            DBTerminal();

            void enter(jtkDatabase::Database* pDB);

        private:

            void showCmds();

            bool parseCmds(const std::string& cmd, jtkDatabase::Database* pDB);

            bool getTabDataHelper(std::string& str, jtkDatabase::Database* pDB, std::vector<std::vector<string>>& data);

            void addColHelper(const std::string& str, jtkDatabase::Database* pDB);

    };

}

#endif