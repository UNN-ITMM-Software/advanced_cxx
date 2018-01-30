#include "solver.h"
#include "measure.h"
#include <iostream>
#include <cassert>
#include <algorithm>
#include <map>
#include <ctime>
#include <cstdlib>
#include <memory>

std::vector<int32_t> getRandomPerfomanceTest(int32_t elementCount, int32_t source)
{
	std::vector <int32_t> numbers;
	for (auto i = 0; i < elementCount / 2; ++i)
	{
		source = source ? source : 1;
		auto el = rand() % (source * 2);
		auto remainder = source - el;
		numbers.emplace_back(el);
		numbers.emplace_back(remainder);
	}
	std::random_shuffle(numbers.begin(), numbers.end());
	return numbers;
}

template<typename ClassType>
void ctorCall(const std::vector<int32_t> &array)
{
	ClassType instance(array);
}

int main()
{
	// correctness tests
	std::map<std::vector<int32_t>, std::pair<int32_t, int32_t>> correctnessTests = {
		{ { 2, 2, 2, 2 },{ 4, 6 } },
	{ { 1, 2, -1, 4 },{ 3, 2 } },
	{ { 1, 2, 1, 2 },{ 3, 4 } },
	{ { 1, 0 },{ 2, 0 } }
	};
	for (const auto& it : correctnessTests)
	{
		const auto& test = it.first;
		const auto& source = it.second.first;
		const auto& target = it.second.second;

		SimpleSolver ss(test);
		auto result = ss.solve(source);
		assert(result == target);

		MapConstantSolver ms(test);
		result = ms.solve(source);
		assert(result == target);

		MapLinearSolver mls(test);
		result = mls.solve(source);
		assert(result == target);
	}

	// performance tests
	const int32_t N = 10000000;
	std::map<std::vector<int32_t>, int32_t> performanceTests;

	performanceTests[getRandomPerfomanceTest(N, 5)] = 5;
	performanceTests[getRandomPerfomanceTest(N, 1000)] = 1000;
	performanceTests[getRandomPerfomanceTest(N, 31)] = 31;
	performanceTests[getRandomPerfomanceTest(N, 1)] = 1;
	performanceTests[getRandomPerfomanceTest(N, 45)] = 1;
	performanceTests[getRandomPerfomanceTest(N, 0)] = 0;
	performanceTests[getRandomPerfomanceTest(N, 2345654)] = 2345654;
	performanceTests[getRandomPerfomanceTest(N, 22345)] = 22345;
	performanceTests[getRandomPerfomanceTest(N, 512)] = 512;

	std::cout << "\t\tSimple\tConstructor\tSolve\t\t\tMapLinear\\tConstructor\tSolve\tMapConst\t\t\tConstructor\tSolve\n\n";
	const int32_t count = 50;

	auto run = [](std::shared_ptr<ISolver> s, int n) -> int
	{
		return s->solve(n);
	};

	int32_t i = 0;
	for (const auto& test : performanceTests)
	{
		std::cout << i++ << "\t\t";
		std::cout << measure::chrono::execution(count, ctorCall<SimpleSolver>, test.first) << "ms \t\t"
			<< measure::chrono::execution(count, run, std::shared_ptr<ISolver>(new SimpleSolver(test.first)), test.second) << "ms \t\t"
			<< measure::chrono::execution(count, ctorCall<MapLinearSolver>, test.first) << "ms \t\t"
			<< measure::chrono::execution(count, run, std::shared_ptr<ISolver>(new MapLinearSolver(test.first)), test.second) << "ms \t\t"
			<< measure::chrono::execution(count, ctorCall<MapConstantSolver>, test.first) << "ms \t\t"
			<< measure::chrono::execution(count, run, std::shared_ptr<ISolver>(new MapConstantSolver(test.first)), test.second) << "ms \t\t\n";


	}
	return 0;
}

