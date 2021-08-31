#include <Alcubierre/Debug/Tripwire/tripwire.h>
#include <spdlog/spdlog.h>

using namespace Alcubierre::Tripwire;

void logger_func(char* str, bool error)
{
	const char* pattern_string = "[%d/%m/%Y][%I:%M:%S.%e %p]%v";

	////const char* base = "\u001b[95m[LOG::%s]\u001b[36m %s\u001b[0m";
	//const char* base = "%s";
	//char* buff = new char[8192];
	//va_list lst;
	//va_start(lst, fmt);
	//vsprintf(buff, fmt, lst);
	//va_end(lst);
	//char* finalbuff = new char[strlen(base) + strlen(buff)];
	//sprintf(finalbuff, base, buff);
	////fprintf(stdout, finalbuff);
	//if (error) { spdlog::error(finalbuff); }
	//else {
	//	spdlog::info(finalbuff);
	//}

}

void Exit_Func(SEVERITY sev)
{
	if (sev == SEVERITY::NIGHTMARE)
	{
		exit(sev);
		abort();
	}
}

bool process_failure(SEVERITY sev)
{
	return true;
}

//bool Alcubierre::Tripwire::assert(bool check_val)
//{
//	if (check_val == true)
//	{
//		return process_failure(default_serverity);
//	}
//	return false;
//}

bool Alcubierre::Tripwire::error(SEVERITY sev, std::string msg)
{
	return process_failure(sev);
}