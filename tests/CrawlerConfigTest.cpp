#include <gtest/gtest.h>

#include "CrawlerConfig.hpp"


namespace {

class CrawlerConfigTest : public testing::Test
{
protected:
    const std::string CONFIG_PATH = "/home/jamesgaier/Documents/jamsearchengine/tests/test_config.toml";
    const std::vector<std::string> EXPECTED_SEED_URLS = {
        "http://wikipedia.org/"
    };

    const std::vector<std::string> EXPECTED_COPY_OUTPUT = {
        "1", "2"
    };
    constexpr static size_t EXPECTED_NUM_THREADS = 10;
    CrawlerConfigTest()
    : config(CONFIG_PATH)
    {
    }

    void reset(const std::string &path)
    {
        config = jam_crawler::CrawlerConfig(path);
    }

    jam_crawler::CrawlerConfig config;
};

TEST_F(CrawlerConfigTest, ReadTOML)
{
    EXPECT_TRUE(config.seedURLs == EXPECTED_SEED_URLS);
    EXPECT_EQ(config.numThreads, EXPECTED_NUM_THREADS);

    std::vector<std::string> words;
    toml::array arr = toml::array{ "1", "2" };
    config.copyArray(words, arr);
    EXPECT_EQ(words, EXPECTED_COPY_OUTPUT);
}

TEST_F(CrawlerConfigTest, WrongFilename)
{
    EXPECT_ANY_THROW(reset("wrongPath.fjfjf"));
}



}