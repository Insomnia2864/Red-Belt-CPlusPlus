#include "stats.h"

#include <algorithm>
#include <iostream>

Stats::Stats() :
	methods_(
		{
			{"GET", 0},
			{"POST", 0},
			{"PUT", 0},
			{"DELETE", 0},
			{"UNKNOWN", 0},
		}
	),
	uris_(
		{
			{"/", 0},
			{"/order", 0},
			{"/product", 0},
			{"/basket", 0},
			{"/help", 0},
			{"unknown", 0}
		}
	)
{}

void Stats::AddMethod(std::string_view method)
{
	if (methods_.count(method) == 0)
	{
		methods_["UNKNOWN"]++;
	}
	else
	{
		methods_[method]++;
	}
}

void Stats::AddUri(std::string_view uri)
{
	if (uris_.count(uri) == 0)
	{
		uris_["unknown"]++;
	}
	else
	{
		uris_[uri]++;
	}
}

const std::map<std::string_view, int>& Stats::GetMethodStats() const
{
	return methods_;
}

const std::map<std::string_view, int>& Stats::GetUriStats() const
{
	return uris_;
}

HttpRequest ParseRequest(std::string_view line)
{
	HttpRequest res;

	line.remove_prefix(std::min(line.find_first_not_of(' '), line.size()));

	std::size_t pos = line.find(' ');
	res.method = line.substr(0, pos);

	line.remove_prefix(++pos);

	pos = line.find(' ');
	res.uri = line.substr(0, pos);

	line.remove_prefix(++pos);

	res.protocol = line.substr(0);
	
	return res;
}