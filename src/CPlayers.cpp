//Author: Alex Reed

#include "CPlayers.h"

//Constructor
CPlayers::CPlayers(CDeck* pDeck)
{
	mpDeck = pDeck;	//Assign pointer to CDeck class
}

//Return highest player score
int CPlayers::GetHighestScore()
{
	return (*max_element(mPlayers.begin(), mPlayers.end(), [](auto& a, auto& b)
		{ return a->GetScore() < b->GetScore(); }))->GetScore();	//Get highest score from mPlayers vector
}

//Return highest player round wins
int CPlayers::GetHighestRoundWins()
{
	return (*max_element(mPlayers.begin(), mPlayers.end(), [](auto& a, auto& b)
		{ return a->GetRoundWins() < b->GetRoundWins(); }))->GetRoundWins();	//Get highest round wins from mPlayers vector
}

//Return highest player game wins
int CPlayers::GetHighestGameWins()
{
	return (*max_element(mPlayers.begin(), mPlayers.end(), [](auto& a, auto& b)
		{ return a->GetGameWins() < b->GetGameWins(); }))->GetGameWins();	//Get highest game wins from mPlayers vector
}

//Return pointer to first player in mPlayers vector
CPlayer* CPlayers::GetFirst()
{
	return mPlayers.front().get();
}

//Clear user input buffer and reset error flags
void CPlayers::ClearUserInput()
{
	cin.clear();	//Reset input error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Clear input buffer
}

//Ask for number of players and player names
//and then fill mPlayers vector
void CPlayers::CreatePlayers()
{
	int numPlayers = 0;

	//Ask how many players are in the game
	//Loop until chosen number is between 2 and 7
	while (numPlayers < 2 || numPlayers > 7)
	{
		//Output request to console
		cout << endl << "Between 2 and 7 players are allowed." << endl;
		cout << "How many people are playing? ";

		cin >> numPlayers;	//Get user input

		ClearUserInput();
	}

	cout << endl;

	//For each player, ask for name and create player
	for (int i = 1; i <= numPlayers; ++i)
	{
		string playerName = "";

		cout << "What is the name of player " << i << "? ";	//Output request to console

		cin >> playerName;	//Get user input

		NewPlayer(playerName);	//Create new player with user input name

		ClearUserInput();
	}
}

//Create new player object with input name
//and add to mPlayers vector
void CPlayers::NewPlayer(string name)
{
	auto pNewPlayer{ make_unique<CPlayer>(name, mpDeck) };	//Create new CPlayer object

	//If elements already exist
	if (mPlayers.size() > 0)
	{
		//For current last element in mPlayers, set pointer
		//to next player to new CPlayer pointer
		mPlayers.back().get()->SetNextPlayer(pNewPlayer.get());
	}

	mPlayers.push_back(move(pNewPlayer));	//Add new CPlayer object to mPlayers vector
}

//Reset players in mPlayers for new round
void CPlayers::ResetPlayersForRound()
{
	//Loop through players
	for (auto& pPlayer : mPlayers)
	{
		pPlayer->ResetForRound();	//Reset player for round
	}

	DealCards();
}

//Reset players in mPlayers for new game
void CPlayers::ResetPlayersForGame()
{
	//Loop through players
	for (auto& pPlayer : mPlayers)
	{
		pPlayer->ResetForGame();	//Reset player for round
	}
}

//For each player, get starting cards from deck
void CPlayers::DealCards()
{
	//Loop through players
	for (auto& pPlayer : mPlayers)
	{
		pPlayer->DealCards();	//Get starting cards
	}
}