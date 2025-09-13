#pragma once

#include <string>
#include <curl/curl.h>

#include "Page.hpp"


namespace jam_crawler
{

// Downloads a page with curl
class PageDownloader
{
public:

    // cleanup the curl pointer
    ~PageDownloader();


    // init curl pointer
    PageDownloader();


    // for now this is going to be a string.  If I need to do more complex stuff It can get its own object
    // download a page from the internet
    Page requestPage(const std::string &url, SQLiteHandler &handler);

private:
    CURL* m_curl;

    // populates the response from the server to the client
    static size_t writeCallback(char* data, size_t size, size_t nmemb, void* userdata);
};

}