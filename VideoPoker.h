// Project name: GAME-230-Project#3- Video Poker
// Author: Bingnan Li, Nathan
// Created Date: 10/19/2017
//Last Modified Date: 10/24/2017

#define _CRTDBG_MAP_ALLOC
#define _CRTDBG_MAP_ALLOC_NEW
#include <cstdlib>
#include <crtdbg.h>
#ifdef _DEBUG
#ifndef DBG_NEW
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#define new DBG_NEW
#endif
#endif

#ifndef VIDEOPOKER_VIDEOPOKER_H
#define VIDEOPOKER_VIDEOPOKER_H

#include "Deck.h"
#include "HandChecker.h"
#include <string>
#include <iostream>

#define C_KEEP 1
#define C_NONE 2
#define C_ALL 3
#define C_EXIT 4
#define C_SWAP 5
#define C_AGAIN 6
#define C_DECK 7


using namespace std;

int money;

LinkedCardList* drawDeck;
LinkedCardList* discardDeck;
LinkedCardList* playersHand;

void initGame();

void printOrderedDeck(LinkedCardList* deck);

// return description of card in sting.
string getCardDesc(Card*);

void newRound();
void drawFiveToHand();
void printPlayersHand(int keepCount);
void printPrompt();
int getPlayerChoice(bool* toDiscard);
int discardAndDraw(bool* toDiscard);
void doSwap(LinkedCardList* hand, LinkedCardList* drawDeck);
void DiscardInHand();
void freeGameDecks();

#endif //VIDEOPOKER_VIDEOPOKER_H
