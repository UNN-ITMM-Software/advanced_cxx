#pragma once
#include <chrono>
#include <omp.h>

namespace measure
{
	namespace chrono
	{
		template<typename F, typename ...Args>
		static std::chrono::milliseconds::rep execution(int32_t count, F func, Args&&... args)
		{
			std::chrono::milliseconds::rep times_average = 0;

			for (int i = 0; i < count; ++i)
			{
				auto start = std::chrono::system_clock::now();

				func(std::forward<Args>(args)...);

				times_average += std::chrono::duration_cast<std::chrono::milliseconds>
					(std::chrono::system_clock::now() - start).count();
			}

			return times_average / count;
		}
	}
#if defined(_OPENMP)
	namespace omp
	{
		template<typename F, typename ...Args>
		static double execution(int32_t count, F func, Args&&... args)
		{
			double times_average = 0.;
			for (int i = 0; i < count; ++i)
			{
				auto start = omp_get_wtime();

				func(std::forward<Args>(args)...);

				times_average += omp_get_wtime() - start;
			}

			return (times_average / count) * 1000;
		}
	}
#endif
}

