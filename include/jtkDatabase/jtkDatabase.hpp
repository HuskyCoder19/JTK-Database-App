#ifndef _JTK_DATABASE_HPP
#define _JTK_DATABASE_HPP
#include <iostream>
#include <vector>

#include "jtkTable/jtkTable.hpp"

namespace jtkDatabase {

    class Database {

        public:

            Database();

            bool initialize(const std::string& pDBName);

            bool addTable(const std::string& pTableName);

            bool deleteTable(const std::string& pTableName);

            bool getTable(const std::string& tableName, jtkTable::Table* pTable);

            void viewTables();

            std::string getName();

        private:

            bool dirExists(const std::string& path);

            void initTables();
        
            std::string m_dbName; // name of database

            std::vector<jtkTable::Table> m_tables; // vector of the database's tables

    };

}

#endif