#include "stdafx.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest
{		
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(writeTest)
		{
			af::XML xml;
			af::XML::Structure fileStruct;
			af::XML::Attribute attributes;
			attributes.name = "class";
			attributes.content = "new World";
			fileStruct.key = "test";
			fileStruct.content = "hello";
			fileStruct.attributes.push_back(attributes);
			af::XML::Structure f2;
			f2.key = "test";
			f2.content = "hello";
			f2.attributes.push_back(attributes);
			fileStruct.childs.push_back(f2);
			xml.create("u_test");
			xml.write(fileStruct);
			xml.close();
		}

		TEST_METHOD(readTest)
		{
			af::XML xml;
			af::XML::Structure fileStruct;
			af::XML::Attribute attributes;
			attributes.name = "class";
			attributes.content = "new World";
			fileStruct.key = "test";
			fileStruct.content = "hello";
			fileStruct.attributes.push_back(attributes);
			af::XML::Structure f2;
			f2.key = "test";
			f2.content = "hello";
			f2.attributes.push_back(attributes);
			fileStruct.childs.push_back(f2);
			xml.open("u_test");
			af::XML::Structure s = xml.read();
			bool same = (fileStruct == s);
			xml.close();
			Assert::IsTrue(same);
		}

		TEST_METHOD(ioTest)
		{
			try {
				std::string path = "debug.xml";
				af::XML xml;
				xml.open(path);
				af::XML::Structure fileStruct;
				fileStruct = xml.read();
				xml.close();
				xml.create(path + ".t");
				xml.write(fileStruct);
				xml.close();
			}
			catch (...)
			{
				Assert::Fail();
			}
		}


		TEST_METHOD(afRead) {
			std::string buffer;
			af::read("r_test.unit", buffer);
			Assert::AreEqual("<test name=\"unit\">\nthis is a test</test>", buffer.data());
		}

		TEST_METHOD(afWrite) {
			std::fstream file;
			file.open("r_test.unit");
			Assert::IsTrue(file.is_open());
			af::write(file, "<test name=\"unit\">\nthis is a test</test>");
		}

	};
}