#pragma once
#include "general.hpp"
#include <vector>
#include <list>

namespace af {
	typedef std::list<std::list<std::string>> table;

	int printCsv(const std::string& file_path, const table& table);
}