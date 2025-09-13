#include "PageDownloader.hpp"
#include "CrawlerConfig.hpp"
#include <iostream>

constexpr static auto ARG_COUNT = 2;


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

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    

    return 0;
}