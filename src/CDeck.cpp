//Author: Alex Reed

#include "CDeck.h"

//For each card in deck, add element to mDeck vector
//and then shuffle mDeck vector
void CDeck::CreateDeck()
{
	mDeck.clear();	//Clear mDeck vector

	int numSuits = 4;
	int cardsPerSuit = 13;

	//Loop through suits
	for (int i = 0; i < numSuits; ++i)
	{
		//Loop through cards in each suit
		for (int j = 1; j <= cardsPerSuit; ++j)
		{
			mDeck.push_back(j);	//Add card number to mDeck vector
		}
	}

	//Shuffle mDeck vector
	shuffle(mDeck.begin(), mDeck.end(), default_random_engine{ random_device{}() });
}

//Get last element from mDeck vector then remove it
int CDeck::DrawCard()
{
	int card = mDeck.back();	//Get last element from mDeck vector
	mDeck.pop_back();	//Delete last element from mDeck vector

	return card;
}