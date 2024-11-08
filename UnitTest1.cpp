#include "pch.h"
#include "CppUnitTest.h"
#include "../lab6_1/lab6.1int.cpp"
#include "../lab6_1/lab6.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			const int n = 5;
			int a[n] = {4, 12, -2, 1, -6};
			int expectation = CountElements(a, n);
			int actual = 4;
			Assert::AreEqual(expectation, actual);
		}

		TEST_METHOD(TestMethod2)
		{
			const int n = 5;
			int a[n] = { 4, 12, -2, 1, -6 };
			int expectation = SumElements(a, n, 0, 0);
			int actual = 15;
			Assert::AreEqual(expectation, actual);
		}
	};
}
