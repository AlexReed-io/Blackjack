//Author: Alex Reed

#include "CRoundManager.h"

//Constructor
CRoundManager::CRoundManager(CDeck* pDeck, CPlayers* pPlayers)
{
	mpDeck = pDeck;	//Assign pointer to CDeck class
	mpPlayers = pPlayers;	//Assign pointer to CPlayers class
}

//Clear user input buffer and reset error flags
void CRoundManager::ClearUserInput()
{
	cin.clear();	//Reset input error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Clear input buffer
}

//Setup new round
void CRoundManager::SetupRound()
{
	mpDeck->CreateDeck();	//Create new deck of cards
	mpPlayers->ResetPlayersForRound();
}

//Loop through players and take turns then
//calculate and display round winner(s)
void CRoundManager::PlayRound(int mRound, int mNumRounds)
{
	SetupRound();
	
	cout << "==========" << endl << endl;	//Output seperator line
	cout << "ROUND " << mRound << " (of " << mNumRounds << ")" << endl << endl;	//Output round number

	CPlayer* pCurrentPlayer = mpPlayers->GetFirst();	//Get first player in list

	//Loop through players
	while (pCurrentPlayer != nullptr)
	{
		pCurrentPlayer->TakePlayerTurn(mpDeck);	//Take turn for player

		pCurrentPlayer = pCurrentPlayer->GetNextPlayer();	//Get next player in list
	}

	EndRound();
}

//Calculate winner(s) of round and output to console
void CRoundManager::EndRound()
{
	cout << "=====" << endl << endl << "ROUND OVER" << endl;	//Output message to console

	vector<CPlayer*> winningPlayers;	//Vector of pointers to winning players
	int highestScore = mpPlayers->GetHighestScore();	//Get highest score from mPlayers vector

	//If at least one player is not bust
	if (highestScore > 0)
	{
		CPlayer* pCurrentPlayer = mpPlayers->GetFirst();	//Get first player in list

		//Loop through players
		while (pCurrentPlayer != nullptr)
		{
			//If player isn't bust and has highest score then
			//add to winningPlayers vector
			if (pCurrentPlayer->GetScore() == highestScore)
			{
				winningPlayers.push_back(pCurrentPlayer);
			}

			pCurrentPlayer = pCurrentPlayer->GetNextPlayer();	//Get next player in list
		}
	}

	DisplayWinners(winningPlayers);
}

//Create winning players message and output to console
void CRoundManager::DisplayWinners(vector<CPlayer*> winningPlayers)
{
	string winningPlayersMessage = "";	//Winning players message for output
	vector<CPlayer*>::iterator winningPlayersIterator = winningPlayers.begin();	//Iterator for winningPlayers vector

	//Check number of winning players
	if (winningPlayers.size() > 1)
	{
		//Loop through winningPlayers vector
		for (auto player : winningPlayers)
		{
			player->AddWin(0);	//Add round win to player

			//Add comma or and to output message depending
			//on where player name is in the list
			if (player == winningPlayers.back())
			{
				winningPlayersMessage += " and ";
			}
			else if (player != winningPlayers.front())
			{
				winningPlayersMessage += ", ";
			}

			//Add player name to output message
			winningPlayersMessage += player->GetName();
		}

		winningPlayersMessage += " win the round!";	//Add ending to output message
	}
	else if (winningPlayers.size() == 1)
	{
		(winningPlayers.front())->AddWin(0);	//Add round win to player

		//Create output message
		winningPlayersMessage += (winningPlayers.front())->GetName();
		winningPlayersMessage += " wins the round!";
	}
	else
	{
		winningPlayersMessage = "Nobody wins the round.";	//Create output message
	}

	cout << winningPlayersMessage << endl << endl;	//Output winning players message to console
}