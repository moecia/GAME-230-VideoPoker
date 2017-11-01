// Project name: GAME-230-Project#3- Video Poker
// Author: Bingnan Li, Nathan
// Created Date: 10/19/2017
//Last Modified Date: 10/24/2017

#include "VideoPoker.h"
#include <cstdio>

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

using namespace std;

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF |
		_CRTDBG_LEAK_CHECK_DF);

	srand(time(NULL));
	initGame();
	//    printOrderedDeck(drawDeck);
	cout << "Welcome to Video Poker!" << endl;
	cout << "You have started with $" << to_string(money) << endl;
	while (money > 0)
	{
		newRound();
	}
	// When money runs out, print game over.
	freeGameDecks();
	cout << "GAME OVER!" << endl;
	system("PAUSE");
	return 0;
}

void newRound()
{
	money--;
	cout << "You pay $1 ante and now have $" << to_string(money) << endl << endl;
	drawFiveToHand();
	bool askAgain;
	bool toDiscard[5];
	do
	{
		askAgain = false;
		printPlayersHand(0);
		printPrompt();
		for (int i = 0; i < 5; i++)
			toDiscard[i] = true; // assume all is going to be discarded.
		switch (getPlayerChoice(toDiscard))
		{

		case C_EXIT:
			freeGameDecks();
			exit(1);
			break;
		case C_DECK:
			printOrderedDeck(drawDeck);
			askAgain = true;
			break;
		case C_SWAP:
			doSwap(playersHand, drawDeck);
			askAgain = true;
			break;
		case C_AGAIN:
			askAgain = true;
			break;
		case C_KEEP:
		case C_NONE:
		case C_ALL:
			// nothing need to be done here.
			break;
		default:
			askAgain = true;
		}
	} while (askAgain);
	int discardCount = discardAndDraw(toDiscard);
	printPlayersHand(5 - discardCount);

	// Check the hand poker
	int reward = CheckerCheck(playersHand);
	cout << "You earned $" << reward << "!" << endl;
	money += reward;
	cout << "You now have $" << money << "!" << endl;
	// Discard cards in hand.
	DiscardInHand();
	// go to next turn.
	cout << endl;
	cout << "Press enter to play another round...";
	string temp;
	getline(cin, temp);
	cout << "------------------------------------------" << endl;
}

void DiscardInHand()
{
	CardNode* node;
	while (playersHand->N > 0)
	{
		node = PopCardNode(playersHand, 0);
		InsertCardNode(discardDeck, 0, node);
	}
}

int discardAndDraw(bool* toDiscard)
{
	int discardCount = 0;
	for (int i = 4; i >= 0; i--)
	{
		if (toDiscard[i])
		{
			CardNode* popped = PopCardNode(playersHand, i);
			InsertCardNode(discardDeck, 0, popped);
			discardCount++;
		}
	}
	for (int i = 0; i < discardCount; i++)
	{
		CardNode* newCard = DrawCard(drawDeck, discardDeck);
		InsertCardNode(playersHand, 5 - discardCount, newCard);
	}
	cout << endl
		<< "You kept " << 5 - discardCount << " and drew " << discardCount << " cards." << endl;
	return discardCount;
}

void doSwap(LinkedCardList* hand, LinkedCardList* drawDeck)
{
	cout << "Enter the letter of the card in hand: ";
	string input;
	while (input.empty())
		getline(cin, input);

	// get hand card input (hand_idx)
	int idx = -1;
	for (int i = 0; i < input.size(); i++)
	{
		char c = (char)tolower(input[i]);
		if (c == ' ')
			continue;
		if (!(c >= 'a' && c <= 'e'))
		{
			cout << "Invalid hand card input." << endl << endl;
			return;
		}
		int potential = c - 'a';
		if (idx != -1 && potential != idx)
		{ // input 'ab'
			cout << "Invalid hand card input." << endl << endl;
			return;
		}
		idx = potential;
	}

	// Enter the value of the card in the deck to swap with:
	int value;
	input = "";
	cout << "Enter the value of the card in the deck to swap with: ";
	while (input.empty())
		getline(cin, input);
	if (input == "Jack" || input == "jack" || input == "j" || input == "J")
	{
		value = V_JACK;
	}
	else if (input == "Queen" || input == "queen" || input == "q" || input == "Q")
	{
		value = V_QUEEN;
	}
	else if (input == "King" || input == "king" || input == "k" || input == "K")
	{
		value = V_KING;
	}
	else if (input == "Ace" || input == "ace" || input == "a" || input == "A")
	{
		value = V_ACE;
	}
	else
	{
		int temp;
		try
		{
			temp = std::stoi(input);
		}
		catch (int e)
		{
			cout << "Invalid card value." << endl << endl;
			return;
		}
		value = temp;
	}
	if (value < 2 || value > V_ACE)
	{
		cout << "Invalid card value." << endl << endl;
		return;
	}

	int suit;
	input = "";
	cout << "Enter the suit (c,d,h,s) of the card in the deck to swap with:";
	while (input.empty())
		getline(cin, input);
	if (input == "c")
	{
		suit = S_CLUBS;
	}
	else if (input == "d")
	{
		suit = S_DIAMONDS;
	}
	else if (input == "h")
	{
		suit = S_HEARTS;
	}
	else if (input == "s")
	{
		suit = S_SPADES;
	}
	else
	{
		cout << "Invalid card suit." << endl << endl;
		return;
	}

	int idxInDrawDeck = FindCardIndex(drawDeck, value, suit);
	if (idxInDrawDeck == -1)
	{
		cout << "Invalid deck card." << endl << endl;
		return;
	}

	// do the swapping
	CardNode* toReplace = PopCardNode(playersHand, idx);
	CardNode* temp = PopCardNode(drawDeck, idxInDrawDeck);
	InsertCardNode(drawDeck, idxInDrawDeck, toReplace);
	InsertCardNode(playersHand, idx, temp);

	cout << "Swapped " << getCardDesc(toReplace->card) << " with " << getCardDesc(temp->card) << "."
		<< endl
		<< endl;
	return;
}

int getPlayerChoice(bool* toDiscard)
{
	string input;
	while (input.empty())
		getline(cin, input);

	if (input == "none")
	{
		return C_NONE;
	}
	else if (input == "all")
	{
		for (int i = 0; i < 5; i++)
			toDiscard[i] = false;
		return C_ALL;
	}
	else if (input == "exit")
	{
		return C_EXIT;
	}
	else if (input == "swap")
	{
		return C_SWAP;
	}
	else if (input == "deck")
	{
		return C_DECK;
	}
	else
	{
		for (int i = 0; i < input.size(); i++)
		{
			char c = (char)tolower(input[i]);
			if (!(c >= 'a' && c <= 'e'))
			{
				cout << "Sorry, I didn't understand, please try again.." << endl << endl;
				return C_AGAIN;
			}
			toDiscard[c - 'a'] = false;
		}
		return C_KEEP;
	}
}

void printPrompt()
{
	// print deck info
	cout << "The deck contains " << to_string(drawDeck->N) << " cards." << endl << endl;
	cout << "OPTIONS..." << endl;
	cout << "- Type the letters for the cards you wish to keep. (i.e., \"acd\")" << endl;
	cout << "- Type \"deck\" to view the cards remaining in the deck." << endl;
	cout << "- Type \"none\" to discard all cards in your hand." << endl;
	cout << "- Type \"all\" to keep all cards in your hand." << endl;
	cout << "- Type \"exit\" to exit the game." << endl;
	cout << "- Type \"swap\" to CHEAT and swap a card in your hand with one in the deck." << endl;
	cout << "YOUR CHOICE: ";
}

void printPlayersHand(int keepCount)
{
	cout << "Your hand contains:" << endl;
	char cID = 'A'; // card ID in hand i.e. 'A', 'B'...
	CardNode* node = playersHand->head;
	while (node != NULL)
	{
		cout << cID << ": " << getCardDesc(node->card);
		if (keepCount-- > 0)
			cout << " (kept)";
		cout << endl;
		node = node->next;
		cID += 1;
	}
	cout << endl;
}

void drawFiveToHand()
{
	while (playersHand->N < 5)
	{
		CardNode* cardNode = DrawCard(drawDeck, discardDeck);
		InsertCardNode(playersHand, 0, cardNode);
	}
}

void initGame()
{
	money = 10;
	discardDeck = CreateOrderedDeck();
	drawDeck = ShuffleDeck(discardDeck, drawDeck);
	playersHand = (LinkedCardList*)malloc(sizeof(LinkedCardList));
	playersHand->head = NULL;
	playersHand->N = 0;
}

void printOrderedDeck(LinkedCardList* deck)
{
	CardNode* cards_available[NUM_SUITS * NUM_VALUES] = { NULL };
	CardNode* node = deck->head;
	while (node != NULL)
	{
		cards_available[node->card->order] = node;
		node = node->next;
	}
	printf("\n");
	bool printedFirst = false;
	for (int i = 0; i < NUM_SUITS * NUM_VALUES; i++)
	{
		node = cards_available[i];
		if (node == NULL)
			continue;
		string cardDesc = getCardDesc(node->card);
		if (printedFirst)
		{
			printf(", %s", cardDesc.c_str());
		}
		else
		{
			printf("%s", cardDesc.c_str());
			printedFirst = true;
		}
	}
	printf("\n\n");
}

string getCardDesc(Card* c)
{
	string v_str = "NoneValue";
	if (c->value >= 2 && c->value <= 10)
	{
		v_str = to_string(c->value);
	}
	else
	{
		if (c->value == V_JACK)
			v_str = "Jack";
		else if (c->value == V_QUEEN)
			v_str = "Queen";
		else if (c->value == V_KING)
			v_str = "King";
		else if (c->value == V_ACE)
			v_str = "Ace";
	}
	string s_str = "NoneSuit";
	if (c->suit == S_CLUBS)
		s_str = "Clubs";
	else if (c->suit == S_DIAMONDS)
		s_str = "Diamonds";
	else if (c->suit == S_SPADES)
		s_str = "Spades";
	else if (c->suit == S_HEARTS)
		s_str = "Hearts";

	return v_str + " of " + s_str;
}

void freeGameDecks() 
{
	freeDeck(drawDeck);
	freeDeck(discardDeck);
	freeDeck(playersHand);
}