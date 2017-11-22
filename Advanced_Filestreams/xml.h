#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
#include <vector>

namespace af {

	class XML {
	public:
		struct Attribute {
			std::string name;
			std::string content;
		};

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

		void parse();
		void open(std::string path);
		void close();
		void read();
		void getContent(const std::string& key);
		auto getFileStruct() -> Structure;
		auto getFile()->std::fstream;

	private:
		std::fstream file;
		af::XML::Structure parsedFile;
		std::string buffer;
		int useMode = 0;
		int depth = 0;
	};
}



#endif // !AF_XML

