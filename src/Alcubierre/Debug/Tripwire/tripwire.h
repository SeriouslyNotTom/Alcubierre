#pragma once

#include <string>

namespace Alcubierre
{
	namespace Tripwire
	{

		struct TRIPWIRE_CHANNEL
		{
			const char* prefix_tag;
			const char* suffix_tag;
		};

		enum SEVERITY
		{
			IM_TOO_YOUNG_TO_DIE = 663,
			HURT_ME_PLENTY = 664,
			ULTRA_VIOLENCE = 665,
			NIGHTMARE = 666
		};

		//asserts
		//bool assert(bool check_val); //serverity is determined by "tripwire::setDefaultAssertionServerity"
		//bool assert(bool check_val, Tripwire::SEVERITY raise_level);
		//bool assert(bool check_val, Tripwire::SEVERITY raise_level, std::string msg);
		//bool assert(bool check_val, std::string msg);


		//messages
		void nonCriticalErrorMessage();

		//errors
		bool error(Tripwire::SEVERITY raise_level);
		bool error(Tripwire::SEVERITY raise_level, std::string msg);
		bool error(std::string msg);

	}
}