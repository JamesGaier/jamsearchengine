#include "PageDownloader.hpp"
#include "CrawlerConfig.hpp"
#include "Spider.hpp"
#include <iostream>
#include <csignal>
#include <functional>

constexpr static auto ARG_COUNT = 2;
constexpr static auto TABLE_NAME = "urls";


void singalHandler(int sig)
{
    std::cout << "Closing webcrawler" << std::endl;

    _exit(sig);
}


int main(int argc, char *argv[])
{
    if (argc != ARG_COUNT)
    {
        std::cerr << "Program uses one argument: ./jam-web-crawler [config-file-path]\n";
        return 1;
    }

    try
    {
        jam_crawler::CrawlerConfig config(argv[1]);
        jam_crawler::SQLiteHandler handler(TABLE_NAME);
        jam_crawler::Spider spider(config.seedURLs[0], config.queryDelay);
        signal(SIGINT, singalHandler);
        spider.crawl(handler);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    

    return 0;
}