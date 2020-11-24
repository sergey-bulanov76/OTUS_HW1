#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <iterator>
#include <experimental/iterator>
#include "ip_filter.h"

/*!
	\brief Домашнее задание №3 курса "C++ Developer. Professional" ООО «Отус онлайн-образование»
	\author Bulanov Sergey
	\version 0.0.1
	\date Novemer 2020
	\warning Функция создана только в учебных целях

	Реализация перегрузок функции печати условного IP-адреса посредством механизма SFINAE.
*/

int main(int, char const **)
{

    try
    {

        std::vector<std::vector<uint32_t> > ip_pool;
        ipv4_validate validatorIP;
        ipv4_validate validatorTwoTabs(".*\\t.*\\t.*");

        for(std::string line; std::getline(std::cin, line); )
        {
            //my validate: Does the string contain exactly two TABs?
            if(validatorTwoTabs(line))
            {
                std::vector<std::string> v = split(line);
                //my validate Ipv4
                if(validatorIP(v.at(0)))
                {
                    std::vector<uint32_t> vec_ip = split_ip(v.at(0));
                    ip_pool.push_back(vec_ip);
                }
            }
        }

        // TODO reverse sort
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<std::vector<uint32_t>>());

        //print vector
        auto printer = [](const auto& cont)
        {
            /*for(auto it = cont.cbegin(); it != cont.cend(); ++it)
            {
                if (it != cont.cbegin())
                    std::cout << ".";

                std::cout << *it;
            }*/
            std::copy(std::begin(cont), std::end(cont), std::experimental::make_ostream_joiner(std::cout, "."));
            std::cout << std::endl;
        };

        for(const auto& ip : ip_pool)
            printer(ip);

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first byte and output
        // ip = filter(1)
        for(const auto& ip : ip_pool)
            if(ip.at(0) == 1)
                printer(ip);

        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // TODO filter by first and second bytes and output
        // ip = filter(46, 70)

        for(const auto& ip : ip_pool)
            if(ip.at(0) == 46 && ip.at(1) == 70)
                printer(ip);

        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // TODO filter by any byte and output
        // ip = filter_any(46)

        for(const auto& ip : ip_pool)
            if(ip.at(0) == 46 || ip.at(1) == 46|| ip.at(2) == 46|| ip.at(3) == 46)
                printer(ip);

        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch(const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
