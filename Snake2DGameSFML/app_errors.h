#pragma once
#include <exception>

class NotImplementedException : public std::exception
{
public:
	char const* what() const override
	{
		return "Not implemented exception";
	}
};
