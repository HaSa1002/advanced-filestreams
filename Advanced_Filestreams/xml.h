#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
#include <vector>

namespace af {
	///<summary>Handles XML-Files</summary>
	class XML {
	public:
		///<summary>Stores the atributename and the related content</summary>
		struct Attribute {
			std::string name;
			std::string content;
			bool operator==(const Attribute &right);
			bool operator!=(const Attribute &right);
		};

		///<summary>Represents a XML File</summary>
		struct Structure
		{
			std::string key;
			std::vector<af::XML::Attribute> attributes;
			std::string content;
			std::vector<af::XML::Structure> childs;
			bool operator==(const Structure &right);
		};
		///<summary>Opens a file</summary>
		///<remarks>If you need to create the file first use the default constructor instead and call XML::create</remarks>
		XML(std::string filepath);
		XML();
		~XML();

		///<summary>Opens a file</summary>
		void open(std::string path);
		///<summary>Creates a file</summary>
		void create(std::string path);
		///<summary>Close a file</summary>
		void close();
		///<summary>Reads a file</summary>
		///<returns>A Structure which is the file</returns>
		auto read(bool self = false)->Structure;
		
		///<summary>Writes into a file</summary>
		///<param name="file">The Structure Struct which represents a file</param>
		void write(Structure file, bool self = false, unsigned int run = 0);
		///<returns>The loaded Filestruct</returns>
		auto getFileStruct() -> Structure;
		///<returns>The Filestream object</returns>
		auto getFile()->std::fstream&;

	private:
		void manage_stream(int action);
		void eraseSpaces(std::string & line, std::string & buffer, std::streampos & pos);
		
		void skipIf();
		bool checkForEndingTag(Structure & current, std::streampos & pos);
		bool getKey(Structure & dest, std::streampos & pos);
		void getAttribute(Structure & dest, std::streampos & pos);
		bool checkForAttributes(std::streampos & pos);
		std::fstream file;
		std::string filename;
		af::XML::Structure parsedFile;
		std::vector<std::string> tagList;
		std::string buffer;
		int lastAction = 0;
		enum Action {
			r,
			w
		};
		
	};
}

#include "Struct.inl"

#endif // !AF_XML

