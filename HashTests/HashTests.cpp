#include "pch.h"
#include "CppUnitTest.h"
#include "../MyHash/MyHash.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTests
{
	TEST_CLASS(HashTests)
	{
	public:
		
		TEST_METHOD(Add_false)
		{
			MyHash<int> test;
			test.insert(1);
			Assert::IsFalse(test.insert(1).second);
		}

		TEST_METHOD(Add_true)
		{
			MyHash<int> test;
			test.insert(1);
			Assert::IsTrue(test.insert(2).second);
		}

		TEST_METHOD(Rehash)
		{
			MyHash<int> test(1);
			test.insert(1);
			Assert::IsTrue(test.insert(2).second);
		}

		TEST_METHOD(contains_true)
		{
			MyHash<int> test;
			test.insert(1);
			Assert::IsTrue(test.contains(1));
		}

		TEST_METHOD(contains_false)
		{
			MyHash<int> test;
			test.insert(1);
			Assert::IsFalse(test.contains(2));
		}

		TEST_METHOD(size_test)
		{
			MyHash<int> test;
			Assert::AreEqual((size_t)0, test.size());
			test.insert(1);
			test.insert(2);
			test.insert(3);
			test.insert(4);
			test.insert(5);
			Assert::AreEqual((size_t)5,test.size());
		}
	};
}
