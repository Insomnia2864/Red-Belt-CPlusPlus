#include <algorithm>
#include <string>
#include <set>
#include <vector>

class Learner 
{
private:
    std::set<std::string> dict;

public:
    int Learn(const std::vector<std::string>& words) 
    {
        int newWords = 0;
        for (const auto& word : words)
        {
            if (dict.count(word) == 0)
            {
                dict.insert(word);
                newWords++;
            }
        }
        return newWords;
    }

    std::vector<std::string> KnownWords()
    {
        std::vector<std::string> res(dict.begin(), dict.end());
        return res;
    }
};