#include "conversion.h"
#include "memscan.h"
#include <iostream>

void init()
{
	begin_console("ProtoConversion!");

	l = lua_open(); //initialize the vanilla lua state

	int vf_table = addresses::scriptcontext;
	script_context = memory::scan(PAGE_READWRITE, (char*)&vf_table, (char*)"xxxx");

	rl = (script_context + LOCALSCRIPTGLOBALSTATE) - *(int*)(script_context + LOCALSCRIPTGLOBALSTATE); //declare the globalstate

	while (true)
	{
		std::cout << ">";

		std::string input;
		std::getline(std::cin, input);
		std::vector<std::string> arguments = split_string(input, ' ');

		if (arguments.at(0) == "cmds")
		{
			std::cout << "Current Commands:\n- There are no commands right now";
		}

		else if (!arguments.at(0).empty())
		{
			execute_script(rl, l, input);
		}
	}
}

BOOL WINAPI DllMain(HMODULE dll, DWORD reason, PVOID reserved) {
	if (reason == DLL_PROCESS_ATTACH) {
		DisableThreadLibraryCalls(dll);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)init, NULL, NULL, NULL);
	}
	return TRUE;
}