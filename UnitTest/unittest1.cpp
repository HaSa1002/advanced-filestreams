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
			xml.open("u_test");
			af::XML::Structure s = xml.read();
			bool same = (fileStruct == s);
				
			Assert::IsTrue(!same);
			
			xml.close();
		}

	};
}