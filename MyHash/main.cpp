#include <unordered_set>
#include "MyHash.h"
#include <string>
#include <iostream>
#include <random>
#include <chrono>
#include <time.h>
#include <algorithm>
#include <fstream>

using namespace std::chrono;

int main()
{
	{
		int progon = 10;
		std::cout << "TIME MESURE: " << std::endl;
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<long long> nums;
		std::vector<long long> nums2;
		std::uniform_int_distribution<> dis2(1000, 1000000);
		for (int i = 0; i < 100000; i++)
		{
			nums.push_back(dis2(gen));
		}
		for (int i = 0; i < 100; i++)
		{
			nums2.push_back(dis2(gen));
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				MyHash<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.insert(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "myUSet insert: " << duration / progon << std::endl;
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				std::unordered_set<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.insert(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "USet insert: " << duration / progon << std::endl;
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				MyHash<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.contains(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "myUSet contains: " << duration / progon << std::endl;
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				std::unordered_set<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.contains(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "USet contains: " << duration / progon << std::endl;
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				MyHash<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.erase(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "myUSet erase: " << duration / progon << std::endl;
		}
		{
			long long duration = 0;
			for (int i = 0; i < progon; i++)
			{

				std::unordered_set<int> t;
				high_resolution_clock::time_point t1 = high_resolution_clock::now();
				for (int i = 0; i < 50000; i++)
				{
					t.erase(nums[i]);
				}
				high_resolution_clock::time_point t2 = high_resolution_clock::now();
				duration += std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count();
			}
			std::cout << "USet erase: " << duration / progon << std::endl;
		}
		std::cout << "--------------------------------------\n";
	}
	
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::vector<long long> nums;
		std::vector<long long> nums2;
		std::uniform_int_distribution<> dis2(1000, 1000000);
		for (int i = 0; i < 1000; i++)
		{
			nums.push_back(dis2(gen));
			nums2.push_back(dis2(gen));
		}
		MyHash<long long> test(2000);
		for (auto x : nums)
			test.insert(x);
		std::cout << test;
	}
	
}