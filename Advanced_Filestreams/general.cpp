#pragma once
#include "general.h"

namespace af {
	Filestream::Filestream() {

	}
	
	Filestream::Filestream(const std::string & path)
	{
		if (!this->open(path)) {
			throw(Exception::CouldntOpenFile);
		}
	}
	
	bool Filestream::is_open()
	{
		return false;
	}
	bool Filestream::open(const std::string & path)
	{
		return false;
	}
	void Filestream::close()
	{
	}
	void Filestream::write(const std::string & to_write)
	{
	}
	void Filestream::read(std::string & destination)
	{
	}
	void Filestream::find(const std::string & to_find)
	{
	}
	void Filestream::getLine(std::string & destination)
	{
	}
	void Filestream::append(const std::string & to_append)
	{
	}
}