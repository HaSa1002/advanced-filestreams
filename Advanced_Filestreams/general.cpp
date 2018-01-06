#pragma once
#include "general.h"

namespace af {
	void write(std::fstream& file, const std::string & to_write) {
		file << to_write;
	}
	void read(std::fstream& file, std::string& destination) {
		file >> destination;
	}
	void append(std::fstream& file, const std::string& to_append) {
		std::string buffer;
		read(file, buffer);
		buffer += to_append;
		write(file, buffer);
	}



}