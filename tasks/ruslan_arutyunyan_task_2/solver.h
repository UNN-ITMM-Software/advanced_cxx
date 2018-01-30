#pragma once

#include <vector>
#include <unordered_map>

class ISolver
{
public: 
	virtual int32_t solve(int number) = 0;
};

class SimpleSolver : public ISolver
{
public:
	SimpleSolver(const std::vector<int32_t>& num) : numbers(num) { }

	int32_t solve(int32_t number) override
	{
		//Worst case: O((n^2)*log(n))
		int32_t count{ };
		auto end{ numbers.cend() };
		for (auto it = numbers.cbegin(); it != end; ++it)
		{
			auto remainder = number - *it;
			auto it1 = std::find(it + 1, end, remainder);
			while (it1 != end)
			{
				it1 = std::find(it1 + 1, end, remainder);
				++count;
			}
		}
		return count;
	}

private:
	std::vector<int32_t> numbers;
};

class MapLinearSolver : public ISolver
{
public:
	MapLinearSolver(const std::vector<int32_t> &array)
	{
		for (const auto &number : array)
		{
			++unique_els[number];
		}
	}

	int32_t solve(int32_t number) override
	{
		int32_t count { };

		for (const auto& it : unique_els)
		{
			int32_t remainder = number - it.first;

			if (remainder == it.first)
			{
				count += ((it.second - 1) * it.second) / 2;
			}
			else if (remainder > it.first)
			{
				auto it2 = unique_els.find(remainder);

				if (it2 != unique_els.end())
				{
					count += it.second * it2->second;
				}
			}
		}
		return count;
	}

private:
	std::unordered_map<int32_t, int32_t> unique_els;
};


class MapConstantSolver : public ISolver
{
public:
	MapConstantSolver(const std::vector<int32_t>& numbers)
	{
		auto end{ numbers.cend() };
		for (auto it = numbers.cbegin(); it != end; ++it)
		{
			for (auto it1 = it + 1; it1 != end; ++it1)
			{
				++sums[*it + *it1];
			}
		}
	}

	int32_t solve(int32_t number) override
	{
		return sums[number];
	}

private:
	std::unordered_map<int32_t, int32_t> sums;
};