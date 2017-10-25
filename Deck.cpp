// Project name: GAME-230-Project#3- Video Poker
// Author: Bingnan Li, Nathan
// Created Date: 10/19/2017
//Last Modified Date: 10/24/2017

#include "Deck.h"

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

LinkedCardList* CreateOrderedDeck()
{
	LinkedCardList* orderedDeck;
	orderedDeck = (LinkedCardList*)malloc(sizeof(LinkedCardList));
	orderedDeck->head = NULL;
	int n = 0;
	CardNode* curNode = NULL;
	for (int s = S_CLUBS; s <= S_HEARTS; s++)
	{
		for (int v = 2; v <= V_ACE; v++)
		{
			Card* card = CreateCard(v, s);
			CardNode* cardNode;
			cardNode = (CardNode*)malloc(sizeof(CardNode));
			cardNode->card = card;
			cardNode->prev = NULL;
			cardNode->next = NULL;

			if (curNode != NULL)
			{
				curNode->next = cardNode;
				cardNode->prev = curNode;
			}

			if (orderedDeck->head == NULL)
			{
				orderedDeck->head = cardNode;
			}
			curNode = cardNode;
			n++;
		}
	}
	orderedDeck->N = n;
	return orderedDeck;
}

Card* CreateCard(int v, int s)
{
	Card* card;
	card = (Card*)malloc(sizeof(Card));
	card->suit = s;
	card->value = v;
	card->order = (s - 1) * 13 + v - 2;
	return card;
}

LinkedCardList* ShuffleDeck(LinkedCardList* discardDeck, LinkedCardList* drawDeck)
{
	if (drawDeck == NULL)
	{
		drawDeck = (LinkedCardList*)malloc(sizeof(LinkedCardList));
		drawDeck->head = NULL;
		drawDeck->N = 0;
	}
	while (discardDeck->N != 0)
	{
		int idx = rand() % discardDeck->N;
		CardNode* cardNode = PopCardNode(discardDeck, idx);
		InsertCardNode(drawDeck, 0, cardNode);
	}

	return drawDeck;
}

CardNode* PopCardNode(LinkedCardList* list, int index)
{
	CardNode* node = list->head;
	for (int i = 0; i < index; i++)
	{
		node = node->next;
	}
	if (node->prev != NULL)
	{
		node->prev->next = node->next;
	}
	if (node->next != NULL)
	{
		node->next->prev = node->prev;
	}

	if (list->head == node)
	{
		list->head = node->next;
	}

	node->prev = node->next = NULL;
	list->N--;
	return node;
}

void InsertCardNode(LinkedCardList* list, int index, CardNode* newNode)
{
	CardNode* node = list->head;
	CardNode* last = NULL;
	for (int i = 0; i < index; i++)
	{
		last = node;
		node = node->next;
	} // get the index-th node (going to be index+1-th
	if (node == NULL)
	{ //
		if (list->head == NULL)
		{
			list->head = newNode;
		}
		else
		{
			last->next = newNode;
			newNode->prev = last;
		}
	}
	else
	{
		CardNode* precedeNode = node->prev;
		node->prev = newNode;
		newNode->next = node;
		if (precedeNode != NULL)
		{
			precedeNode->next = newNode;
			newNode->prev = precedeNode;
		}
		else
		{
			list->head = newNode;
		}
	}
	list->N++;
}

CardNode* DrawCard(LinkedCardList* drawDeck, LinkedCardList* discardDeck)
{
	CardNode* cardNode = PopCardNode(drawDeck, 0);
	if (drawDeck->N == 0)
	{
		ShuffleDeck(discardDeck, drawDeck);
	}
	return cardNode;
}

int FindCardIndex(LinkedCardList* list, int value, int suit)
{
	CardNode* node = list->head;
	int idx = -1;
	while (node != NULL)
	{
		idx++;
		if (node->card->value == value && node->card->suit == suit)
		{
			return idx;
		}
		node = node->next;
	}
	return -1;
}

void freeDeck(LinkedCardList* deck) 
{
	CardNode* node = deck->head;
	CardNode* temp;
	while (node != NULL) {
		free(node->card);
		node->card = NULL;
		temp = node->next;
		free(node);
		node = temp;
	}
	free(deck);
}