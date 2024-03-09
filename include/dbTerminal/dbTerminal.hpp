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

    };

}

#endif