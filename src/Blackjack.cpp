//Author: Alex Reed

#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#include "CTournamentManager.h"

int main()
{
	{
		auto newTournament{ make_unique<CTournamentManager>() };	//Create new pointer to CTournamentManager
	}

	_CrtDumpMemoryLeaks();	//Check for memory leaks
}