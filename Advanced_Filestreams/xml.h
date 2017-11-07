#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
#include <vector>

namespace af {
	class XML {
		struct Atribute {
			std::string name;
			std::string content;
		};

		struct Structure
		{
			std::string key;
			std::vector<af::XML::Atribute> atributes;
			std::string content;
			std::vector<af::XML::Structure> childs;
		};


		void parse();
		void parseStructure();
		void parseXML();
		void read();
		void getKeys();
		void getContent(const std::string& key);
		void editContent();


	};
}



#endif // !AF_XML

