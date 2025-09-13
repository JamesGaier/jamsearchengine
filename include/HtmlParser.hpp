#pragma once
#include <curl/curl.h>
#include <string> 
#include <unordered_set>
#include "gumbo.h"

namespace jam_crawler
{

class HtmlParser
{
public:

static std::unordered_set<std::string> parse(const std::string &rawPage);


private:
    static void search_for_links(GumboNode* node, std::unordered_set<std::string> &urls);

    static std::unordered_set<std::string> filter(const std::unordered_set<std::string> &urls);
};

}