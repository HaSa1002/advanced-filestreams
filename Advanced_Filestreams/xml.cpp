#include "xml.h"
#include "general.h"


namespace af {

	void XML::open(const std::string& path) {
		file.open(path, std::ios::in | std::ios::out);
		if (!file.is_open())
			throw(af::Exception::CouldntOpenFile);
		lastAction = Action::r;
		filename = path;
	}


	////////////////////////////////////////////////////////////
	void XML::create(const std::string& path) {
		file.open(path, std::fstream::out);
		file << std::flush;
		file.close();
		file.clear();
		open(path);
		lastAction = Action::w;
	}


	////////////////////////////////////////////////////////////
	void XML::close() {
		if (file.is_open())
			file.close();
	}


	////////////////////////////////////////////////////////////
	XML::XML(const std::string& path) {
		std::locale::global(std::locale(""));
		try {
			open(path);
		}
		catch (af::Exception) {
			throw;
		}
	}


	////////////////////////////////////////////////////////////
	XML::XML() {
		std::locale::global(std::locale(""));
	}


	////////////////////////////////////////////////////////////
	XML::~XML() {
		close();
	}


	////////////////////////////////////////////////////////////
	void XML::eraseSpaces(std::string& source, std::string& destination) {
		if (!source.empty()) {
			std::size_t offset = 0;
			if (source.find_first_not_of('\t') != std::string::npos)
				offset = source.find_first_not_of("\t");
			if (source.find_first_not_of(" ") != std::string::npos)
				offset += source.find_first_not_of(" ");

			destination = source.erase(0, offset);
			return;
		}
		throw(Exception::EmptyLine);
	}


	////////////////////////////////////////////////////////////
	void XML::write(Structure file, bool self, unsigned int run) {
		if(!self) {
			buffer.clear();
			manage_stream(Action::w);
		}
		std::string spacing = "";
		for (int i = run; i > 0; --i) {
			spacing += "\t";
		}
		buffer += spacing + "<" + file.key;
		for each (af::XML::Attribute attribute in file.attributes) {
			buffer += " " + attribute.name + "=\"" + attribute.content + "\"";
		}
		buffer += ">";
		bool skipChilds = file.childs.empty();
		if (!file.content.empty()) {
			if (skipChilds)
				buffer += file.content;
			else
				buffer += "\n" + spacing + "\t" + file.content + "\n";
		}
		else {
			if (!skipChilds)
				buffer += "\n";
		}
		if (!skipChilds) {
			for each (af::XML::Structure elem in file.childs) {
				write(elem, 1, run + 1);
			}
			buffer += spacing;
		}
		buffer += "</" + file.key + ">\n";
		if(!self) {
			af::write(this->file, buffer);
			this->file << std::flush;
		}
	} //write


	  ////////////////////////////////////////////////////////////
	void XML::skipIf() {
		if (buffer.find("<!") == 0)
			throw(Exception::EmptyLine);
		if (buffer.find("<?") == 0)
			throw(Exception::EmptyLine);
	}


	////////////////////////////////////////////////////////////
	bool XML::checkForEndingTag() {
		unsigned int close = buffer.find("</");
		if (close == 0) {
			close = buffer.find('>');
			if (close != std::string::npos) {
				if (tagList.at(tagList.size() - 1) == buffer.substr(2, close - 2)) {
					tagList.pop_back();
					buffer.erase(0, close + 1);
					return true;
				}
				else
					throw(af::Exception::FoundUnexpectedEndingTag);
			}
			
		}
		return false;
	}


	////////////////////////////////////////////////////////////
	bool XML::getKey(Structure& destination) {
		unsigned int end = buffer.find_first_of(" ");
		if (end == std::string::npos || end > buffer.find_first_of(">")) {
			//If attributes NOT included
			end = buffer.find_first_of('>') - 1;
			destination.key = buffer.substr(1, end);
			tagList.push_back(destination.key);
			buffer = buffer.erase(0, end + 2);
			return true;
		}
		else {
			//If attributes included
			destination.key = buffer.substr(1, end - 1);
			tagList.push_back(destination.key);
			buffer = buffer.erase(0, end + 1);
			return false;
		}
	}


	////////////////////////////////////////////////////////////
	void XML::getAttribute(Structure& destination) {
		Attribute attribute;
		attribute.name = buffer.substr(0, buffer.find_first_of("="));
		int start = buffer.find_first_of("=") + 2;
		int ending = buffer.find_first_of("\"", buffer.find_first_of("=") + 2) - start;
		attribute.content = buffer.substr(start, ending);
		destination.attributes.push_back(attribute);
		buffer = buffer.erase(0, start + ending + 2);
	}


	////////////////////////////////////////////////////////////
	bool XML::checkForAttributes() {
		unsigned int end = buffer.find_first_of("\"");
		if (end == std::string::npos || buffer.find_first_of('>') < end) {
			//No attributes left
			//Checking if there is anything behind the closing delimiter
			int size = buffer.size() - 1;
			int temp = buffer.find_first_of('>');
			if (temp != size)
				//Something is behind
				buffer = buffer.erase(0, temp + 1);

			return true;
		}
		else {
			//Attributes left
			//buffer = buffer.substr(end + 1);
			return false;
		}
	}


	////////////////////////////////////////////////////////////
	auto XML::read(bool self)->Structure {
		// Vars
		manage_stream(Action::r);
		bool opendTag = false;
		Structure current;
		
		//Check if file has to be read
		if (!self)
			af::read(filename, data);

		//skip reading if buffer is not clear
		while (af::getline(data, buffer)) {
			//erases Spaces
			try {
				eraseSpaces(buffer, buffer);
				skipIf();
			}
			catch (af::Exception) {
				//empty line, read new line
				buffer.clear();
				continue;
			}
			//Checks for Endingtag
			if (checkForEndingTag())
				return current;

			
			if (buffer.find_first_of('<') == 0) {
				//openeningTag found
				if (opendTag) {
					//method already run -> prepare recursive call
					try {
						current.childs.push_back(this->read(true));
					}
					catch (af::Exception) {
						throw;
					}
				}
				else {
					//first run
					opendTag = true;
					bool closingDelim = getKey(current);
					//Reading of Attributes
					unsigned int end = buffer.find_first_of('>');
					if (end != std::string::npos && !closingDelim) {
						//attributes found
						while (!closingDelim) {
							getAttribute(current);
							closingDelim = checkForAttributes();
						} //WHILE !closingTag
					} //IF attributes
				} //ELSE opendTag
			} //IF <

			if (!buffer.empty()) {
				//buffer is not empty -> vi stuff left ...it works!
				unsigned int close = buffer.find("</");
				if (close != 0) {
					while(buffer.find_first_of('<') == 0) {
						//method already run -> prepare recursive call
						try {
							current.childs.push_back(this->read(true));
							if (checkForEndingTag())
								return current;
						}
						catch (af::Exception) {
							throw;
						}
					}
					unsigned int close = buffer.find("</");
					//content left -> get content
					current.content = buffer.substr(0, close);
					buffer.erase(0, close);
				}
				if (checkForEndingTag())
					return current;
			} //IF empty
		} //while
		if (tagList.empty())
			return current;
		//Should never reached, because method normally ends earlier
		throw(af::Exception::FoundUnexpectedEndOfFile);
	} //read


	////////////////////////////////////////////////////////////
	void XML::manage_stream(Action action) {
		if (action != this->lastAction) {
			switch (action) {
			case Action::r:
				this->close();
				this->open(filename);
				break;
			case Action::w:
				this->close();
				this->create(filename);
				break;
			default:
				break;
			} //switch
			lastAction = action;
		} //if
	} //manage_stream


	////////////////////////////////////////////////////////////
	auto XML::getFile() -> std::fstream&	{
		return file;
	}


	////////////////////////////////////////////////////////////
	auto af::XML::getFileStruct() -> Structure {
		return parsedFile;
	}
} //AF
