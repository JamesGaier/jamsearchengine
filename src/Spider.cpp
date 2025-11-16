#include "Spider.hpp"

#include "PageDownloader.hpp"
#include <iostream>
#include <chrono>
#include <thread>

#include "Logger.hpp"

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
        if (m_linksQueue.empty())
        {
            LOG_ERROR("Links queue is empty exiting...");
            break;
        }

        auto parentURL = m_linksQueue.front();
        m_linksQueue.pop_front();
        LOG_INFO("Crawling: %s", parentURL.c_str());
        bool success = handler.insertLink(parentURL);
        if (!success)
        {
            LOG_ERROR("Error! Failed to insert %s into database", parentURL.c_str());
        }

        Page curPage = downloader.requestPage(parentURL, handler);

        if (curPage.code != CURLE_OK) {
            LOG_ERROR("CURL error (%d): %s - %s", curPage.code, curl_easy_strerror(curPage.code), parentURL.c_str());
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