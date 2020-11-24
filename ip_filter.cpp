#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "ip_filter.h"

std::vector<std::string> split(const std::string &str)
{
    std::vector<std::string> r;
    char d = '\t';
    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while(stop != std::string::npos)
    {
        r.push_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.push_back(str.substr(start));

    return r;
}
std::vector<uint32_t> split_ip(const std::string &str)
{
    std::vector<uint32_t> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of('.');
    uint32_t s2i;

    while(stop != std::string::npos)
    {
        s2i = stoi(str.substr(start, stop - start));
        r.push_back(s2i);

        start = stop + 1;
        stop = str.find_first_of('.', start);
    }

    s2i = stoi(str.substr(start));
    r.push_back(s2i);

    return r;
}

ipv4_validate::ipv4_validate(const std::string& in_str)
                : ipv4_regex(in_str) {}

bool ipv4_validate::operator()(const std::string& is_valid)
{
    return regex_match(is_valid, match, ipv4_regex);
}
