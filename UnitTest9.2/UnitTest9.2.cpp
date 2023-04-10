#include "pch.h"
#include "CppUnitTest.h"
#include "../Source.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest92
{
	TEST_CLASS(UnitTest92)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			Student students[3] =
			{
				{"a", I,Kn, 5,4,3},
				{"b", I,Kn, 5,5,2},
				{"c", I,In, 3,3,5}
			};
			int index = BinSearch(students, 3, "b", Kn, 5);
			Assert::AreEqual(1, index);
		}
	};
}
