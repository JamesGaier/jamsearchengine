#include "SQLiteHandler.hpp"

#include <iostream>

#include "Logger.hpp"

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
        LOG_ERROR("Failed to create table %s", m_tableName.c_str());
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

        return maxId; 
    }
    catch(const std::exception& ex)
    {
        LOG_ERROR("Failed to get max id from db");
        LOG_ERROR("%s", ex.what());
        return 0;
    }
    
}

bool SQLiteHandler::insertLink(const std::string &url)
{
    try
    {
        if (containsLink(url))
        {
            LOG_ERROR("DB already contains link...");
            return false;
        }

        SQLite::Transaction transaction(m_db);
        std::stringstream query; 
        query << "INSERT INTO " << m_tableName << " VALUES (";
        query << std::to_string(m_curId++) << ",\"" << url << "\")";

        // check that the link is not already in the db first

        m_db.exec(query.str());
        transaction.commit();
        return true;
    }
    catch (const std::exception &ex)
    {
        LOG_ERROR("Error is: %s", ex.what());
        LOG_ERROR("Error failed to insert %s into %s", url.c_str(), m_tableName.c_str());
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
        LOG_ERROR("Error failed to remove link %s from %s", url.c_str(), m_tableName.c_str());
        LOG_ERROR("Error: %s", ex.what());
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
        LOG_ERROR("Error failed to get links from keyword %s from %s", keyword.c_str(), m_tableName.c_str());
        LOG_ERROR("Error: %s", ex.what());
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
        LOG_ERROR("Error failed to check if link  %s is contained in %s", queryLink.c_str(), m_tableName.c_str());
        LOG_ERROR("Error: %s", ex.what());
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
        LOG_ERROR("Error failed to create table %s", m_tableName.c_str());
        LOG_ERROR("Error: %s", ex.what());
        return false;
    }
}


}