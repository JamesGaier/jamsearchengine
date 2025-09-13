#include "SQLiteHandler.hpp"

#include <iostream>


namespace jam_crawler
{

SQLiteHandler::SQLiteHandler(const std::string &tableName)
: m_db("test.db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
, m_tableName(tableName)
, m_curId(0)
{
    createTable();
}

void SQLiteHandler::insertLink(const std::string &url)
{
    std::string query = "INSERT INTO " + m_tableName;
    query += " VALUES (";
    query += std::to_string(m_curId++) + ",\"" + url + "\")";
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


bool SQLiteHandler::containsLink(const std::string &queryLink)
{
    std::string rawQuery = "SELECT * FROM " + m_tableName;
    rawQuery += " WHERE url =";
    rawQuery += "\"queryLink\"";
    SQLite::Statement query(m_db, rawQuery);
    while (query.executeStep())
    {
        std::string link = query.getColumn(1);
        if (link == queryLink)
        {
            return true;
        }
    }

    return false;
}

void SQLiteHandler::createTable()
{
    std::cout << "Creating table " << m_tableName << std::endl;
    std::string query = "CREATE TABLE IF NOT EXISTS ";
    query += m_tableName;
    query += " (id INTEGER PRIMARY KEY, url TEXT)";
    m_db.exec(query);
}


}