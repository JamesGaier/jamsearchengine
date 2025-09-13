#include "HtmlParser.hpp"
#include <iostream>

namespace jam_crawler 
{

void HtmlParser::search_for_links(GumboNode* node, std::unordered_set<std::string> &urls) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        if (href->value) {
            urls.insert(href->value);
        }
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        search_for_links(static_cast<GumboNode*>(children->data[i]), urls);
    }
}

std::unordered_set<std::string> HtmlParser::filter(const std::unordered_set<std::string> &urls, SQLiteHandler &handler)
{
    std::unordered_set<std::string> answer;
    for (const auto &link : urls)
    {
        if ((link.rfind("http://", 0) != std::string::npos 
        || link.rfind("https://", 0) != std::string::npos)
        && link.find(" ") == std::string::npos
        && !handler.containsLink(link)) 
        {
            answer.insert(link);
        }
    } 

    return answer;
}

std::unordered_set<std::string> HtmlParser::parse(const std::string &rawHtmlParser, SQLiteHandler &handler)
{
    auto *node = gumbo_parse(rawHtmlParser.c_str());
    std::unordered_set<std::string> urls;
    search_for_links(node->root, urls);
    gumbo_destroy_output(&kGumboDefaultOptions, node);

    urls = filter(urls, handler);

    return urls;
}

}