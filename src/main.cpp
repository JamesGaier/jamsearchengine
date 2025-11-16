#include "PageDownloader.hpp"
#include "CrawlerConfig.hpp"
#include "Spider.hpp"
#include <iostream>
#include <csignal>
#include <functional>

#include "Logger.hpp"


constexpr static auto ARG_COUNT = 2;


void singalHandler(int sig)
{
    LOG_INFO("CTRL+C Pressed exiting...");

    _exit(sig);
}


int main(int argc, char *argv[])
{
    if (argc != ARG_COUNT)
    {
        LOG_ERROR("Program uses one argument: ./jam-web-crawler [config-file-path]");
        return 1;
    }

    try
    {
        jam_crawler::CrawlerConfig config(argv[1]);
        LOG_INFO("Starting web crawler");
        jam_crawler::SQLiteHandler handler(
            config.dbName, 
            config.tableName, 
            config.idsRowName,
            config.urlsRowName
        );
        jam_crawler::Spider spider(config.seedURLs[0], config.queryDelay);
        signal(SIGINT, singalHandler);
        signal(SIGTERM, singalHandler);
        spider.crawl(handler);
    }
    catch(const std::exception& ex)
    {
        LOG_ERROR("%s", ex.what());
        return 1;
    }
    

    return 0;
}