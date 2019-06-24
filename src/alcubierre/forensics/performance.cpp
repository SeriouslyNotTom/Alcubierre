#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

class profiler
{
	high_resolution_clock::time_point in_point;
	high_resolution_clock::time_point out_point;

public:

	profiler()
	{

	}

	void in()
	{
		in_point = high_resolution_clock::now();
	}

	void out()
	{
		out_point = high_resolution_clock::now();
	}

	uint64_t nanos()
	{
		uint64_t nano_in = duration_cast<nanoseconds>(in_point.time_since_epoch()).count();
		uint64_t nano_out = duration_cast<nanoseconds>(out_point.time_since_epoch()).count();
		return int(nano_out-nano_in);
	}

};