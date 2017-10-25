//Project name: GAME-230-Project#3- Video Poker
//Author: Bingnan Li, Nathan				  
//Created Date: 10/19/2017	
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

#ifndef VIDEOPOKER_HANDCHECKER_H
#define VIDEOPOKER_HANDCHECKER_H
#include "Deck.h"
#include <iostream>
#define R_ROYALFLUSH 800
#define R_STAIGHTFLUSH 50
#define R_FOUROFAKIND 25
#define R_FULLHOUSE 9
#define R_FLUSH 6
#define R_STRAIGHT 4
#define R_THREEOFAKIND 3
#define R_TWOPAIR 2
#define R_ONEPAIR 1
using namespace std;

int CheckerCheck(LinkedCardList* handPokerList);

bool CheckerOnePair(LinkedCardList* handPokerList);

bool CheckerTwoPair(LinkedCardList* handPokerList);

bool CheckerThreeOfAKind(LinkedCardList* handPokerList);

bool CheckerStraight(LinkedCardList* handPokerList);

bool CheckerFlush(LinkedCardList* handPokerList);

bool CheckerFullHouse(LinkedCardList* handPokerList);

bool CheckerFourOfAkind(LinkedCardList* handPokerList);

bool CheckerStraightFlush(LinkedCardList* handPokerList);

bool CheckerRoyalFlush(LinkedCardList* handPokerList);


void SortList(LinkedCardList* list);


#endif
