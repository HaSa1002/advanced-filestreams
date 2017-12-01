#pragma once
#include "xml.h"
#include "general.h"


namespace af {



	void XML::open(std::string path) {
		file.open(path, std::ios::in | std::ios::out);
		if (!file.is_open())
			throw(af::Exception::CouldntOpenFile);
	}

	void XML::close() {
		if (file.is_open())
			file.close();
	}

	XML::XML(std::string path) {
		try {
			open(path);
		}
		catch (af::Exception) {
			throw;
		}
	}
	XML::XML() {
	}

	XML::~XML() {
		close();
	}

	//Entfernt führende Leerzeichen und schreibt in einen neuen String
	bool eraseSpaces(std::string& line, std::string& buffer) {
		if (!line.empty()) {
			if (line.find_first_not_of('\t') != std::string::npos) {
				buffer = line.substr(line.find_first_not_of("\t"));
			}
			if (line.find_first_not_of(" ") != std::string::npos) {
				buffer = line.substr(line.find_first_not_of(" "));
			}
			return 0;
		}
		throw(EmptyLine);
	}
	
	void XML::write(Structure file, bool self) {
		if(!self) {
		buffer.clear();
		}
		buffer += "<" + file.key;
		for each (af::XML::Attribute attribute in file.attributes)
		{
			buffer += " " + attribute.name + "=\"" + attribute.content + "\"";
		}
		buffer += ">" + file.content + "\n";
		for each (af::XML::Structure elem in file.childs)
		{
			this->write(elem, 1);
		}
		buffer += "</" + file.key + ">\n";
		if(!self) {
			af::write(this->file, buffer);
		}
	} //write
	
	auto XML::read()->Structure {
		bool opendTag = false;
		Structure current;
		std::streampos streampos = 0;
		while (std::getline(file, buffer)) {
			//Check if buffer is empty, has XML Definitions
			try {
				eraseSpaces(buffer, buffer);
			}
			catch (af::Exception) {
				continue;
			}
			if (buffer.find("<!") == 0)
				continue;
			if (buffer.find("<?") == 0)
				continue;
			//Checks for Endingtag
			unsigned int close = buffer.find("</");
			if ( close == 0) {
				close = buffer.find('>');
				if (close != std::string::npos) {
					if (tagList.at(tagList.size() - 1) == buffer.substr(2, close - 2)) {
						tagList.pop_back();
						buffer.clear();
						return current;
					}
					else
						throw(af::Exception::FoundUnexpectedEndingTag);
				}
			}
			if (buffer.find_first_of('<') == 0) {
				if (opendTag) {
					file.seekg(streampos);
					current.childs.push_back(this->read());
				}
				else {
					opendTag = true;
					//Schlussklammer gefunden
					bool closingDelim = false;
					{ //gets the Key
						unsigned int end = buffer.find_first_of(" ");
						if (end == std::string::npos || end > buffer.find_first_of(">")) {
							end = buffer.find_first_of(">") - 1;
							current.key = buffer.substr(1, end);
							tagList.push_back(current.key);
							buffer = buffer.substr(end + 2);
							closingDelim = true;
						}
						else {
							current.key = buffer.substr(1, end - 1);
							tagList.push_back(current.key);
							buffer = buffer.substr(end + 1);
						}
						
					}
					
					
					//Reading of Attributes
					unsigned int end = buffer.find_first_of('>');
					if (end != std::string::npos || !closingDelim) {
						while (!closingDelim) {
							Attribute attribute;
							//Getting Attributes
							attribute.name = buffer.substr(0, buffer.find_first_of("="));
							int start = buffer.find_first_of("=") + 2;
							int ending = buffer.find_first_of("\"", buffer.find_first_of("=") + 2) - start;
							attribute.content = buffer.substr(start, ending);
							current.attributes.push_back(attribute);
							//Checking if there are any attributes left
							unsigned int end = buffer.find_first_of(" ");
							if (end == std::string::npos || buffer.find_first_of('>') < end) {
								//No attributes left
								//Checking if there is anything behind the closing delimiter
								int size = buffer.size() - 1;
								int temp = buffer.find_first_of('>');
								if (temp != size)
									//Something is behind
									buffer = buffer.substr(temp + 1);
								else
									//Nothing is behind
									buffer.clear();
								//End the while
								closingDelim = 1;
							}
							else
								//Attributes left
								buffer = buffer.substr(end + 1);
						} //WHILE !closingTag
					} //IF attributes
					  //Checking if there is anything behind the closing delimiter
					/*int size = buffer.size() - 1;
					int temp = buffer.find_first_of('>');
					if (temp != size)
						//Something is behind
						buffer = buffer.substr(temp);
					else
						//Nothing is behind
						buffer.clear();*/
				} //ELSE opendTag
			} //IF <
			if (!buffer.empty()) {
				unsigned int close = buffer.find("</");
				if (close != 0) {
					//Content bekommen
					current.content = buffer.substr(0, close);
					if (close == std::string::npos)
						buffer.clear();
					else
						buffer = buffer.substr(close);
					close = buffer.find("</");
				}
				
				if (close == 0) {
					close = buffer.find('>');
					if (close != std::string::npos) {
						if (tagList.at(tagList.size() - 1) == buffer.substr(2, close - 2)) {
							tagList.pop_back();
							buffer.clear();
							return current;
						}
						else
							throw(af::Exception::FoundUnexpectedEndingTag);
					} // IF close
				} //IF close
			} //IF empty
			streampos = file.tellg();
		} //while
		throw(af::Exception::FoundUnexpectedEndOfFile);
	} //read



} //AF
