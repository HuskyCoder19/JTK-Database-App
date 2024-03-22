#ifndef _JTK_DATABASE_HPP
#define _JTK_DATABASE_HPP
#include <iostream>
#include <vector>
#include <utility>

#include "jtkTable/jtkTable.hpp"

namespace jtkDatabase {

    class Database {

        public:

            Database();

            bool initialize(const std::string& pDBName);

            bool addTable(const std::string& pTableName);

            bool deleteTable(const std::string& pTableName);

            bool getTable(const std::string& tableName, jtkTable::Table* pTable);

            bool addTableRow(const std::string& tableName, const std::vector<std::pair<std::string, std::string>>& data);

            bool addTableCol(const std::string& tableName, const std::string& colName, const std::string& colType);

            bool getTableCols(const std::string& tableName, std::vector<std::pair<std::string, std::string>>& cols);

            void viewTables();

            std::string getName();

        private:

            bool dirExists(const std::string& path);

            void initTables();

            int getTableInd(const std::string& tableName); // get index of table from table name
        
            std::string m_dbName; // name of database

            std::vector<jtkTable::Table> m_tables; // vector of the database's tables

    };

}

#endif