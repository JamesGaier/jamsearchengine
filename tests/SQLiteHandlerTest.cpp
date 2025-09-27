#include <gtest/gtest.h>

#include "SQLiteHandler.hpp"

#include <chrono>
#include <thread>


namespace {

constexpr static auto DB_NAME = "links";
constexpr static auto TABLE_NAME = "urls";
constexpr static auto IDS_ROW_NAME = "id";
constexpr static auto URLS_ROW_NAME = "url";
constexpr static auto TEST_LINK = "www.google.com";

class SQLiteHandlerTest : public testing::Test
{
protected:
    constexpr static auto BAD_LINK = "\"";
    constexpr static auto KEYWORD = "google";
    constexpr static auto NO_MATCH_KEYWORD = "blah";

    const std::unordered_set<std::string> EXPECTED_URLS = {
        "www.google.com"
    };

    const std::unordered_set<std::string> NO_MATCH_EXPECTED_URLS = {
    };


    jam_crawler::SQLiteHandler handler;

    SQLiteHandlerTest()
    : handler(
        DB_NAME, 
        TABLE_NAME,
        IDS_ROW_NAME,
        URLS_ROW_NAME
    )
{
    handler.removeLink(TEST_LINK);
    handler.removeLink(BAD_LINK);
}
};

class SQLiteHandlerExistingDbTest : public testing::Test
{
protected:
jam_crawler::SQLiteHandler handler;

    SQLiteHandlerExistingDbTest()
    : handler(
        DB_NAME, 
        TABLE_NAME,
        IDS_ROW_NAME,
        URLS_ROW_NAME
    )
    {
    }
};


TEST_F(SQLiteHandlerTest, TestInsertLink)
{
    EXPECT_TRUE(handler.insertLink(TEST_LINK));
    EXPECT_TRUE(handler.containsLink(TEST_LINK));
}

TEST_F(SQLiteHandlerTest, TestBadInsertLink)
{
    EXPECT_FALSE(handler.insertLink(BAD_LINK));
}

TEST_F(SQLiteHandlerTest, TestKeywordSearch)
{
    EXPECT_TRUE(handler.insertLink(TEST_LINK));
    EXPECT_TRUE(handler.containsLink(TEST_LINK));
    EXPECT_EQ(handler.keywordSearch(NO_MATCH_KEYWORD), NO_MATCH_EXPECTED_URLS);
}

TEST_F(SQLiteHandlerTest, TestBadKeywordSearch)
{
    EXPECT_TRUE(handler.insertLink(TEST_LINK));
    EXPECT_TRUE(handler.containsLink(TEST_LINK));
    EXPECT_EQ(handler.keywordSearch(BAD_LINK), NO_MATCH_EXPECTED_URLS);
}

TEST_F(SQLiteHandlerTest, TestBadContainsLink)
{
    EXPECT_TRUE(handler.insertLink(TEST_LINK));
    EXPECT_FALSE(handler.containsLink(BAD_LINK));
}

TEST_F(SQLiteHandlerExistingDbTest, TestExistingDb)
{
    EXPECT_TRUE(handler.insertLink(TEST_LINK));
}

}