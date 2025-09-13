#include "Page.hpp"
#include "HtmlParser.hpp"

namespace jam_crawler
{

Page::Page(const std::string &rawPage, CURLcode code_)
: code(code_)
{
    urls = HtmlParser::parse(rawPage);
}

}