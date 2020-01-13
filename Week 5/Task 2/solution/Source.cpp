#include "test_runner.h"

#include <algorithm>
#include <string>
#include <vector>
#include <map>
#include <set>
#include <utility>


template <typename String>
using Group = std::vector<String>;

template <typename String>
using Char = typename String::value_type;

template <typename String>
std::vector<Group<String>> GroupHeavyStrings(std::vector<String> strings) 
{
    std::map<std::set<typename String::value_type>, Group<String>> groups_map;

    for (String& str : strings) 
    {
        groups_map[std::set<typename String::value_type>(str.begin(), str.end())].push_back(std::move(str));
    }

    std::vector<Group<String>> groups;

    for (auto& [key, group] : groups_map) 
    {
        groups.push_back(move(group));
    }
    return groups;
}


void TestGroupingABC()
{
    std::vector<std::string> strings = { "caab", "abc", "cccc", "bacc", "c" };

    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 2);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({ "caab", "abc", "bacc" }));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({ "cccc", "c" }));
}

void TestGroupingReal() 
{
    std::vector<std::string> strings = { "law", "port", "top", "laptop", "pot", "paloalto", "wall", "awl" };
    auto groups = GroupHeavyStrings(strings);
    ASSERT_EQUAL(groups.size(), 4);
    sort(begin(groups), end(groups));  // Порядок групп не имеет значения
    ASSERT_EQUAL(groups[0], std::vector<std::string>({ "laptop", "paloalto" }));
    ASSERT_EQUAL(groups[1], std::vector<std::string>({ "law", "wall", "awl" }));
    ASSERT_EQUAL(groups[2], std::vector<std::string>({ "port" }));
    ASSERT_EQUAL(groups[3], std::vector<std::string>({ "top", "pot" }));
}

int main()
{
    TestRunner tr;
    RUN_TEST(tr, TestGroupingABC);
    RUN_TEST(tr, TestGroupingReal);
    return 0;
}