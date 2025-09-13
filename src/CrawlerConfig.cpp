#include "CrawlerConfig.hpp"

#include <iostream>

namespace jam_crawler
{

CrawlerConfig &CrawlerConfig::operator=(const CrawlerConfig &copy)
{
    crawlerConfig = copy.crawlerConfig;
    seedURLs = copy.seedURLs;
    numThreads = copy.numThreads;
    return *this;    
}

CrawlerConfig::CrawlerConfig(const CrawlerConfig &copy)
{
    operator=(copy);
}
    
void CrawlerConfig::copyArray(std::vector<std::string> &vec, const toml::array &array)
{
    for (const auto &el : array)
    {
        std::string str = static_cast<std::string>(*el.as_string());
        vec.push_back(str);
    }
}

CrawlerConfig::CrawlerConfig(const std::string &configPath)
{
    // we don't want to catch exceptions being thrown so it will bubble up the exception to client
    crawlerConfig = toml::parse_file(configPath);
    auto downloaderNode = crawlerConfig[DOWNLOADER_NODE];
    auto seedUrlArray = readNode<toml::array>(downloaderNode, SEED_URL_NODE);
    copyArray(seedURLs, seedUrlArray);
    queryDelay = readNode<int64_t>(downloaderNode, DELAY_NODE);

    auto spiderNode = crawlerConfig[SPIDER_NODE];
    auto numThreadsNode = readNode<int64_t>(spiderNode, NUM_THREADS_NODE);
    numThreads = numThreadsNode;
}

}