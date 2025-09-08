#pragma once

#include <toml++/toml.hpp>

#include <vector>
#include <variant>
#include <iostream>
#include <typeinfo>

namespace jam_crawler
{

struct CrawlerConfig
{
    const std::string DOWNLOADER_NODE = "Downloader";
    const std::string SPIDER_NODE = "Spider";
    const std::string SEED_URL_NODE = "seed_urls";
    const std::string NUM_THREADS_NODE = "num_threads";
    toml::table crawlerConfig;
    std::vector<std::string> seedURLs;
    int64_t numThreads{};

    ~CrawlerConfig() = default;

    CrawlerConfig &operator=(const CrawlerConfig &copy);

    CrawlerConfig(const CrawlerConfig &copy);

    CrawlerConfig(const std::string &configPath);

    template <typename T, typename U>
    [[nodiscard]] T readNode(U parent, const std::string &nodeName)
    {
        auto childNode = parent[nodeName];
        T result;
        if constexpr (std::is_same<T, toml::array>::value)
        {
            result = *childNode.as_array();
        }
        else 
        {
            auto resultOpt = childNode.template value<T>();
            if (!resultOpt)
            {
                std::string strEx = nodeName + " Node not found in config...";
                throw strEx;
            }
            result = *resultOpt;
        }

        return result;
    }

    
    void copyArray(std::vector<std::string> &arr, const toml::array &array);
};


}