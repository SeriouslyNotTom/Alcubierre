#pragma once
#define GLFW_INCLUDE_NONE
#include <Alcubierre/Alcubierre.h>
#include <Alcubierre/Engine/Engine.h>
#include <Alcubierre/Debug/Log.h>
#include <spdlog/spdlog.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <thread>

#ifdef WIN32
#include <spdlog/sinks/msvc_sink.h>
#endif // WIN32

int Alcubierre::argc = NULL;
char* Alcubierre::argv = NULL;
bool Alcubierre::Debug_Mode = true;
Alcubierre::ALCB_Engine* Alcubierre::Engine::engine_core = NULL;
std::function<void()>** Alcubierre::ban_list;
std::vector<std::function<void()>> Alcubierre::hook_list;

using namespace Alcubierre;

bool ALCB_Task_Manager::addTask(ALCB_TASK* task)
{
	tasks.push_back(task);
	return true;
}

void ALCB_Task_Manager::Load()
{

}

void ALCB_Task_Manager::Start()
{

}

void ALCB_Task_Manager::Tick()
{
	int numtasks = tasks.size();

	for (int i = 0; i < numtasks; i++)
	{
		tasks[i]->Tick();
	}
}



void Alcubierre::Initialize_Core()
{

	std::thread alcb_main_thread;

	spdlog::set_level(spdlog::level::debug);
	try
	{
		auto file_logger = std::make_shared<spdlog::sinks::basic_file_sink_mt>("jatapt-log.txt", false);
#ifdef WIN32
			auto msvc_sink = std::make_shared<spdlog::sinks::msvc_sink_mt>();
			spdlog::default_logger()->sinks().push_back(msvc_sink);
#endif // WIN32

		spdlog::default_logger()->sinks().push_back(file_logger);
		spdlog::flush_on(spdlog::level::info);
		spdlog::debug("-------------------- Beginning of Log --------------------");
		//spdlog::set_default_logger();
	}
	catch (const spdlog::spdlog_ex& ex)
	{
		std::cout << "Log init failed: " << ex.what() << std::endl;
	}
	Alcubierre::Debug::Log::Msg("Alcubierre","(%s %s) [%s %s] %s", PROJECT_NAME_READABLE, PROJECT_OS, PROJECT_BUILD_TYPE, PROJECT_VER, PROJECT_VER_TYPE, PROJECT_BUILD_DATE);
	Info = _Info();
	Basic_Config = _Basic_Config();

	Alcubierre::Engine::engine_core = new Alcubierre::ALCB_Engine();

	ban_list = new std::function<void()>*[64];
	hook_list = std::vector<std::function<void()>>();

}

bool Alcubierre::addHook(std::function<void()> func)
{
	hook_list.push_back(func);
	return true;
}

void Alcubierre::update()
{
	Engine::engine_core->tick();
	for each (std::function<void()> var in hook_list)
	{
		var();
	}
}

void Alcubierre::Accept_Arguments(int argc, char* argv)
{
	Alcubierre::argc = argc;
	Alcubierre::argv = argv;



}

void Alcubierre::Exit(int code)
{
	Alcubierre::Debug::Log::Msg("Alcubierre", "Got Exit Code (%i)", code);
	exit(code);
}
