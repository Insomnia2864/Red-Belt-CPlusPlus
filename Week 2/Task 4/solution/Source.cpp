#include <iomanip>
#include <iostream>
#include <vector>
#include <utility>
#include <map>

class ReadingManager 
{
public:
    ReadingManager(): 
        vec1(MAX_USER_COUNT_ + 1, -1),
        pages(MAX_PAGE_COUNT_ + 1, 0)
    {}

    void Read(int user_id, int page_count) 
    {
        for (int i = vec1[user_id] + 1; i <= page_count; i++)
        {
            ++pages[i];
        }

        vec1[user_id] = page_count;
    }

    double Cheer(int user_id) const 
    {
        int pages_count = vec1[user_id];

        if (pages_count == -1) 
        {
            return 0;
        }

        int user_count = pages[0];

        if (user_count == 1) 
        {
            return 1;
        }
    
        return static_cast<double>(user_count - pages[pages_count]) / static_cast<double>(user_count - 1);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    std::vector<int> vec1;
    std::vector<int> pages;
};


int main() 
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    ReadingManager manager;

    int query_count;
    std::cin >> query_count;

    for (int query_id = 0; query_id < query_count; ++query_id) 
    {
        std::string query_type;
        std::cin >> query_type;
        int user_id;
        std::cin >> user_id;

        if (query_type == "READ") 
        {
            int page_count;
            std::cin >> page_count;
            manager.Read(user_id, page_count);
        }
        else if (query_type == "CHEER") 
        {
            std::cout << std::setprecision(6) << manager.Cheer(user_id) << "\n";
        }
    }

    return 0;
}