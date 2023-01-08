//Author: Alex Reed

#pragma once

#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <memory>
using std::vector;
using std::default_random_engine;
using std::random_device;

class CDeck
{
private:
	vector<int> mDeck;	//Deck of cards vector
public:
	void CreateDeck();	//Create new deck of cards
	int DrawCard();	//Get card from deck
};