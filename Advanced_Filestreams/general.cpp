#include "general.h"

#include <vector>
#include <array>

namespace af {
	
	extern void write(std::fstream& file, const std::string & to_write) {
		file << to_write;
	}


	////////////////////////////////////////////////////////////
	extern void read(const std::string& file, std::string& destination) {
		std::ifstream in(file, std::ios::in | std::ios::binary);
		if (in) {
			//write into std::string
			in.seekg(0, std::ios::end);
			destination.resize(static_cast<const unsigned int>(in.tellg()));
			in.seekg(0, std::ios::beg);
			in.read(&destination[0], destination.size());
			in.close();
			//unify line ending to unix style (\n)
			for (std::size_t pos = destination.find_first_of("\r\n"); pos < destination.size(); pos = destination.find_first_of("\r\n", ++pos)) {
				if (destination.at(pos) == '\r') {
					if (destination.at(pos + 1) == '\n')
						destination.replace(pos, 2, "\n");
					else
						destination.at(pos) = '\n';
				}
			}
			return;
		}
		throw(errno);
	}


	////////////////////////////////////////////////////////////
	extern void append(std::fstream& file, const std::string& to_append) {
		std::string buffer;
		//read(file, buffer);
		buffer += to_append;
		write(file, buffer);
	}


	////////////////////////////////////////////////////////////
	extern bool getline(std::string & source, std::string & dest, bool skip_if_not_empty, const std::string & delim) {
		if (skip_if_not_empty && !dest.empty())
			return true;

		unsigned int end_pos = source.find_first_of(delim);
		if (end_pos == std::string::npos && source.empty())
			return false;

		dest = source.substr(0, end_pos);
		++end_pos;
		source.erase(0, end_pos);
		return true;
	}
}