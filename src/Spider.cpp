#include "Spider.hpp"

#include "PageDownloader.hpp"
#include <iostream>

namespace jam_crawler
{

Spider::Spider(const std::string &parentURL)
{
    m_linksQueue.push(parentURL);
}

void Spider::crawl()
{
    while (m_running)
    {
        PageDownloader downloader;
        auto parentURL = m_linksQueue.front();
        Page curPage = downloader.requestPage(parentURL);

        if (curPage.code != CURLE_OK) {
            std::cerr << "CURL error (" << curPage.code << "): " 
                << curl_easy_strerror(curPage.code) << " - " << parentURL << std::endl;
            continue;
        }

        for (const auto& link : curPage.urls) 
        {
            m_linksQueue.push(link);
        }
    }
}

void Spider::stop()
{
    m_running = false;
}

}