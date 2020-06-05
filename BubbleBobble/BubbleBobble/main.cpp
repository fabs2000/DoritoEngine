#include "Game.h"

#if _DEBUG
#include <vld.h>
#endif

int main()
{
	Game engine;
	engine.Initialize(1280,960,"DoritoEngine");
	engine.Run();
	engine.Cleanup();
	return 0;
}