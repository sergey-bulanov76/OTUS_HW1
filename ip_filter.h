#ifndef IP_FILTER_H_INCLUDED
#define IP_FILTER_H_INCLUDED

#include <regex>

std::vector<std::string> split(const std::string &str);
std::vector<uint32_t> split_ip(const std::string &str);
struct ipv4_validate{

    ipv4_validate(const std::string& in_str = "((25[0-5]|2[0-4]\\d|[01]?\\d\\d?)\\.){3}(25[0-5]|2[0-4]\\d|[1]?\\d\\d?)");

    bool operator()(const std::string&);

    std::regex ipv4_regex;
    std::smatch match;
};

#endif // IP_FILTER_H_INCLUDED
