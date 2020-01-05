#include "test_runner.h"
#include <deque>
#include <iostream>
#include <map>
#include <string_view>
#include <vector>


class Translator 
{
public:
    void Add(std::string_view source, std::string_view target)
    {
        const std::string_view source_ = GetStringView(source);
        const std::string_view target_ = GetStringView(target);

        forward_base_[source_] = target_;
        backward_base_[target_] = source_;
    }

    std::string_view TranslateForward(std::string_view source) const 
    {
        auto it = forward_base_.find(source);
        if (it == forward_base_.end())
        {
            return "";
        }

        return it->second;
    }

    std::string_view TranslateBackward(std::string_view target) const 
    {
        auto it = backward_base_.find(target);
        if (it == backward_base_.end())
        {
            return "";
        }

        return it->second;
    }

private:
    std::map<std::string_view, std::string_view> forward_base_;
    std::map<std::string_view, std::string_view> backward_base_;
    std::deque<std::string> base_;

    std::string_view GetStringView(std::string_view s)
    {
        auto iter = forward_base_.find(s);
        if (iter != forward_base_.end())
        {
            return iter->first;
        }

        auto iter2 = backward_base_.find(s);
        if (iter2 != backward_base_.end())
        {
            return iter2->first;
        }

        base_.emplace_back(s);

        return std::string_view(base_.back());
    }
};