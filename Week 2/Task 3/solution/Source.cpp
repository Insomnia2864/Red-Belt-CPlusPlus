#include <algorithm>
#include <cmath>
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <set>


class RouteManager 
{
public:
    void AddRoute(int start, int finish) 
    {
        reachable_lists_[start].insert(finish);
        reachable_lists_[finish].insert(start);
    }
    int FindNearestFinish(int start, int finish) const
    {
        int def = std::abs(finish - start);

        if (reachable_lists_.count(start) == 0)
        {
            return def;
        }

        const auto& st = reachable_lists_.at(start);
        auto iter = st.lower_bound(finish);

        if (iter == st.end())
        {
            iter = std::prev(iter);
        }
        else if (iter != st.begin())
        {
            iter = std::abs(*std::prev(iter) - finish) > std::abs(*iter - finish) ? iter : std::prev(iter);
        }

        return def > std::abs((*iter) - finish) ? std::abs((*iter) - finish) : def;
    }
private:
    std::map<int, std::set<int>> reachable_lists_;
};


int main() {
    RouteManager routes;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id)
    {
        std::string query_type;
        std::cin >> query_type;
        int start, finish;
        std::cin >> start >> finish;
        if (query_type == "ADD") {
            routes.AddRoute(start, finish);
        }
        else if (query_type == "GO") {
            std::cout << routes.FindNearestFinish(start, finish) << "\n";
        }
    }

    return 0;
}