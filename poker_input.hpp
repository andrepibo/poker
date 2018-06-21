#pragma once
#include <string>
#include <vector>
#include <cstdio>

#include "types.hpp"
#include "utils.hpp"

class PokerInput
{

public:	
	PokerInput(std::string _input) : input(_input), isInputValid(true)
	{			
		try
		{			
			parseInput();
		}
		catch(std::runtime_error e)
		{
			isInputValid = false;
			invalidReason = e.what();
		}
	}
	
	bool isValid()
	{
		return isInputValid;
	}

	void printReason()
	{
		std::cout << "Invalid reason: " << invalidReason << ". (input: " << input << ")" << std::endl;
	}


	std::vector<Card> hand, deck;	

private:
	std::string input;	
	bool isInputValid;
	std::string invalidReason;
	
	void parseInput()
	{		

		if(input.size() < 29)
		{
			isInputValid = false;
			invalidReason = "invalid size.";			
			return;
		}

		const char *str = input.c_str();
		for(int card = 0; card < 10; card++)
		{
			char face, suit;
			if(sscanf(str, "%c%c ", &face, &suit) != 2)
			{
				throw std::runtime_error("malformed input.");
			}

			str += 3;
			
			if(card < 5)			
				hand.push_back(Card(suit,face));			
			else
				deck.push_back(Card(suit,face));			
			
		}
	}
};
