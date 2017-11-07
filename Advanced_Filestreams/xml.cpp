#pragma once
#include "xml.h"


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

	void XML::read() {
		af::read(file, buffer);

	}

	//Entfernt führende Leerzeichen und schreibt in einen neuen String
	void eraseSpaces(std::string& line, std::string& buffer) {
		if (line.find_first_of("<") != std::string::npos) {
			buffer = line.substr(line.find_first_of("<"));
		}
	}
	//Bekommt den Content zwischen den Keys
	auto getContent(std::string& buffer)->std::string {
		int last = buffer.find_last_of("<");
		int first = buffer.find_first_of(">") + 1;
		int count = last - first;
		return buffer.substr(first, count);
	}
	auto getKey(std::string& buffer)->std::string {
		int end = buffer.find_first_of(">")- 1;
		return buffer.substr(1, end);
	}

	void XML::parse() {
		std::string line;
		while (std::getline(file, line)) {
			//Erase spaces
			if(line.find_first_not_of(" ") != std::string::npos)
				line = line.substr(line.find_first_not_of(" "));
			//Definitions in the XML File. The reading of this will be skipped
			if (line.find("<!") == 0)
				continue;
			if (line.find_first_of("<") == 0) {
				int end = buffer.find_first_of(">");
				//TBC
			}
		}
		
	}
}





/*

	//Extrahiert ein Savegame
	auto XMLHandler::savegame(pse::Savegame::Structure& destination)->void {
		int found = 0;
		int currentPosition = 0;
		int inventory = 0;
		Savegame::foundPart part;
		std::string line;
		std::string buffer;

		while (std::getline(opendFile, line)) {
			eraseSpaces(line, buffer);
			//Bei Leerzeile:
			if (buffer == "") {
				continue;
			}

			//am Häufigsten:
			//gefundene Objekte:
			if (found == 3 && buffer.find("<object>") == 0) {
				part.objectsFound.push_back(getContent(buffer));
				continue;
			}
			//gelöste Rätsel
			if (found == 3 && buffer.find("<puzzle>") == 0) {
				part.puzzlesSolved.push_back(getContent(buffer));
				continue;
			}
			//geöffnete Türen/Schränke etc.
			if (found == 3 && buffer.find("<open>") == 0) {
				part.opendStuff.push_back(getContent(buffer));
				continue;
			}
			//Objekte im Inventar:
			if (inventory == 1 && buffer.find("<object>") == 0) {
				destination.inventory.push_back(getContent(buffer));
				continue;
			}

			//found Block der Rest
			if (found == 1 && buffer.find("<part>") == 0) {
				++found;
				continue;
			}
			if (found == 2 && buffer.find("<partNumber>") == 0) {
				part.part = std::stoi(getContent(buffer));
				continue;
			}
			if (found == 2 && buffer.find("<objects>") == 0) {
				++found;
				continue;
			}
			if (found == 3 && buffer.find("</objects>") == 0) {
				--found;
				continue;
			}
			if (found == 2 && buffer.find("<puzzles>") == 0) {
				++found;
				continue;
			}
			if (found == 3 && buffer.find("</puzzles>") == 0) {
				--found;
				continue;
			}
			if (found == 2 && buffer.find("<opend>") == 0) {
				++found;
				continue;
			}

			if (found == 3 && buffer.find("</opend>") == 0) {
				--found;
				continue;
			}
			if (found == 2 && buffer.find("</part>") == 0) {
				--found;
				destination.found.push_back(part);
			}

			//Einmal angefasst:
			if (currentPosition == 1 && buffer.find("<part>") == 0) {
				//Fehler?
				destination.part = std::stoi(getContent(buffer));
				continue;
			}
			if (currentPosition == 1 && buffer.find("<scene>") == 0) {
				destination.scene = std::stoi(getContent(buffer));
				continue;
			}
			if (currentPosition == 1 && buffer.find("</currentPosition>") == 0) {
				--currentPosition;
				continue;
			}

			if (inventory == 1 && buffer.find("</inventory>") == 0) {
				--inventory;
				continue;
			}

			//Langsame Kröten
			if (buffer.find("<found>") == 0) {
				++found;
				continue;
			}
			if (buffer.find("<inventory>") == 0) {
				++inventory;
				continue;
			}
			if (buffer.find("<currentPosition>") == 0) {
				++currentPosition;
				continue;
			}

			//Möglichkeit der Konvertierung prüfen!
			if (buffer.find("<lastTimeSaved>") == 0) {
				//destination.lastSaved = getContent(buffer);
				continue;
			}
			if (buffer.find("<playTime>") == 0) {
				//destination.hoursPlayed = getContent(buffer);
				continue;
			}
		}
	}
	//Extrahiert die Savegameliste
	auto XMLHandler::savegames(std::vector<pse::Savegame::SavegameList>& destination)->void {
		int run = 0; //Eigentlich nicht gebraucht
		Savegame::SavegameList part;
		std::string line;
		std::string buffer;

		while (std::getline(opendFile, line)) {
			++run;
			eraseSpaces(line, buffer);
			//Bei Leerzeile:
			if (buffer == "") {
				continue;
			}
			if (buffer.find("<name>") == 0) {
				part.name = getContent(buffer);
				continue;
			}
			if (buffer.find("<path>") == 0) {
				part.path = getContent(buffer);
				continue;
			}
			if (buffer.find("</save>") == 0) {
				destination.push_back(part);
				continue;
			}

		}
	}
	//Erstellt ein neues Savegame
	void XMLHandler::newSavegame(const std::string& file) {
		this->openFile(file);
		opendFile << "<?xml version=\"1.0\" encoding=\"utf - 8\"?>\n<savegame>\n<stats>\n<lastTimeSaved>";
		std::time_t tt = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		struct std::tm* tm = std::localtime(&tt);
		opendFile << std::put_time(tm, "%D %T") << "</lastTimeSaved>\n<playtime>0</playtime>\n</stats>\n<currentPosition>\n<part>0</part>\n<scene>1</scene>\n</currentPosition>\n";
		opendFile << "<inventory>\n</inventory>\n<found>\n</found>\n</savegame>";

	}

	/*
	Bis zu Ending Tag können die Funktionen nicht funktionieren. Umschreiben erforderlich

	//Fügt einen Key samt Content hinzu
	void XMLHandler::addKey(const std::string& key, const std::string& parent, const std::string& content, bool position) {
		try {
			this->isOpen();
		}
		catch (pse::ReturnCode) {
			throw;
		}
		char* buffptr = 0;
		std::string buffer(buffptr);
		int foundParent = 0;
		int parentEnd = 0;
		long posToSave = 0;
		opendFile.read(buffptr, opendFile.gcount());
		foundParent = buffer.find_first_of(parent);
		parentEnd = buffer.find_first_of("</" + parent + ">");
		if (position) {
			posToSave = buffer.find_first_of("<" + key + ">");
		}
		else {
			posToSave = buffer.find_last_of("</" + key + ">");
			if (posToSave == std::string::npos) {
				posToSave = parentEnd;
			}
		}
		opendFile.seekp(posToSave);
		opendFile << "\n<" + key + ">" << content << "</" + key + ">" << '\n';

	}
	//Editiert den Content eines Keys
	void XMLHandler::editKey(const std::string& key, const std::string& content) {
		try {
			this->isOpen();
		}
		catch (pse::ReturnCode) {
			throw;
		}
		char* buffptr = 0;
		std::string buffer(buffptr);
		int pos = buffer.find_first_of(key);
		if (pos != std::string::npos) {
			opendFile.read(buffptr, opendFile.gcount());
			opendFile.seekp(pos);
			opendFile << "\n<" + key + ">" << content << "</" + key + ">" << '\n';
		}
		else {
			throw(pse::ReturnCode::FailFileStream);
		}

	}
	//Editiert den Content eines Keys
	void XMLHandler::editKey(const std::string& key, const int content) {
		try {
			this->isOpen();
		}
		catch (pse::ReturnCode) {
			throw;
		}
		char* buffptr = 0;
		std::string buffer(buffptr);
		int pos = buffer.find_first_of(key);
		if (pos != std::string::npos) {
			opendFile.read(buffptr, opendFile.gcount());
			opendFile.seekp(pos);
			opendFile << "\n<" + key + ">" << content << "</" + key + ">" << '\n';
		}
		else {
			throw(pse::ReturnCode::FailFileStream);
		}
	}
	//Editiert den Content eines Keys
	void XMLHandler::editKey(const std::string& key, const std::string& content, const std::string& parent) {
		try {
			this->isOpen();
		}
		catch (pse::ReturnCode) {
			throw;
		}
		char* buffptr;
		std::string buffer(buffptr);
		int foundParent = 0;
		int parentEnd = 0;
		long posToSave = 0;
		opendFile.read(buffptr, opendFile.gcount());
		foundParent = buffer.find_first_of(parent);
		parentEnd = buffer.find_first_of("</" + parent + ">");
		int pos = buffer.find_first_of(key);
		if (pos != std::string::npos) {
			if (foundParent < pos && pos < parentEnd) {
				opendFile.read(buffptr, opendFile.gcount());
				opendFile.seekp(pos);
				opendFile << "\n<" + key + ">" << content << "</" + key + ">" << '\n';
			}
			else {
				throw(pse::ReturnCode::FailEngine);
			}
		}
		else {
			throw(pse::ReturnCode::FailFileStream);
		}
	}
	//Entfernt einen Key
	void pse::XMLHandler::removeKey(const std::string& key, const std::string& content) {
		try {
			this->isOpen();
		}
		catch (pse::ReturnCode) {
			throw;
		}
		char* buffptr = 0;
		std::string buffer(buffptr);

		opendFile.read(buffptr, opendFile.gcount());
		buffer.erase(buffer.find("<" + key + ">" + content + "</" + key + ">\n"));
		opendFile.seekp(0);
		opendFile.write(buffptr, buffer.length());
	}
	/*
	END OF NONFUNCTIONAL

	//Gets a list of all Scenes in the gamedirectory
	void XMLHandler::getScenes(std::vector<pse::Leveleditor::part> &dest) {
		try {
			this->isOpen();
		}
		catch (ReturnCode) {
			try {
				openFile(".\\resources\\parts.xml");

			}
			catch (pse::ReturnCode) {
				std::cout << "\nAn Error occured. Please be patient!\n";
			}
		}



		std::string line;
		std::string buffer;
		std::vector<int> pNums;

		while (std::getline(opendFile, line)) {
			eraseSpaces(line, buffer);
			pNums.push_back(std::stoi(getContent(buffer)));
			std::cout << line;
		}
		closeFile();
		for each (int part in pNums)
		{
			try {
				std::string s;
				s = ".\\resources\\part" + std::to_string(part) + "\\part" + std::to_string(part) + ".xml";
				openFile(s);
				std::string tp;
				opendFile;
			}
			catch (pse::ReturnCode) {
				std::cout << "ERROR!\n";
			}
			std::vector<std::string> scenes;
			Leveleditor::part partElem;

			while (std::getline(opendFile, line)) {
				eraseSpaces(line, buffer);
				scenes.push_back(getContent(buffer));
			}
			partElem.partNumber = part;
			partElem.scenes = scenes;
			dest.push_back(partElem);
			closeFile();
		}
	}

	//Loads the List of the Objects
	void XMLHandler::getObjects(std::vector<Object> &dest) {
		std::string line;
		std::string buffer;
		int x = 0;
		int y = 0;
		int inObject{ 0 };
		Object currentObject;
		while (std::getline(opendFile, line)) {
			this->eraseSpaces(line, buffer);
			if (buffer.empty()) {
				continue;
			}
			if (inObject == 1) {
				if (buffer.find("<key>") == 0) {
					currentObject.key = getContent(buffer);
					continue;
				}
				if (buffer.find("<path>") == 0) {
					currentObject.path = getContent(buffer);
					continue;
				}
				if (buffer.find("<point1>") == 0) {
					inObject = 2;
					continue;
				}
				if (buffer.find("<point2>") == 0) {
					inObject = 3;
					continue;
				}
				if (buffer.find("<stdname>") == 0) {
					currentObject.stdname = getContent(buffer);
					continue;
				}
				if (buffer.find("<interactable>") == 0) {
					currentObject.std_is_interactable = getContent(buffer);
					continue;
				}
				if (buffer.find("<lookable>") == 0) {
					currentObject.std_is_lookable = getContent(buffer);
					continue;
				}
				if (buffer.find("<collectable>") == 0) {
					currentObject.std_is_collectable = getContent(buffer);
					continue;
				}
				if (buffer.find("<usable>") == 0) {
					currentObject.std_is_usable = getContent(buffer);
					continue;
				}
				if (buffer.find("</object>") == 0) {
					dest.push_back(currentObject);
					inObject = 0;
					continue;
				}
			}
			if (inObject == 2) {
				if (buffer.find("<x>") == 0) {
					currentObject.point1.x = std::stoi(getContent(buffer));
					continue;
				}
				if (buffer.find("<y>") == 0) {
					currentObject.point1.y = std::stoi(getContent(buffer));
					continue;
				}
				if (buffer.find("</point1>") == 0) {
					inObject = 1;
				}
			}
			if (inObject == 3) {
				if (buffer.find("<x>") == 0) {
					currentObject.point2.x = std::stoi(getContent(buffer));
					continue;
				}
				if (buffer.find("<y>") == 0) {
					currentObject.point2.y = std::stoi(getContent(buffer));
					continue;
				}
				if (buffer.find("</point2>") == 0) {
					inObject = 1;
				}
			}
			if (buffer.find("<object>") == 0) {
				if (inObject) {
					throw(FailEngine);
				}
				inObject = 1;
				continue;
			}
		}
		closeFile();
	}
	//Removes a certain Object from the file
	void XMLHandler::removeObject(const std::string &name) {
		try {
			this->isOpen();
		}
		catch (ReturnCode) {
			try {
				openFile(".\\resources\\objects.xml");

			}
			catch (pse::ReturnCode) {
				std::cout << "\nKonnte die Datei nicht finden\n";
			}
		}
		std::string line;
		std::string buffer;
		std::string fileFirst;
		std::string fileLast;
		std::string buff1;
		std::string buff2;
		int object_pos_start;
		int object_pos_end;
		int found{ 0 };
		while (std::getline(opendFile, line)) {
			eraseSpaces(line, buffer);
			if (found == 0) {
				buff1 = buffer;
				fileFirst += buffer;
				fileFirst += '\n';
				if (buffer.find("<object>") == 0) {

					object_pos_start = opendFile.tellg();
					object_pos_start -= line.length() + 1;
					std::cout << "Objekt gefunden!\n";
					continue;
				}

				if (buffer.find("<key>") == 0) {
					if (name == getContent(buffer)) {
						buff2 = getContent(buffer);
						fileFirst.erase(fileFirst.find("<object>\n<key>" + buff2 + "</key>\n"));
						found = 1;
						continue;
					}
				}
			}

			if (found == 1) {
				if (buffer.find("</object>") == 0) {
					object_pos_end = opendFile.tellg();
					found = 2;
					continue;
				}
			}
			if (found == 2) {
				fileLast += buffer;
				fileLast += '\n';
			}
		}

		closeFile();
		opendFile.open(".\\resources\\objects.xml", std::ios::out);
		fileFirst += fileLast;
		//const int len = fileFirst.length();
		//char* fptr = new char[len];
		//fptr = std::fileFirst;
		opendFile << fileFirst;
		std::cout << fileFirst;
		//opendFile.write(fptr, len);
		//opendFile.sync();
		opendFile.close();
		//delete[] fptr;
		return;
	}
	//Add an Object to the File
	void XMLHandler::addObject(const pse::Object &toAdd) {
		try {
			this->isOpen();
		}
		catch (ReturnCode) {
			try {
				openFile(".\\resources\\objects.xml");

			}
			catch (pse::ReturnCode) {
				std::cout << "\nKonnte die Datei nicht finden\n";
			}
		}
		std::string line;
		std::string buffer;
		while (std::getline(opendFile, line))
		{
			buffer += line;
			buffer += "\n";
		}
		buffer += "<object>\n<key>" + toAdd.key + "</key>\n<path>" + toAdd.path + "</path>\n<point1>\n<x>" + std::to_string(toAdd.point1.x) + "</x>\n<y>"
			+ std::to_string(toAdd.point1.y) + "</y>\n</point1>\n<point2>\n<x>" + std::to_string(toAdd.point2.x) + "</x>\n<y>" + std::to_string(toAdd.point2.y)
			+ "</y>\n</point2>\n<stdname>" + toAdd.stdname + "</stdname>\n<interactable>" + toAdd.std_is_interactable + "</interactable>\n<lookable>"
			+ toAdd.std_is_lookable + "</lookable>\n<collectable>" + toAdd.std_is_collectable + "</collectable>\n<usable>"
			+ toAdd.std_is_usable + "</usable>\n</object>\n";
		closeFile();
		opendFile.open(".\\resources\\objects.xml", std::ios::out);
		opendFile << buffer;
		opendFile.close();
		return;
	}

	void XMLHandler::getObjectsFromCatalog(std::vector<Object> &dest) {
		try {
			this->isOpen();
		}
		catch (ReturnCode) {
			try {
				openFile(".\\resources\\objects.xml");

			}
			catch (pse::ReturnCode) {
				std::cout << "\nAn Error occured. Please be patient!\n";
			}
		}
		this->getObjects(dest);
	}

	void XMLHandler::readScene(Scene& scene) {
		try {
			this->isOpen();
		}
		catch (ReturnCode) {
			try {
				openFile(".\\resources\\" + scene.name + ".xml");

			}
			catch (pse::ReturnCode) {
				std::cout << "\nAn Error occured. Please be patient!\n";
			}
		}
		scene.size = this->getSizeOfScene();
		getObjects(scene.objects);
	}

	void XMLHandler::removeObjectFromScene(const std::string& object) {

	}

	void XMLHandler::addObjectToScene(const Object& object) {

	}

	void XMLHandler::setSizeOfScene(const int x, const int y) {

	}

	auto XMLHandler::getSizeOfScene()->sf::Vector2i {
		std::string line;
		std::string buffer;
		sf::Vector2i size;
		int foundSize = 0;
		while (std::getline(opendFile, line)) {
			this->eraseSpaces(line, buffer);
			if (buffer.empty()) {
				continue;
			}
			if (buffer.find("<size>") == 0) {
				foundSize = 1;
				continue;
			}
			if (foundSize) {
				if (buffer.find("<x>") == 0) {
					size.x = std::stoi(getContent(buffer));
					continue;
				}
				if (buffer.find("<y>") == 0) {
					size.y = std::stoi(getContent(buffer));
					return size;
				}
			}
		}
		throw(pse::ReturnCode::FailFileStream);
	}

	void XMLHandler::createNewScene(const std::string& name, const int x, const int y, const std::vector<Object>) {

	}
};
*/
