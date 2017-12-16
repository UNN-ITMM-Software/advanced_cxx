#pragma once
#include <chrono>

namespace measure
{
	template<typename F, typename ...Args>
	static std::chrono::milliseconds::rep execution(F func, Args&&... args)
	{
		auto start = std::chrono::system_clock::now();

		func(std::forward<Args>(args)...);

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>
			(std::chrono::system_clock::now() - start);

		return duration.count();
	}
};