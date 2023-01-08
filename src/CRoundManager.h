//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include "CDeck.h"
#include "CPlayers.h"
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::numeric_limits;
using std::streamsize;

class CRoundManager
{
private:
	CDeck* mpDeck;	//Pointer to CDeck class
	CPlayers* mpPlayers;	//Pointer to CPlayers class

	void ClearUserInput();	//Clear user input buffer and reset error flags
	void SetupRound();	//Setup new round
	void EndRound();	//Calculate and display winner(s) of round
	void DisplayWinners(vector<CPlayer*> winningPlayers);	//Display winning players message
public:
	CRoundManager(CDeck* pDeck, CPlayers* pPlayers);	//Constructor
	
	void PlayRound(int mRound, int mNumRounds);	//Play a round
};