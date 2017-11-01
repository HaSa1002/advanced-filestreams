#pragma once
#ifndef AF_XML
#define AF_XML
#include "general.h"
namespace af {
	class XML : TextFilestream {
		
		void parse();
		void read();

	};
}



#endif // !AF_XML

