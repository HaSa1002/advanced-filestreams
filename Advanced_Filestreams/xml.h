#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
#include <vector>

namespace af {
	///<summary>Handles XML-Files</summary>
	class XML {
	public:
		///<summary>stores the atributename and the related content</summary>
		struct Attribute {
			std::string name;
			std::string content;
		};

		///<summary>Represents a XML File</summary>
		struct Structure
		{
			std::string key;
			std::vector<af::XML::Attribute> attributes;
			std::string content;
			std::vector<af::XML::Structure> childs;
		};

		XML(std::string filepath);
		XML();
		~XML();

		void open(std::string path);
		void create(std::string path);
		void close();
		auto read()->Structure;
		void write(Structure file, bool self = 0);
		auto getFileStruct() -> Structure;
		auto getFile()->std::fstream;

	private:
		void manage_stream(int action);
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



#endif // !AF_XML

