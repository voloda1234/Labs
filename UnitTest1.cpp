#include "pch.h"
#include "CppUnitTest.h"
#include "../lab5_1/lab5.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			double x = 5.0;
			double y = 6.0;

			double result;
			result = (function(x * y, pow(x, 2), pow(y, 2)) - pow(function(1, x, y), 2)) / 1 + function(sqrt(x), pow(y, 2), 1);
			Assert::AreEqual(result, 279.0);
		}
	};
}
