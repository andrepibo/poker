#pragma once

#include "poker_input.hpp"
#include "poker_output.hpp"
#include "evaluators.hpp"
#include "types.hpp"

#include <vector>
#include <functional>
#include <algorithm>
#include <tuple>

	
class Solver
{
public:
	Solver(PokerInput _input) : input(_input), bestHand(HandValue::None) 
	{
		evaluators = {  IsStraightFlush,
						IsFourOfAKind,
						IsFullHouse,
						IsFlush,
						IsStraight,
						IsThreeOfAKind,
						IsTwoPair,
						IsPair,
						IsHighestCard};
	}

	PokerOutput solve() 
	{
		std::vector<bool> selectedCards(5, false);
		ProcessCombination(selectedCards);
		
		for(int firstNode = 0; firstNode < 5; firstNode++)
			GenerateCombinations(selectedCards, firstNode);

		return PokerOutput(input, bestHand);
	}	

private:
	PokerInput input;
	HandValue bestHand;
	std::vector<std::function<HandValue(const std::vector<Card>&)>> evaluators;	

	//DFS-style 
	void GenerateCombinations(std::vector<bool>& selectedCards, int node)
	{
		selectedCards[node] = true;
				
		ProcessCombination(selectedCards);

		for(int next = node + 1; next < 5; next++)
		{
			GenerateCombinations(selectedCards, next);
		}

		selectedCards[node] = false;
	}

	void ProcessCombination(const std::vector<bool>& selectedCards)
	{
		auto cards = GenerateHand(selectedCards);
		auto bestHandValuation = EvaluateCardCombination(cards);

		if(bestHandValuation < bestHand)
			bestHand = bestHandValuation;
	}

	std::vector<Card> GenerateHand(const std::vector<bool>& selectedCards) const
	{
		std::vector<Card> cardsToBeEvaluated;

		//From player's hand
		for(int i=0; i<5; i++)
		{
			if(selectedCards[i])
				cardsToBeEvaluated.push_back(input.hand[i]);			
		}

		//From deck
		int i =0;
		while(cardsToBeEvaluated.size() < 5)
		{
			cardsToBeEvaluated.push_back(input.deck[i]);
			i++;
		}

		std::sort(begin(cardsToBeEvaluated), end(cardsToBeEvaluated), [](const Card& l, const Card& r){ return std::tie(l.faceValue, l.suit) < std::tie(r.faceValue, r.suit); });
		return cardsToBeEvaluated;
	}

	HandValue EvaluateCardCombination(const std::vector<Card>& cards) const
	{
		for(auto evaluator : evaluators)
		{
			auto result = evaluator(cards);
			if(result != HandValue::None)			
				return result;		
		}
	}

};