//Author: Alex Reed

#include "CTournamentManager.h"

//Constructor
CTournamentManager::CTournamentManager()
{
	mNumGames = 0;	//Initialise total number of games played
	mpDeck = make_unique<CDeck>();	//Create pointer to CDeck class
	mpPlayers = make_unique<CPlayers>(mpDeck.get());	//Create pointer to CPlayers class
	mpGame = make_unique<CGameManager>(mpDeck.get(), mpPlayers.get());	//Create new pointer to CGameManager

	DisplayTitle();
	mpPlayers->CreatePlayers();
	PlayTournament();
}

//Clear user input buffer and reset error flags
void CTournamentManager::ClearUserInput()
{
	cin.clear();	//Reset input error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Clear input buffer
}

//Loop through vector of titles and output
//each to the console
void CTournamentManager::DisplayTitle()
{
	vector<string> titles = { "Welcome to", "- B L A C K J A C K -" };	//Add titles to vector
	int maxTitleLength = max_element(titles.begin(), titles.end(), [](const auto& a, const auto& b)
		{ return a.length() < b.length(); })->length();	//Get length of longest title from titles vector

	//Display each title in the titles vector
	for (auto title : titles)
	{
		int padding = (maxTitleLength - title.length()) / 2;	//Calculate the padding

		//Output padding to console
		for (int i = 0; i < padding; ++i)
		{
			cout << " ";
		}

		cout << title << endl;	//Output title to console
	}
}

//Play game and then repeat until stopped
void CTournamentManager::PlayTournament()
{
	char userInput = 'y';

	while (userInput == 'y')
	{
		mpGame->PlayGame();

		mNumGames++;	//Increment total number of games played

		//Output request to console
		cout << "==========" << endl << endl << "Would you like to play again? Press y for yes or any other key to finish." << endl;

		userInput = cin.get();	//Get user input

		ClearUserInput();
	}

	if (mNumGames > 1)	//If more than one game has been played then end tournament
	{
		EndTournament();
	}
}

//Calculate winner(s) of tournament and output to console
void CTournamentManager::EndTournament()
{
	cout << "==========" << endl << endl << "TOURNAMENT OVER" << endl;	//Output message to console

	vector<CPlayer*> winningPlayers;	//Vector of pointers to winning players
	int highestGameWins = mpPlayers->GetHighestGameWins();	//Get highest player game wins

	//If at least one player won a game
	if (highestGameWins > 0)
	{
		CPlayer* pCurrentPlayer = mpPlayers->GetFirst();	//Get first player in list

		//Loop through players
		while (pCurrentPlayer != nullptr)
		{
			//If player has highest game wins then
			//add to winningPlayers vector
			if (pCurrentPlayer->GetGameWins() == highestGameWins)
			{
				winningPlayers.push_back(pCurrentPlayer);
			}

			pCurrentPlayer = pCurrentPlayer->GetNextPlayer();	//Get next player in list
		}
	}

	DisplayWinners(winningPlayers);
}

//Create winning players message and output to console
void CTournamentManager::DisplayWinners(vector<CPlayer*> winningPlayers)
{
	string winningPlayersMessage = "";	//Winning players message for output
	vector<CPlayer*>::iterator winningPlayersIterator = winningPlayers.begin();	//Iterator for winningPlayers vector

	//Check number of winning players
	if (winningPlayers.size() > 1)
	{
		//Loop through winningPlayers vector
		for (auto player : winningPlayers)
		{
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

		winningPlayersMessage += " win the tournament!";	//Add ending to output message
	}
	else if (winningPlayers.size() == 1)
	{
		//Create output message
		winningPlayersMessage += (winningPlayers.front())->GetName();
		winningPlayersMessage += " wins the tournament!";
	}
	else
	{
	winningPlayersMessage = "Nobody wins the tournament.";	//Create output message
	}

	cout << winningPlayersMessage << endl << endl;	//Output winning players message to console
}