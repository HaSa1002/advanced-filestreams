#pragma once
#include "general.h"

namespace af {
	extern void write(std::fstream& file, const std::string & to_write)
	{
		file << to_write;
	}
	extern void read(std::fstream& file, std::string& destination)
	{
		file >> destination;
	}
	extern void append(std::fstream& file, const std::string& to_append)
	{
		std::string buffer;
		read(file, buffer);
		buffer += to_append;
		write(file, buffer);
	}
}