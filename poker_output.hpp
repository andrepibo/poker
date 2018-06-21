#pragma once
#include "poker_input.hpp"
#include "utils.hpp"
#include <iostream>

class PokerOutput
{
public:	

	PokerOutput(PokerInput _input, HandValue _bestHand) : input(_input), bestHand(_bestHand)
	{}

	void print()
	{
		std::cout << "Hand: ";
		for(auto card: input.hand)
			std::cout << card << " ";

		std::cout << "Deck: ";
		for(auto card: input.deck)
			std::cout << card << " ";

		std::cout << "Best hand: " << bestHand << "  " << std::endl;
	}
private: 
	PokerInput input;
	HandValue bestHand;	
};