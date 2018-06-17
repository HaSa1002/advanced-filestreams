#include "csv.hpp"

namespace af {
	int printCsv(const std::string& file_path, const table& table) {
		std::string buffer;
		// Create File
		std::fstream file;
		file.open(file_path, std::fstream::out);
		file << std::flush;

		for (auto& row : table) {
			for (auto& col : row) {
				buffer += col + ',';
			}
			buffer += '\n';
		}
		af::write(file, buffer);
		file.close();
	}
}