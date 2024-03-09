#ifndef _TABLE_TERMINAL_HPP
#define _TABLE_TERMINAL_HPP
#include <iostream>

#include "jtkTable/jtkTable.hpp"

namespace tableTerminal {

    class TableTerminal {

        public:
            
            TableTerminal();

            void enter(jtkTable::Table* pTable, const std::string& dbName);

        private:

            void showCmds();

            bool parseCmds(const std::string& cmd, jtkTable::Table* pTable);
    };

}

#endif