#ifndef _JTK_TABLE_HPP
#define _JTK_TABLE_HPP
#include <iostream>
#include <fstream>
#include <vector>
#include <map>

namespace jtkTable {

    class Table {

        public:

            Table();

            bool initialize(const std::string& tableName, const std::string& dbName);

            bool addColumn(const std::string& field, const std::string& type);

            bool addRow(const std::string& field, const std::string& data);

            void viewTable();

            std::string getName();

            enum class DataType {
                STRING,
                DOUBLE,
                FLOAT,
                INT,
                CHAR
            };

        private:

            struct TableCol {
                std::string name;
                DataType type;
                std::vector<std::string> data;
            };

            std::map<std::string, DataType> m_typeMap = {
                {"string", DataType::STRING},
                {"double", DataType::DOUBLE},
                {"float", DataType::FLOAT},
                {"int", DataType::INT},
                {"char", DataType::CHAR}
            };


            void buildTable(std::fstream* tabFile);

            std::vector<std::string> parseCSV(const std::string& ln);

            std::string extractType(std::string& str);

            std::vector<TableCol> m_tableCols;

            std::string m_tableName;

            std::string m_dbName;
    };

}

#endif