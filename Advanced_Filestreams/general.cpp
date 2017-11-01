#pragma once
#include "general.h"

namespace af {
	TextFilestream::TextFilestream() {

	}
	
	TextFilestream::TextFilestream(const std::string & path)
	{
		try {
			if (!this->open(path)) {
				throw(Exception::CouldntOpenFile);
			}
		}
		catch (Exception) {
			throw;
		}
	}
	
	bool TextFilestream::is_open()
	{
		if (!file.is_open()) {
			if (exception_mode) {
				throw(Exception::CouldntOpenFile);
				return false;
			}
			else
				return false;
		} //is_open()
		return true;
	}

	bool TextFilestream::open(const std::string & path)
	{
		file.open(path, std::ios::in | std::ios::out);
		if (exception_mode) {
			try {
				!this->is_open();
				return true;
			}
			catch (Exception) {
				throw;
				return false;
			}
		}
		else
			return this->is_open();
	}

	void TextFilestream::close()
	{
		bool mode = exception_mode;
		exception_mode = 0;
		if (this->is_open())
			file.close();
		exception_mode = mode;
	}
	void TextFilestream::write(const std::string & to_write)
	{
		file << to_write;
	}
	void TextFilestream::read(std::string & destination)
	{
		file >> destination;
	}
	void TextFilestream::getLine(std::string & destination)
	{
		std::getline(file, destination);
	}
	void TextFilestream::append(const std::string & to_append)
	{
		std::string buffer;
		this->read(buffer);
		buffer += to_append;
		this->write(buffer);
	}
	void TextFilestream::setExceptionMode(bool mode)
	{
		exception_mode = mode;
	}
}