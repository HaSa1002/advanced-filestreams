#pragma once
#ifndef ADVANCED_FILESTREAMS
#define ADVANCED_FILESTREAMS
#include <fstream>
#include <string>

namespace af {
	enum Exception {
		CouldntOpenFile,			/// The given file couldn't be opend
		WrongXmlFormat,				/// A non xml format is used
		FoundUnexpectedEndOfFile,	/// the end of file was reached before the first tag was closed
		FoundUnexpectedEndingTag,	/// an unexpected ending tag was found
		EmptyLine					/// the line is empty
	};
		/// <summary>Writes into the file</summary>
		/// <remarks>You allways overwrite the content. If you don't want that, you need to use append()</remarks>
		/// <param name="to_write">what to write into</param>
		/// <param name="file">where to write</param>
		extern void write(std::fstream& file, const std::string& to_write);

		/// <summary>Reads the text into the given String</summary>
		/// <param name="destination">Where to read from</param>
		/// <param name="file">From where</param>
		extern void read(const std::string& file, std::string& destination);

		/// <summary>Appends content to the file</summary>
		/// <param name="to_append">what to append</param>
		/// <param name="file">Where to append</param>
		extern void append(std::fstream& file, const std::string& to_append);

		/// <summary>gets a line from a string</summary>
		/// <param name="source">where to read from</param>
		/// <param name="dest">where to write into</param>
		/// <param name="delim">delimeting character. Default: "\n"</param>
		extern bool getline(std::string& source, std::string& dest, bool skip_if_not_empty = true, const std::string& delim = "\n");
}


#endif // !ADVANCED_FILESTREAMS
