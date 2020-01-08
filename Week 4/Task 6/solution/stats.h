#pragma once

#include "http_request.h"

#include <string_view>
#include <map>

class Stats 
{
public:
    Stats();
    void AddMethod(std::string_view method);
    void AddUri(std::string_view uri);
    const std::map<std::string_view, int>& GetMethodStats() const;
    const std::map<std::string_view, int>& GetUriStats() const;
private:
    std::map<std::string_view, int> methods_;
    std::map<std::string_view, int> uris_;
};

HttpRequest ParseRequest(std::string_view line);