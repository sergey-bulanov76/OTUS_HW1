#include "ip_filter.h"
#include <gtest/gtest.h>
#include <vector>
#include <random>
#include <limits>


TEST(split_string, without_TAB) {

    // Arrange
    std::string str{""};

    // Act
    std::vector<std::string> keeper = split(str);

    // Assert
    ASSERT_EQ(keeper.size(), 1);

}

TEST(split_string, one_TAB) {

    // Arrange
    std::string str{"1\t2"};

    // Act
    std::vector<std::string> keeper = split(str);

    // Assert
    ASSERT_EQ(keeper.size(), 2);

}

TEST(split_string, two_TAB) {

    // Arrange
    std::string str{"1\t2\tnexttxt"};

    // Act
    std::vector<std::string> keeper = split(str);

    // Assert
    ASSERT_EQ(keeper.size(), 3);

}

TEST(split_string, more_than_two_TAB) {

    // Arrange
    std::string str{"1\t2\tn\ne\tx\tt\nt\vx\tt"};

    // Act
    std::vector<std::string> keeper = split(str);

    // Assert
    ASSERT_EQ(keeper.size(), 6);

}

TEST(split_ip, test_valid_IPv4) {

    // Arrange
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis_ui(0, 255);
    auto rand_string_IPv4 = [&dis_ui, &gen]()
    {
        return std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen)) + "."
               + std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen));
    };

    // Act
    std::vector<std::vector<uint32_t>> keeper(10000);
    for(unsigned i{0}; i < 10000; ++i)
        keeper.at(i) = split_ip(rand_string_IPv4());

    // Assert
    ASSERT_EQ(keeper.size(), 10000);

}

TEST(regexprTABS, in_string_exactly_two_TABs) {

    // Arrange
    ipv4_validate validatorTwoTabs(".*\\t.*\\t.*");
    std::vector<std::string> keeper{"", "jkgjfjaiewi", "a\tb", "a\tbcbn\tcvmnc", "a\tb\t", "\tb\tjfdgfdklg\t  \t",  "1\t2\tn\ne\tx\tt\nt\vx\tt"};
    std::vector<std::string> valid_str;

    // Act
    for(unsigned i{0}; i < 7; ++i)
    {
        if(validatorTwoTabs(keeper.at(i)))
            valid_str.push_back(keeper.at(i));
    }

    // Assert
    ASSERT_EQ(valid_str.size(), 3);

}

TEST(regexprIP, test_valid_IPv4) {

    // Arrange
    ipv4_validate validatorIP;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis_ui(0, 255);
    auto rand_string_IPv4 = [&dis_ui, &gen]()
    {
        return std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen)) + "."
               + std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen));
    };

    // Act
    std::vector<std::string> keeper;
    for(unsigned i{0}; i < 10000; ++i)
    {
        std::string str = rand_string_IPv4();
        if(validatorIP(str))
            keeper.push_back(str);
    }

    // Assert
    ASSERT_EQ(keeper.size(), 10000);

}

TEST(regexprIP, first_invalid_IPv4) {

    // Arrange
    ipv4_validate validatorIP;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<unsigned int> dis_ui(256, std::numeric_limits<unsigned int>::max());
    auto rand_string_IPv4 = [&dis_ui, &gen]()
    {
        return std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen)) + "."
               + std::to_string(dis_ui(gen)) + "." + std::to_string(dis_ui(gen));
    };

    // Act
    std::vector<std::string> keeper;
    for(unsigned i{0}; i < 10000; ++i)
    {
        std::string str = rand_string_IPv4();
        if(validatorIP(str))
            keeper.push_back(str);
    }

    // Assert
    ASSERT_EQ(keeper.size(), 0);

}

TEST(regexprIP, second_invalid_IPv4) {

    // Arrange
    ipv4_validate validatorIP;
    std::vector<std::string> keeper{"", "0", "1.1", ".11", "11.",
                                    ".22.2", "2.2.2",
                                    "3.3.3.", ".3.3.3", ".3.33.", "...",
                                    "4.4.4.4.4", ".44.4.444.",
                                    "5.5.5.5.5.5"};
    std::vector<std::string> valid_str;

    // Act

    for(unsigned i{0}; i < 14; ++i)

        if(validatorIP(keeper.at(i)))

            valid_str.push_back(keeper.at(i));

    // Assert
    ASSERT_EQ(valid_str.size(), 0);

}

int main(int argc, char** argv) {

    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();

}
