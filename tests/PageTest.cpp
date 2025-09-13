#include <gtest/gtest.h>

#include "HtmlParser.hpp"

namespace {

class ParserTest : public testing::Test
{
protected:

    const std::string page = R"(
        <html>
            <div>
                <a href="https://lamb.com">a lamb</a>
                <a href="https://ram.com">ram</a>
                <a href="https://bam.com">bam</a>
                <a href="fake-lamb.com">bam</a>
                <a href="bam.comhttps://">bam</a>
                <a href="https:// bam.com">bam</a>
            </div>
        </html>
    )";
    const std::unordered_set<std::string> expectedLinks = {
        "https://lamb.com",
        "https://ram.com",
        "https://bam.com"
    };
};


TEST_F(ParserTest, TestParsingLinks)
{
    auto result = jam_crawler::HtmlParser::parse(page);
    EXPECT_EQ(result, expectedLinks);
}

}