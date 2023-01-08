//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include "CDeck.h"
using std::cout;
using std::endl;
using std::vector;
using std::string;

class CPlayer
{
private:
	string mName;	//Player's name
	int mScore;	//Player's score
	vector<int> mHand;	//Player's hand
	int mRoundWins;	//Number of round wins
	int mGameWins;	//Number of round wins
	bool mAceInHand;	//Flag to show if player has an Ace in hand
	bool mAceHigh;	//Flag to show if Ace value changed to 11
	bool mBust;	//Flag to show if player is bust
	bool mStand;	//Flag to show if player is sticking with their hand
	CDeck* mpDeck;	//Pointer to CDeck class
	CPlayer* mpNextPlayer;	//Pointer to next CPlayer in list

	void ClearUserInput();	//Clear user input buffer and reset error flags
	void AddToScore(int card);	//Calculate player's score
	void Hit(CDeck* pDeck);	//Give player another card
	void Stand();	//Player keeps current hand
	void PickUpCard(int card);	//Add input card to hand
	void DisplayHand();	//Output player's hand to console
public:
	CPlayer(string name, CDeck* pDeck);	//Constructor

	string GetName();	//Return player's name
	int GetScore();	//Return player's score
	int GetRoundWins();	//Return player's number of round wins
	int GetGameWins();	//Return player's number of game wins
	bool GetBust();	//Return flag for if player is bust
	CPlayer* GetNextPlayer();	//Return pointer to next player in list

	void SetNextPlayer(CPlayer* pNextPlayer);	//Set pointer to next player
	void DealCards();	//Get starting cards
	void TakePlayerTurn(CDeck* pDeck);	//Input player takes their turn
	void ResetForRound();	//Reset player's variables for new round
	void ResetForGame();	//Reset player's variables for new game
	void AddWin(int type);	//Increment player's number of round/game wins
};