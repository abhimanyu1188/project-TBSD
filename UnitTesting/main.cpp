#include "pch.h"
#include "CppUnitTest.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

extern "C" {
#include "Blackjack.h"
}

namespace UnitTesting
{
	TEST_CLASS(UnitTesting)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			int equal = 0; 
			Assert::AreEqual(equal, 0);
		}
	};
}
