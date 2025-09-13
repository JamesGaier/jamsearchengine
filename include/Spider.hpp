#pragma once
#include <string>
#include <queue>
#include <boost/circular_buffer.hpp>

#include "SQLiteHandler.hpp"


namespace jam_crawler
{


class Spider
{
public:
    Spider(const std::string &parentURL, int64_t queryDelay);

    void stop();

    // pass by copy because this could be in its own thread in the future maybe if I work on this more lol
    void crawl(SQLiteHandler &handler);
private:

    constexpr static auto MAX_LINKS_SIZE = 512;
    bool m_running{true};
    // replace me with circular queue so the queue doesn't fill up and get to being too big
    boost::circular_buffer<std::string> m_linksQueue;
    int64_t m_queryDelay;
};

}