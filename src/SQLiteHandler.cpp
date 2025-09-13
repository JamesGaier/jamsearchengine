#include "SQLiteHandler.hpp"

#include <iostream>


namespace jam_crawler
{

SQLiteHandler::SQLiteHandler(const std::string &tableName)
: m_db("test.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
{
    createTable(tableName);
}

void SQLiteHandler::insertLink(const std::string &url)
{
    std::string query = "INSERT INTO test VALUES ('";
    query += url + "')";
    m_db.exec(query);
}

std::unordered_set<std::string> SQLiteHandler::keywordSearch(const std::string &keyword)
{
    std::string rawQuery = "SELECT * FROM links WHERE url LIKE '%";
    rawQuery += keyword + "%'";
    SQLite::Statement query(m_db, rawQuery);
    std::unordered_set<std::string> keywords;
    while (query.executeStep())
    {
        std::string link = query.getColumn(1);
        keywords.insert(link);
    }

    return keywords;
}


bool SQLiteHandler::containsLink(const std::string &keyword)
{
    std::string rawQuery = "SELECT * FROM links WHERE url =";
    rawQuery += keyword;
    SQLite::Statement query(m_db, rawQuery);
    while (query.executeStep())
    {
        std::string link = query.getColumn(1);
        if (link == keyword)
        {
            return true;
        }
    }

    return false;
}

void SQLiteHandler::createTable(const std::string &tableName)
{
    std::cout << "Creating table " << tableName << std::endl;
    std::string query = "CREATE TABLE IF NOT EXISTS ";
    query += tableName;
    query += " links (id INTEGER PRIMARY KEY, url TEXT)";
    m_db.exec(query);
}


}