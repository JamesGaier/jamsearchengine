#include "Page.hpp"
#include <iostream>

namespace jam_crawler 
{

void Page::search_for_links(GumboNode* node, std::vector<std::string> &urls) {
    if (node->type != GUMBO_NODE_ELEMENT) {
        return;
    }
    
    GumboAttribute* href;
    if (node->v.element.tag == GUMBO_TAG_A &&
        (href = gumbo_get_attribute(&node->v.element.attributes, "href"))) {
        if (href->value) {
            urls.push_back(href->value);
        }
    }

    GumboVector* children = &node->v.element.children;
    for (unsigned int i = 0; i < children->length; ++i) {
        search_for_links(static_cast<GumboNode*>(children->data[i]), urls);
    }
}

std::vector<std::string> Page::filter(const std::vector<std::string> &urls)
{
    std::vector<std::string> answer;
    for (size_t i = 0; i < urls.size(); ++i)
    {
        auto link = urls[i];
        if ((link.rfind("http://", 0) != std::string::npos 
        || link.rfind("https://", 0) != std::string::npos)
        && link.find(" ") == std::string::npos) 
        {
            answer.push_back(link);
        }
    } 

    return answer;
}

std::vector<std::string> Page::parse(const std::string &rawPage)
{
    auto *node = gumbo_parse(rawPage.c_str());
    std::vector<std::string> urls;
    search_for_links(node->root, urls);
    gumbo_destroy_output(&kGumboDefaultOptions, node);

    urls = filter(urls);

    return urls;
}

}