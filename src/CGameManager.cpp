//Author: Alex Reed

#include "CGameManager.h"

//Constructor
CGameManager::CGameManager(CDeck* pDeck, CPlayers* pPlayers)
{
	mRound = 1;	//Set starting round number
	mNumRounds = 0;	//Initialise total number of rounds
	mpDeck = pDeck;	//Assign pointer to CDeck class
	mpPlayers = pPlayers;	//Assign pointer to CPlayers class
	mpRound = make_unique<CRoundManager>(mpDeck, mpPlayers);	//Create pointer to CRoundManager class
}

//Clear user input buffer and reset error flags
void CGameManager::ClearUserInput()
{
	cin.clear();	//Reset input error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Clear input buffer
}

//Setup new game
void CGameManager::SetupGame()
{
	mpPlayers->ResetPlayersForGame();
	CreateRounds();
}

//Ask user for number of rounds and setup
//mRound and mNumRounds variables
void CGameManager::CreateRounds()
{
	mRound = 1;	//Set starting round number
	mNumRounds = 0;	//Initialise total number of rounds
	
	//Ask how many rounds should be played
	//Loop until chosen number is between 1 and 10
	while (mNumRounds < 1 || mNumRounds > 10)
	{
		//Output request to console
		cout << endl << "You can play between 1 and 10 rounds." << endl;
		cout << "How many rounds would you like to play? ";

		cin >> mNumRounds;	//Get user input

		ClearUserInput();
	}

	cout << endl << endl;
}

//Loop through number of rounds and play each round then
//calculate and display game winner(s)
void CGameManager::PlayGame()
{
	SetupGame();
	
	//Play each round up to total number of rounds
	while (mRound <= mNumRounds)
	{
		mpRound->PlayRound(mRound, mNumRounds);
		mRound++;	//Increment round number
	}

	EndGame();
}

//Calculate winner(s) of game and output to console
void CGameManager::EndGame()
{
	cout << "==========" << endl << endl << "GAME OVER" << endl;	//Output message to console

	vector<CPlayer*> winningPlayers;	//Vector of pointers to winning players
	int highestRoundWins = mpPlayers->GetHighestRoundWins();	//Get highest round wins from mPlayers vector

	//If at least one player won a round
	if (highestRoundWins > 0)
	{
		CPlayer* pCurrentPlayer = mpPlayers->GetFirst();	//Get first player in list

		//Loop through players
		while (pCurrentPlayer != nullptr)
		{
			//If player has highest round wins then
			//add to winningPlayers vector
			if (pCurrentPlayer->GetRoundWins() == highestRoundWins)
			{
				winningPlayers.push_back(pCurrentPlayer);
			}

			pCurrentPlayer = pCurrentPlayer->GetNextPlayer();	//Get next player in list
		}
	}

	DisplayWinners(winningPlayers);
}

//Create winning players message and output to console
void CGameManager::DisplayWinners(vector<CPlayer*> winningPlayers)
{
	string winningPlayersMessage = "";	//Winning players message for output
	vector<CPlayer*>::iterator winningPlayersIterator = winningPlayers.begin();	//Iterator for winningPlayers vector

	//Check number of winning players
	if (winningPlayers.size() > 1)
	{
		//Loop through winningPlayers vector
		for (auto player : winningPlayers)
		{
			player->AddWin(1);	//Add game win to player
			
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

		winningPlayersMessage += " win the game!";	//Add ending to output message
	}
	else if (winningPlayers.size() == 1)
	{
		(winningPlayers.front())->AddWin(1);	//Add game win to player
		
		//Create output message
		winningPlayersMessage += (winningPlayers.front())->GetName();
		winningPlayersMessage += " wins the game!";
	}
	else
	{
		winningPlayersMessage = "Nobody wins the game.";	//Create output message
	}

	cout << winningPlayersMessage << endl << endl;	//Output winning players message to console
}