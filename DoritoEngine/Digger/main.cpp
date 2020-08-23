#include "DoritoPCH.h"
#include "DoritoEngine.h"

#ifdef _DEBUG
#include <vld.h>
#endif


int main()
{
	srand(static_cast<unsigned int>(time(NULL)));

	DoritoEngine engine;
	engine.Initialize(1600, 900, "DoritoEngine", true);
	engine.Run();
	engine.Cleanup();

	return 0;
}
