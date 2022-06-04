#pragma once
#include <iostream>

class a {

public:
	a(const std::string& val);
	a(const a& rhs);
	a(a&& rhs);
	~a();

	char* get() const;

private:
	char* pole;
};