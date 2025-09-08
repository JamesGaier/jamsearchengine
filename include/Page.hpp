#pragma once
#include <curl/curl.h>
#include <string> 
#include <vector>
#include "gumbo.h"

namespace jam_crawler
{

class Page 
{
public:

static std::vector<std::string> parse(const std::string &rawPage);


private:
    static void search_for_links(GumboNode* node, std::vector<std::string> &urls);

    static std::vector<std::string> filter(const std::vector<std::string> &urls);
};

}