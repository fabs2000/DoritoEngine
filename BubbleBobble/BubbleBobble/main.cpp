#include "DoritoPCH.h"
#include "DoritoEngine.h"

//Memory Leak detection
//More detailed explanation of where leak is
//#define _CRTDBG_MAP_ALLOC
//#include <stdlib.h>
//#include <crtdbg.h>

#ifdef _DEBUG
#include <vld.h>
#endif

int main()
{
	{
		srand(static_cast<unsigned int>(time(NULL)));

		DoritoEngine engine;
		engine.Initialize(1280, 720, "DoritoEngine");
		engine.Run();
		engine.Cleanup();
	}

	return 0;
}


//Using this causes memory leaks since SFML deletes its resurces after application exits

#pragma region MemoryLeak

////DETECTS LEAKS
//#ifdef _DEBUG
//	// Notify user if heap is corrupt
//HeapSetInformation(NULL, HeapEnableTerminationOnCorruption, NULL, 0);
//
//// Report detected leaks when the program exits
//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
//
//// Set a breakpoint on the specified object allocation order number
////_CrtSetBreakAlloc(2696);
//#endif
//
//
//
////DUMP
//#ifdef _DEBUG
//_CrtDumpMemoryLeaks();
//#endif

#pragma endregion