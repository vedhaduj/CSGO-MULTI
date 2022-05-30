#include <Windows.h>
#include <iostream>
#include <thread>


int main()
{
	DWORD localplayer = 0xDBA5BC;
	DWORD flags = 0x104;
	DWORD forcejump = 0x5280924;

	//misc
	DWORD fov = 0x31F4;
	DWORD flashalpha = 0x1046C;

	DWORD gameModule;

	gameModule = (DWORD)GetModuleHandle("client.dll");
	localplayer = *(DWORD*)(gameModule + localplayer);


	while (!GetAsyncKeyState(VK_END)) 
	{
		byte flag = *(BYTE*)(localplayer + flags);

		//comment this out if you don't want fov
		*(DWORD*)(localplayer + fov) = 120;

		*(DWORD*)(localplayer + flashalpha) = 0;

		if (GetAsyncKeyState(VK_SPACE) && flag & (1 << 0))
		{
			*(DWORD*)(gameModule + forcejump) = 6;
		}
		
	}
}

//dll injecto!
BOOL WINAPI DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH) {

		DisableThreadLibraryCalls(hModule);
		CreateThread(NULL, NULL, (LPTHREAD_START_ROUTINE)main, NULL, NULL, NULL);
	}
	return TRUE;
}
