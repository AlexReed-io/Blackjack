//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <limits>
#include "CDeck.h"
#include "CPlayer.h"
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;
using std::unique_ptr;
using std::make_unique;
using std::numeric_limits;
using std::streamsize;

class CPlayers
{
private:
	CDeck* mpDeck;	//Pointer to CDeck class
	vector<unique_ptr <CPlayer>> mPlayers;	//Vector of pointers to CPlayer objects

	void ClearUserInput();	//Clear user input buffer and reset error flags
	void NewPlayer(string name);	//Create new player with input name
	void DealCards();	//Give each player starting cards
public:
	CPlayers(CDeck* pDeck);	//Constructor

	int GetHighestScore();	//Return highest player score
	int GetHighestRoundWins();	//Return highest player round wins
	int GetHighestGameWins();	//Return highest player game wins
	CPlayer* GetFirst();	//Return pointer to first player in list

	void CreatePlayers();	//Fill mPlayers vector
	void ResetPlayersForRound();	//Reset players in mPlayers for new round
	void ResetPlayersForGame();	//Reset players in mPlayers for new game
};