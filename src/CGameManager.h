//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include "CPlayers.h"
#include "CRoundManager.h"
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::numeric_limits;
using std::streamsize;

class CGameManager
{
private:
	int mRound;	//Current round in game
	int mNumRounds;	//Total number of rounds in game
	CDeck* mpDeck;	//Pointer to CDeck class
	CPlayers* mpPlayers;	//Pointer to CPlayers class
	unique_ptr <CRoundManager> mpRound;	//Pointer to CRoundManager class
	
	void ClearUserInput();	//Clear user input buffer and reset error flags
	void SetupGame();	//Setup new game
	void CreateRounds();	//Ask for number of rounds and setup variables
	void EndGame();	//Calculate and display winner(s) of game
	void DisplayWinners(vector<CPlayer*> winningPlayers);	//Display winning players message
public:
	CGameManager(CDeck* pDeck, CPlayers* pPlayers);	//Constructor

	void PlayGame();	//Play the rounds of the game
};