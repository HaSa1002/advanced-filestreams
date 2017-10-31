#pragma once
#ifndef ADVANCED_FILESTREAMS
#define ADVANCED_FILESTREAMS
#include <fstream>
#include <string>

namespace af {
	enum Exception {
		CouldntOpenFile,

	};

	///<summary>The basic class in this framework. All operations are done on top of this class</summary>
	class Filestream {
	public:
		///<summary>Suprisingly it does nothing</summary>
		Filestream();

		///<summary>Opens a file</summary>
		///<exception cref="Exception::CouldntOpenFile">File couldn't be opend</exception>
		///<param name="path">Path to file</param>
		Filestream(const std::string& path);

		///<summary>Checks wether a file is open or not</summary>
		///<returns>0: not open | 1: open</returns>
		bool is_open();
		///<summary>Opens a file</summary>
		///<param name="path">Path to the file</param>
		bool open(const std::string& path);
		///<summary>Closes the file</summary>
		void close();
		///<summary>Writes into the file</summary>
		///<remarks>You will allways overwrite the content. If you don't want that, you need to use append()</remarks>
		///<param name="to_write">String to write into</param>
		void write(const std::string& to_write);

		///<summary>Reads the text into the given String</summary>
		///<param name="destination">Pushes content into<
		void read(std::string& destination);
		void find(const std::string& to_find);
		void getLine(std::string& destination);
		void append(const std::string& to_append);
		void setExceptionMode(bool mode);
		
	private:
		bool exception_mode = 0;
		std::string file_buffer;
		std::fstream file;
		long int file_position;
	};
}


#endif // !ADVANCED_FILESTREAMS
