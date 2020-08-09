#include "DoritoPCH.h"
#include "DoritoEngine.h"

#ifdef _DEBUG
#include <vld.h>
#endif


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	DoritoEngine engine;
	engine.Initialize(1280, 720, "DoritoEngine");
	engine.Run();
	engine.Cleanup();

	return 0;
}
