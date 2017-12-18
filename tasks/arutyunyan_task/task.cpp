/*  Задан массив целых чисел (тип int). Нужно найти, если ли в массиве такое число, что количество чисел меньших данного числа равно заданному числу. Искомое число должно быть максимальным.
Примеры:
[1,1,1,3] - ответ 3 (ровно 3 числа меньше трех)
[1,3,1,1] - ответ 3
[0,3,1,2] - ответ 3 (одно число меньше единицы, два числа меньше двойки и три числа меньше тройки, но тройка максимальная из них, поэтому ответ три)
[12,1,6] - ответ 0
[1] - ответ 0
[1,1] - ответ 0
*/

#include <functional>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <iostream>
#include "measure.h"

namespace SimpleSolution
{
	int32_t run(std::vector<int32_t> v)
	{
		if (v.size() < 2)
		{
			return 0;
		}

		//O(nlog(n))
		std::sort(v.begin(), v.end());

		//O(n)
		for (auto index = v.size() - 1; index > 0; --index)
		{
			if (v[index] == index && v[index - 1] != index)
			{
				return v[index];
			}
		}

		return 0;
	}
}

namespace MultisetSolution
{
	int32_t run(const std::vector<int32_t>& values)
	{
		if (values.size() < 2)
		{
			return 0;
		}

		// O(n*log(n))
		std::multiset<int32_t, std::greater<int32_t>> sortValues(values.cbegin(), values.cend());

		// O(n)
		int prevElemCount = sortValues.size() - 1;
		for (auto it = sortValues.begin(); it != sortValues.end(); ++it, --prevElemCount)
		{
			auto isLast(prevElemCount == 0);
			auto nextIt = std::next(it);
			if (*it == prevElemCount && (isLast || *it != *nextIt))
			{
				return *it;
			}
		}
		return 0;
	}
};

namespace BinaryHeapSolution
{
	int32_t run(std::vector<int32_t> v)
	{
		if (v.size() < 2)
		{
			return 0;
		}
		else if (v.size() == 2)
		{
			int32_t el;
			if (((el = (v[0] > v[1] ? v[0] : v[1]))) == 1 && v[0] != v[1])
			{
				return 1;
			}
		}
		else
		{
			//O(n)
			std::make_heap(v.begin(), v.end());

			//O(n*log(n))
			while (v.size() > 2)
			{
				if (v[0] == v.size() - 1 && v[0] != v[1] && v[0] != v[2])
				{
					return v[0];
				}
				//O(log(n))
				std::pop_heap(v.begin(), v.end());
				//O(1)
				v.pop_back();
			}
		}
		return 0;
	}
}

namespace IndexOrientedSolution
{
	int32_t run(const std::vector<int32_t>& values)
	{
		if (values.size() < 2)
		{
			return 0;
		}

		auto size(values.size());
		auto totalCount(size);
		std::vector<int32_t> valueCounts(size);
		// O(n)
		for (auto val : values)
		{
			if (val < 0 || val < size)
			{
				val = val < 0 ? 0 : val;
				++valueCounts[val];
			}
			else
			{
				--totalCount;
			}
		}

		// O(n)
		for (auto i = valueCounts.size() - 1; i > 0; --i)
		{
			if (valueCounts[i] > 0)
			{
				totalCount -= valueCounts[i];
				if (i == totalCount)
				{
					return i;
				}
			}
		}
		return 0;
	}
};


int main()
{
	// correctness tests
	std::vector<std::vector<int32_t>> testValues = {
		{ 4, 5, 3, 3, 3, 3, 3, 7, 7 },
		{ 5, -1, 4, 7, -1, 4, 17, 6, 1, 3 },
		{ -1 },
		{ 0 },
		{ -4, -3, -2, -1, 5, 5, 5, -1 },
		{ 1, 1, 1, 1, 1 },
		{ 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 },
		{ 17, 17, 17 }
	};

	std::vector<int32_t> testResults = { 7, 4, 0, 0, 5, 0, 10, 0 };

	for (auto i = 0; i < testValues.size(); ++i)
	{
		auto s_v = SimpleSolution::run(testValues[i]);
		assert(s_v == testResults[i]);
		auto m_v = MultisetSolution::run(testValues[i]);
		assert(m_v == testResults[i]);
		auto b_v = BinaryHeapSolution::run(testValues[i]);
		assert(b_v == testResults[i]);
		auto i_v = IndexOrientedSolution::run(testValues[i]);
		assert(i_v == testResults[i]);
	}

	// performance tests
	testValues.clear();
	std::vector<int32_t> bigVector;
	for (int i = 0; i < 10000000; ++i)
		bigVector.push_back(i);

	// ascending order
	testValues.push_back(bigVector);
	
	// descending order
	std::reverse(bigVector.begin(), bigVector.end());
	testValues.push_back(bigVector);

	// random order
	std::random_shuffle(bigVector.begin(), bigVector.end());
	testValues.push_back(bigVector);

	// random order
	std::random_shuffle(bigVector.begin(), bigVector.end());
	testValues.push_back(bigVector);

	// random order
	std::random_shuffle(bigVector.begin(), bigVector.end());
	testValues.push_back(bigVector);

	// random order
	std::random_shuffle(bigVector.begin(), bigVector.end());
	testValues.push_back(bigVector);

	for (auto i = 0; i < testValues.size(); ++i)
	{
		const int32_t count = 50;
		std::cout << "\nTest #" << i << "\n";

		auto time = measure::chrono::execution(count, SimpleSolution::run, testValues[i]);
		std::cout << "SimpleSolution: " << time << " ms \n";

		time = measure::chrono::execution(count, MultisetSolution::run, testValues[i]);
		std::cout << "MultisetSolution: " << time << " ms \n";

		time = measure::chrono::execution(count, BinaryHeapSolution::run, testValues[i]);
		std::cout << "BinaryHeapSolution: " << time << " ms \n";

		time = measure::chrono::execution(count, IndexOrientedSolution::run, testValues[i]);
		std::cout << "IndexOrientedSolution: " << time << " ms \n";
	}
#if defined(_OPENMP)
	for (auto i = 0; i < testValues.size(); ++i)
	{
		const int32_t count = 50;
		std::cout << "\nTest #" << i << "\n";

		auto time = measure::omp::execution(count, SimpleSolution::run, testValues[i]);
		std::cout << "SimpleSolution: " << time << " ms \n";

		time = measure::omp::execution(count, MultisetSolution::run, testValues[i]);
		std::cout << "MultisetSolution: " << time << " ms \n";

		time = measure::omp::execution(count, BinaryHeapSolution::run, testValues[i]);
		std::cout << "BinaryHeapSolution: " << time << " ms \n";

		time = measure::omp::execution(count, IndexOrientedSolution::run, testValues[i]);
		std::cout << "IndexOrientedSolution: " << time << " ms \n";
	}
#endif
}