//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include "CDeck.h"
#include "CPlayers.h"
#include "CGameManager.h"
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::numeric_limits;
using std::streamsize;

class CTournamentManager
{
private:
	int mNumGames;	//Total number of games played
	unique_ptr <CDeck> mpDeck;	//Pointer to CDeck class
	unique_ptr <CPlayers> mpPlayers;	//Pointer to CPlayers class
	unique_ptr <CGameManager> mpGame;	//Pointer to CGameManager class

	void ClearUserInput();	//Clear user input buffer and reset error flags
	void DisplayTitle();	//Display the title to the console
	void PlayTournament();	//Play game and then repeat until stopped
	void EndTournament();	//Calculate and display winner(s) of tournament
	void DisplayWinners(vector<CPlayer*> winningPlayers);	//Display winning players message
public:
	CTournamentManager();	//Constructor
};