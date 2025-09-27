#pragma once

#include <drogon/HttpController.h>

using namespace drogon;

namespace crawler
{
namespace v1
{
class WebCrawlerController : public drogon::HttpController<WebCrawlerController>
{
  public:
    // I am choosing to hardcode this info because I don't want someone to inject sql queries if I make the table name
    // configurable through the search queries
    // I could read from a file but I am only using one db so it doesn't make sense to do that here...
    constexpr static auto TABLE_NAME = "links";
    constexpr static auto ROW_NAME = "url";
    METHOD_LIST_BEGIN
    ADD_METHOD_TO(WebCrawlerController::search, "/search?q1={1}", Get);

    METHOD_LIST_END
    // your declaration of processing function maybe like this:
    void search(
      const HttpRequestPtr& req, 
      std::function<void (const HttpResponsePtr &)> &&callback, 
      const std::string &searchQuery
    );
};
}
}
