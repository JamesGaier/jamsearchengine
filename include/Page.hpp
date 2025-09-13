#pragma once

#include <string>
#include <curl/curl.h>
#include <unordered_set>

#include "SQLiteHandler.hpp"

namespace jam_crawler
{

struct Page
{
    std::unordered_set<std::string> urls;
    CURLcode code;

    Page() = default;
    Page(const std::string &rawPage, CURLcode code, SQLiteHandler &handler);
};

}