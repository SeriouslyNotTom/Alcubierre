#pragma once

#include <Windows.h>
#include <stdlib.h>
#include <WinBase.h>
#include <debugapi.h>

///I KNOW WHO YOU ARE
///BECAUSE I BACKTRACED IT!
///AND YOU'VE BEEN REPORTED TO THE CYBERPOLICE
static void Backtrace()
{
	PVOID* frames = new PVOID[4];
	int frames_num = CaptureStackBackTrace(0, 4, frames, NULL);

}