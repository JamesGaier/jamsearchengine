#include "crawler_v1_WebCrawlerController.h"
#include <drogon/orm/DbClient.h>
#include <drogon/orm/Exception.h>

#include <sstream>

using namespace crawler::v1;

// Add definition of your processing function here
void WebCrawlerController::search(
    const HttpRequestPtr& req, 
    std::function<void (const HttpResponsePtr &)> &&callback, 
    const std::string &searchQuery
)
{
    LOG_DEBUG << "User searched " << searchQuery << " On table " << TABLE_NAME << " On row " << ROW_NAME;

    auto dbClient = app().getDbClient("search_client");
    std::stringstream rawQuery;
    rawQuery << "SELECT * FROM " << TABLE_NAME << " WHERE " << ROW_NAME;
    rawQuery << " LIKE '%" << searchQuery << "%'";
    auto queryFuture = dbClient->execSqlAsyncFuture(rawQuery.str());

    Json::Value ret;
    try 
    {
        auto result = queryFuture.get();
        LOG_INFO << "Received " << result.size() << " results";
        for (const auto &row : result)
        {
            ret[ROW_NAME].append(row[ROW_NAME].as<std::string>());
        }
    }
    catch (const drogon::orm::DrogonDbException &ex)
    {
        LOG_ERROR << "Error:" << ex.base().what();
    }
    auto resp = HttpResponse::newHttpJsonResponse(ret);
    callback(resp);
}