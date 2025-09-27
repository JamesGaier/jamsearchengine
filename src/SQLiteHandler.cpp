#include "SQLiteHandler.hpp"

#include <iostream>


namespace jam_crawler
{

SQLiteHandler::SQLiteHandler(
    const std::string &dbName, 
    const std::string &tableName,
    const std::string &idsRowName,
    const std::string &urlsRowName
)
: m_db(dbName + ".db3", SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE)
, m_tableName(tableName)
, m_idsRowName(idsRowName)
, m_urlsRowName(urlsRowName)
, m_curId(0)
{
    auto success = createTable();
    if (!success)
    {
        std::cout << "Failed to create table " << m_tableName << std::endl;
    }

    // if the table already exists we want set the id to the largest id we have so far
    m_curId = getMaxId() + 1;
}

uint64_t SQLiteHandler::getMaxId()
{
    try
    {
        SQLite::Transaction transaction(m_db);
        std::stringstream queryStr; 
        queryStr << "SELECT MAX(" << "id" << ")" << " AS " << " MaxId " << " FROM " << m_tableName;
        SQLite::Statement query(m_db, queryStr.str());
        int64_t maxId = 0;
        while (query.executeStep())
        {
            maxId = std::max(maxId, query.getColumn(0).getInt64());
        }

        std::cout << "MAXID IS: " << maxId << std::endl;
        return maxId; 
    }
    catch(const std::exception& ex)
    {
        std::cerr << "Failed to get max id from db" << std::endl;
        std::cerr << ex.what() << std::endl;
        return 0;
    }
    
}

bool SQLiteHandler::insertLink(const std::string &url)
{
    try
    {
        SQLite::Transaction transaction(m_db);
        std::stringstream query; 
        query << "INSERT INTO " << m_tableName << " VALUES (";
        query << std::to_string(m_curId++) << ",\"" << url << "\")";
        m_db.exec(query.str());
        transaction.commit();
        return true;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error failed to insert " << url << " into " << m_tableName << std::endl;
        return false;
    }
}

void SQLiteHandler::removeLink(const std::string &url)
{
    try 
    {
        SQLite::Transaction transaction(m_db);
        std::stringstream queryStr;
        queryStr <<  "DELETE FROM " << m_tableName <<  " WHERE " << m_urlsRowName << "='" << url << "'";  
        m_db.exec(queryStr.str());
        transaction.commit();
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error failed to remove link " << url << " from " << m_tableName << std::endl;
    }
}

std::unordered_set<std::string> SQLiteHandler::keywordSearch(const std::string &keyword)
{
    try 
    {
        std::stringstream rawQuery;
        rawQuery << "SELECT * FROM " << m_tableName <<  " WHERE " << m_urlsRowName << " LIKE '%";
        rawQuery << keyword << "%'";
        SQLite::Statement query(m_db, rawQuery.str());
        std::unordered_set<std::string> keywords;
        while (query.executeStep())
        {
            std::string link = query.getColumn(1);
            keywords.insert(link);
        }

        return keywords;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error failed to get links from keyword " << keyword << " from " << m_tableName << std::endl;
        return {};
    }
}


bool SQLiteHandler::containsLink(const std::string &queryLink)
{
    try 
    {
        std::stringstream rawQuery;
        rawQuery << "SELECT * FROM " << m_tableName << " WHERE " << m_urlsRowName << "=";
        rawQuery  << "\"" << queryLink << "\"";
        SQLite::Statement query(m_db, rawQuery.str());
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
    catch (const std::exception &ex)
    {
        std::cerr << "Error failed to check if link " << queryLink << " is contained in " << m_tableName << std::endl;
        return false;
    }
}

bool SQLiteHandler::createTable()
{
    try
    {
        SQLite::Transaction transaction(m_db);
        std::stringstream query;
        query << "CREATE TABLE IF NOT EXISTS " <<  m_tableName << " (" << m_idsRowName;
        query << " INTEGER PRIMARY KEY, " << m_urlsRowName << " TEXT)";
        m_db.exec(query.str());
        transaction.commit();
        return true;
    }
    catch (const std::exception &ex)
    {
        std::cerr << "Error failed to create table " << m_tableName << std::endl;
        return false;
    }
}


}