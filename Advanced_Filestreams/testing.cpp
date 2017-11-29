#include "general.h"
#include "xml.h"
#include <iostream>
#pragma comment(linker, "/SUBSYSTEM:console /ENTRY:mainCRTStartup")

//Go one deeper
void output(af::XML::Structure child) {
	std::cout << child.key << " (";
	for each (af::XML::Attribute attribute in child.attributes)
	{
		std::cout << attribute.name + "=" + attribute.content + " ";
	}
	std::cout << "): " << child.content << std::endl;
	for each (af::XML::Structure elem in child.childs)
	{
		output(elem);
	}
}


int main() {
	af::XML xml(".\\test.xml");
	af::XML::Structure file;
	file = xml.read();
	std::cout << file.key << " (";
	for each (af::XML::Attribute attribute in file.attributes)
	{
		std::cout << attribute.name + "=" + attribute.content + " ";
	}
	std::cout << "): " << file.content << std::endl;
	for each (af::XML::Structure elem in file.childs)
	{
		output(elem);
	}
	std::cout << "END ... Press a key to close";
	std::string end;
	std::cin >> end;
}