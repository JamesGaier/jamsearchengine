#pragma once
#include <string>
#include <queue>


namespace jam_crawler
{


class Spider
{
public:
    Spider(const std::string &parentURL);

    void stop();

private:
    // pass by copy because this could be in its own thread in the future maybe if I work on this more lol
    void crawl();

    bool m_running{true};
    // replace me with circular queue so the queue doesn't fill up and get to being too big
    std::queue<std::string> m_linksQueue;
};

}