#include "pch.h"
#include "CppUnitTest.h"
#include "../lab7.3/7.3it.cpp"
#include "../lab7.3/7.3rec.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
            int a[3][3] = { {1, 2,5}, {3, 4,4}, {7, -2,9} };

            int** dynamicArray = new int* [3];
            for (int i = 0; i < 3; ++i) {
                dynamicArray[i] = new int[3];
                for (int j = 0; j < 3; ++j) {
                    dynamicArray[i][j] = a[i][j];
                }
            }

            int excpectation = 11;

            Assert::AreEqual(excpectation, SumAboveMainDiagonal(dynamicArray, 3));
		}

        TEST_METHOD(TestMethod2)
        {
            int a[3][3] = { {1, 2,5}, {3, 4,4}, {7, -2,9} };

            int** dynamicArray = new int* [3];
            for (int i = 0; i < 3; ++i) {
                dynamicArray[i] = new int[3];
                for (int j = 0; j < 3; ++j) {
                    dynamicArray[i][j] = a[i][j];
                }
            }

            int sum = 0;
            int excpectation = 11;

            Assert::AreEqual(excpectation, SumAboveMainDiagonalRec(dynamicArray, 3, 0, 1,sum));
        }
	};
}
