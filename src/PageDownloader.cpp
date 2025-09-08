#include "PageDownloader.hpp"

#include <iostream>

namespace jam_crawler
{

PageDownloader::~PageDownloader()
{
    curl_easy_cleanup(m_curl);
}

PageDownloader::PageDownloader()
{
    m_curl = curl_easy_init();
    if (!m_curl) {
        throw "CURL initialization failed ";
    }
}

size_t PageDownloader::writeCallback(char* data, size_t size, size_t nmemb, void* userdata) 
{
    std::string* response = static_cast<std::string*>(userdata);
    size_t total_size = size * nmemb;
    response->append(data, total_size);
    return total_size;
}

Page PageDownloader::requestPage(const std::string &url)
{
    std::string response;
    curl_easy_setopt(m_curl, CURLOPT_URL, url.c_str());

    curl_easy_setopt(m_curl, CURLOPT_WRITEFUNCTION, PageDownloader::writeCallback);
    curl_easy_setopt(m_curl, CURLOPT_WRITEDATA, &response);
    curl_easy_setopt(m_curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    curl_easy_setopt(m_curl, CURLOPT_FOLLOWLOCATION, 1L);
    curl_easy_setopt(m_curl, CURLOPT_ACCEPT_ENCODING, "");
    curl_easy_setopt(m_curl, CURLOPT_TIMEOUT, 10L);  // 10-second timeout
    
    CURLcode code = curl_easy_perform(m_curl);
    if (code != CURLE_OK) {
        std::cerr << "CURL error (" << code << "): " 
            << curl_easy_strerror(code) << " - " << url << std::endl;
    }

    return {code, response};
}

}