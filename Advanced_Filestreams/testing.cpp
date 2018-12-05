#define DEBUG
#ifndef DEBUG
#include "general.hpp"
#include "xml.hpp"
#include <iostream>
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")

int main() {
	std::string end;
	std::cout << "Filepath to read: ";
	std::cin >> end;
	af::XML xml(end);
	af::XML::Structure file;
	file = xml.read();
	std::cout << "\nFilepath to write: ";
	std::cin >> end;
	xml.close();
	xml.create(end);
	xml.write(file);
	xml.close();
	std::cout << "END ... Press a key to close";
	std::cin >> end;
}
#endif // !DEBUG