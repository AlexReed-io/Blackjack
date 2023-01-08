//Author: Alex Reed

#include "CPlayer.h"
#include "CGameManager.h"

//Constructor
CPlayer::CPlayer(string name, CDeck* pDeck)
{
	mName = name;	//Initialise name to input name
	mScore = 0;	//Initialise score
	mRoundWins = 0;	//Initialise number of round wins
	mGameWins = 0;	//Initialise number of game wins
	mAceInHand = false;	//Initialise flag to show if player has an Ace in hand
	mAceHigh = false;	//Initialise flag to show if Ace value changed to 11
	mBust = false;	//Initialise bust flag
	mStand = false;	//Initialise stand flag

	mpNextPlayer = nullptr;	//Initialise pointer to next player
	mpDeck = pDeck;	//Assign pointer to CDeck class
}

//Return player's name
string CPlayer::GetName()
{
	return mName;
}

//Return player's score
int CPlayer::GetScore()
{
	return mScore;
}

//Return player's number of round wins
int CPlayer::GetRoundWins()
{
	return mRoundWins;
}

//Return player's number of game wins
int CPlayer::GetGameWins()
{
	return mGameWins;
}

//Return flag for if player is bust
bool CPlayer::GetBust()
{
	return mBust;
}

//Return pointer to next player in list
CPlayer* CPlayer::GetNextPlayer()
{
	return mpNextPlayer;
}

//Clear user input buffer and reset error flags
void CPlayer::ClearUserInput()
{
	cin.clear();	//Reset input error flags
	cin.ignore(numeric_limits<streamsize>::max(), '\n');	//Clear input buffer
}

//Calculate player's score
void CPlayer::AddToScore(int card)
{
	//Check if card is face card and add to score accordingly
	if (card > 10)
	{
		mScore += 10;
	}
	else
	{
		mScore += card;
	}

	//If score is above 21, an Ace has been changed to 11, and
	//changing Ace back to 1 would bring score below 21 then
	//take 10 off score
	if ((mScore > 21) && mAceHigh && ((mScore - 10) <= 21))
	{
		mScore -= 10;
		mAceHigh = false;
	}

	//If score is over 21, change flag and remove score
	if (mScore > 21)
	{
		mBust = true;
	}
	else
	{
		//If card is Ace, change flag
		if (card == 1)
		{
			mAceInHand = true;
		}

		//If player has Ace and score plus 10 is less than 21
		//then add 10 to score
		if (mAceInHand && ((mScore + 10) <= 21))
		{
			mScore += 10;
			mAceHigh = true;
		}
	}
}

//Set pointer to next player
void CPlayer::SetNextPlayer(CPlayer* pNextPlayer)
{
	mpNextPlayer = pNextPlayer;
}

//Get starting cards from deck
void CPlayer::DealCards()
{
	int cardsToDeal = 2;	//Set number of cards to be dealt

	//Loop up to number of cards to deal
	for (int i = 0; i < cardsToDeal; ++i)
	{
		PickUpCard(mpDeck->DrawCard());	//Draw card from deck and give to player
	}
}

//Display player's hand and ask user if they
//want to pick up more cards
void CPlayer::TakePlayerTurn(CDeck* pDeck)
{
	DisplayHand();

	//Loop unless player becomes bust or wants to stand
	while (!mBust && !mStand)
	{
		cout << "Press 'h' to hit (draw another card) or any other key to stand (stop drawing cards)." << endl;	//Output request to console

		//Check if user input is 'h' or not
		if (cin.get() == 'h')
		{
			cout << endl;

			Hit(pDeck);
		}
		else
		{
			Stand();
		}

		ClearUserInput();
	}

	cout << endl;
}

//Give player another card
void CPlayer::Hit(CDeck* pDeck)
{
	PickUpCard(pDeck->DrawCard());	//Draw card from deck and give to player

	DisplayHand();
}

//Change stand flag to true
void CPlayer::Stand()
{
	mStand = true;
}

//Add input card to mHand vector and
//add card value to score
void CPlayer::PickUpCard(int card)
{
	mHand.push_back(card);
	AddToScore(card);
}

//Output bust message or player's hand to console
void CPlayer::DisplayHand()
{
	cout << mName << " has ";	//Output player's name to console

	const string cards[13] = { "A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K" };	//Card names

	//Loop through deck
	for (auto card : mHand)
	{
		cout << cards[card - 1] << " ";	//Output card name to console
	}

	cout << "(score: " << mScore << ")" << endl;	//Output score to console
	
	//If player is bust, output message to console and clear score
	if (mBust)
	{
		cout << mName << " is bust." << endl << endl;
		mScore = 0;
	}
}

//Clear player's hand and reset variables for new round
void CPlayer::ResetForRound()
{
	mHand.clear();
	mScore = 0;
	mAceInHand = false;
	mAceHigh = false;
	mBust = false;
	mStand = false;
}

//Reset player for round and reset round wins
void CPlayer::ResetForGame()
{
	ResetForRound();
	mRoundWins = 0;
}

//Depending on input type, increment player's
//number of round or game wins
void CPlayer::AddWin(int type)
{
	if (type == 0)
	{
		mRoundWins++;
	}
	else if (type == 1)
	{
		mGameWins++;
	}
}