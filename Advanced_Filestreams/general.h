#pragma once
#ifndef ADVANCED_FILESTREAMS
#define ADVANCED_FILESTREAMS
#include <fstream>
#include <string>

namespace af {
	enum Exception {
		CouldntOpenFile,
		WrongXmlFormat,
		FoundUnexpectedEndOfFile,
		FoundUnexpectedEndingTag,
		EmptyLine
	};
		///<summary>Writes into the file</summary>
		///<remarks>You allways overwrite the content. If you don't want that, you need to use append()</remarks>
		///<param name="to_write">what to write into</param>
		///<param name="file">where to write</param>
		extern void write(std::fstream& file, const std::string& to_write);

		///<summary>Reads the text into the given String</summary>
		///<param name="destination">Where to write into</param>
		///<param name="file">From where</param>
		extern void read(std::fstream& file, std::string& destination);

		///<summary>Appends content to the file</summary>
		///<param name="to_append">what to append</param>
		///<param name="file">Where to append</param>
		extern void append(std::fstream& file, const std::string& to_append);
}


#endif // !ADVANCED_FILESTREAMS
