// Project name: GAME-230-Project#3- Video Poker
// Author: Bingnan Li, Nathan
// Created Date: 10/19/2017
//Last Modified Date: 10/24/2017

#include "HandChecker.h"

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

//Check hand pokers and return a reward.(If matched)
int CheckerCheck(LinkedCardList* handPokerList)
{
	if (CheckerRoyalFlush(handPokerList))
	{
		cout << "ROYAL FLUSH!" << endl;
		return R_ROYALFLUSH;
	}

    if(CheckerStraightFlush(handPokerList))
    {
        cout << "Straight flush!" << endl;
        return R_STAIGHTFLUSH;
    }

	if (CheckerFourOfAkind(handPokerList))
	{
		cout << "Four a kind!" << endl;
		return R_FOUROFAKIND;
	}
	
	if (CheckerFullHouse(handPokerList))
	{
		cout << "Full house!" << endl;
		return R_FULLHOUSE;
	}

	if (CheckerFlush(handPokerList))
	{
		cout << "FLUSH!" << endl;
		return R_FLUSH;
	}
	if (CheckerStraight(handPokerList))
	{
		cout << "Straight!" << endl;
		return R_STRAIGHT;
	}

	if (CheckerThreeOfAKind(handPokerList))
	{
		cout << "Three of a kind!" << endl;
		return R_THREEOFAKIND;
	}

	if (CheckerTwoPair(handPokerList))
	{
		cout << "Two pairs!" << endl;
		return R_TWOPAIR;
	}

	if (CheckerOnePair(handPokerList))
	{
		cout << "One pair!" << endl;
		return R_ONEPAIR;
	}

	cout << "No Poker hand scored. :(" << endl;
	return 0;
}

bool CheckerRoyalFlush(LinkedCardList* handPokerList)
{
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	if (node->card->value != 10)
		return false;

	int lastSuit = node->card->suit;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->suit != lastSuit || node->card->value != (lastValue + 1))
			return false;
		lastValue = node->card->value;
		lastSuit = node->card->suit;
		node = node->next;
	}
	return true;
}

bool CheckerStraightFlush(LinkedCardList* handPokerList)
{
    SortList(handPokerList);
    CardNode* node = handPokerList->head;

    int lastSuit = node->card->suit;
    int lastValue = node->card->value;
    node = node->next;
    while (node != NULL)
    {
        if (node->card->suit != lastSuit || node->card->value != (lastValue + 1))
            return false;
        lastValue = node->card->value;
        lastSuit = node->card->suit;
        node = node->next;
    }
    return true;
}

bool CheckerFourOfAkind(LinkedCardList* handPokerList)
{
	int counter = 1;
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->value == lastValue)
			counter += 1;
		else
			counter = 1;

		if (counter == 4)
			return true;

		lastValue = node->card->value;
		node = node->next;
	}
		return false;
}

bool CheckerFullHouse(LinkedCardList* handPokerList)
{
	int counterThree = 1;
	int counterTwo = 1;
	bool swapCounter = false;
	int index = 1;
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (index < 2)
		{
			if (node->card->value == lastValue)
			{
				counterThree += 1;
			}
		}
		if (index == 2)
		{
			if (node->card->value == lastValue)
			{
				counterThree += 1;
			}
			else
			{
				counterTwo = counterThree;
				counterThree = 1;
				swapCounter = true;
			}
		}
		if (index > 2)
		{
			if (swapCounter == true)
			{
				if (node->card->value == lastValue)
				{
					counterThree += 1;
				}
			}
			else
			{
				if (node->card->value == lastValue)
				{
					counterTwo += 1;
				}
			}
		}
		index++;
		lastValue = node->card->value;
		node = node->next;
	}
	if (counterThree == 3 && counterTwo == 2)
		return true;
	else
		return false;
}

bool CheckerStraight(LinkedCardList* handPokerList)
{
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->value != (lastValue + 1))
			return false;
		lastValue = node->card->value;
		node = node->next;
	}
	return true;
}

bool CheckerFlush(LinkedCardList* handPokerList)
{
	CardNode* node = handPokerList->head;
	int lastSuit = node->card->suit;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->suit != lastSuit)
			return false;
		lastSuit = node->card->suit;
		node = node->next;
	}
	return true;
}

bool CheckerThreeOfAKind(LinkedCardList* handPokerList)
{
	int counter = 1;
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->value == lastValue)
			counter += 1;
		else
			counter = 1;

		if (counter == 3)
			return true;

		lastValue = node->card->value;
		node = node->next;
	}
		return false;
}

bool CheckerTwoPair(LinkedCardList* handPokerList)
{
	int counterPair1 = 1;
	int counterPair2 = 1;
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (counterPair1 < 2)
		{
			if (node->card->value == lastValue)
			{
				counterPair1 += 1;
			}
			else
			{
				counterPair1 = 1;
			}
		}
		else
		{
			if (node->card->value == lastValue)
			{
				counterPair2 += 1;
			}
			else
			{
				counterPair2 = 1;
			}
		}
		lastValue = node->card->value;
		node = node->next;
	}
	if (counterPair1 == 2 && counterPair2 == 2)
		return true;
	else
		return false;
}

bool CheckerOnePair(LinkedCardList* handPokerList)
{
	bool jackOrBetter = false;
	SortList(handPokerList);
	CardNode* node = handPokerList->head;
	int lastValue = node->card->value;
	node = node->next;
	while (node != NULL)
	{
		if (node->card->value > 10)
		{
			if (node->card->value == lastValue)
				return true;
		}

		lastValue = node->card->value;
		node = node->next;
	}
		return false;
}

void SortList(LinkedCardList* list)
{
	CardNode* node_i = list->head;
	int idx = -1;
	while (node_i != NULL)
	{
		idx++;
		CardNode* minNode = node_i;
		CardNode* node_j = node_i->next;
		while (node_j != NULL)
		{
			if (node_j->card->value < minNode->card->value)
			{
				minNode = node_j;
			}
			node_j = node_j->next;
		}
		// swap card
		int t_value, t_suit, t_order;
		t_value = node_i->card->value;
		t_suit = node_i->card->suit;
		t_order = node_i->card->order;
		node_i->card->value = minNode->card->value;
		node_i->card->suit = minNode->card->suit;
		node_i->card->order = minNode->card->order;
		minNode->card->value = t_value;
		minNode->card->suit = t_suit;
		minNode->card->order = t_order;
		node_i = node_i->next;
	}
}