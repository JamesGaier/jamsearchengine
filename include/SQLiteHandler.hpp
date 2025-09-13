#pragma once

#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <unordered_set>

namespace jam_crawler
{

// handles CRUD operations to sqllite database
class SQLiteHandler
{
public:

    SQLiteHandler(const std::string &tableName);

    void insertLink(const std::string &url);

    std::unordered_set<std::string> keywordSearch(const std::string &keyword);

    bool containsLink(const std::string &keyword);

private:

    SQLite::Database m_db;

    void createTable(const std::string &tableName);
};

}