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

#ifndef VIDEOPOKER_DECK_H
#define VIDEOPOKER_DECK_H
#include <ctime>
#include <cstdlib>

#define V_ACE 14
#define V_KING 13
#define V_QUEEN 12
#define V_JACK 11
#define NUM_VALUES 13

#define S_CLUBS 1
#define S_DIAMONDS 2
#define S_SPADES 3
#define S_HEARTS 4
#define NUM_SUITS 4


typedef struct card
{
    int value;
    int suit;
    int order; // order in a normal deck of cards.
} Card;

typedef struct card_node
{
    Card* card;
    struct card_node* prev;
    struct card_node* next;
} CardNode;

typedef struct linked_card_list
{
    CardNode* head;
    int N;
} LinkedCardList;

// pop index-th card node from list
CardNode* PopCardNode(LinkedCardList* list, int index);
// insert card node to list as index-th node
void InsertCardNode(LinkedCardList* list, int index, CardNode* newNode);
//void PreppendCardNode(LinkedCardList* list, CardNode* newNode);
Card* CreateCard(int, int);

LinkedCardList* CreateOrderedDeck();

// shuffle cards in discardDeck and save into drawDeck
LinkedCardList* ShuffleDeck(LinkedCardList* discardDeck, LinkedCardList* drawDeck);

CardNode* DrawCard(LinkedCardList* drawDeck, LinkedCardList* discardDeck);

int FindCardIndex(LinkedCardList* list, int value, int suit);

void freeDeck(LinkedCardList* deck);

#endif //VIDEOPOKER_DECK_H
