#include "Spider.hpp"

#include "PageDownloader.hpp"
#include <iostream>
#include <chrono>
#include <thread>

namespace jam_crawler
{

Spider::Spider(const std::string &parentURL, int64_t delay)
: m_linksQueue(MAX_LINKS_SIZE)
, m_queryDelay(delay)
{
    m_linksQueue.push_back(parentURL);
}

void Spider::crawl(SQLiteHandler &handler)
{
    while (m_running)
    {
        PageDownloader downloader;
        auto parentURL = m_linksQueue.front();
        std::cout << "Crawling: " <<  parentURL << std::endl; 
        handler.insertLink(parentURL);
        m_linksQueue.pop_front();
        Page curPage = downloader.requestPage(parentURL, handler);

        if (curPage.code != CURLE_OK) {
            std::cerr << "CURL error (" << curPage.code << "): " 
                << curl_easy_strerror(curPage.code) << " - " << parentURL << std::endl;
            continue;
        }

        for (const auto& link : curPage.urls) 
        {
            m_linksQueue.push_back(link);
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(m_queryDelay));
    }
}

void Spider::stop()
{
    m_running = false;
}

}