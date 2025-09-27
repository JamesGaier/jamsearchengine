#pragma once

#include <SQLiteCpp/SQLiteCpp.h>

#include <string>
#include <unordered_set>
#include <random>

namespace jam_crawler
{

// handles CRUD operations to sqllite database
class SQLiteHandler
{
public:

    SQLiteHandler(
        const std::string &dbName, 
        const std::string &tableName,
        const std::string &idsRowName,
        const std::string &urlsRowName
    );

    [[nodiscard]] bool insertLink(const std::string &url);

    void removeLink(const std::string &url);

    [[nodiscard]] std::unordered_set<std::string> keywordSearch(const std::string &keyword);

    [[nodiscard]] bool containsLink(const std::string &queryLink);

private:
    SQLite::Database m_db;
    const std::string m_tableName;
    const std::string m_idsRowName;
    const std::string m_urlsRowName;
    uint64_t m_curId;

    [[nodiscard]] bool createTable();

    [[nodiscard]] uint64_t getMaxId();

};

}