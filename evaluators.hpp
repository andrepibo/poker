#pragma once

#include "utils.hpp"
#include "types.hpp"

#include <vector>


HandValue IsFlush(const std::vector<Card>& cards);
HandValue IsStraight(const std::vector<Card>& cards);

/*
* All of the same suit.
* Continuous sequence:
*	A 2 3 4 5
* 	T J Q K A
*	Q K A 2 3
*/
HandValue IsStraightFlush(const std::vector<Card>& cards)
{

	if(IsFlush(cards) == HandValue::Flush && IsStraight(cards) == HandValue::Straight)
		return HandValue::StraightFlush;

	return HandValue::None;
}

/*
* 
* Any 4 cards of with the same face value
*/
HandValue IsFourOfAKind(const std::vector<Card>& cards)
{
	for(int i=0; i < cards.size()-3; i++)
	{
		bool fourOfAKind = true;
		for(int j=1; j <= 3; j++)
			fourOfAKind = fourOfAKind && (cards[i].faceValue == cards[i+j].faceValue);
				
		if(fourOfAKind)
			return HandValue::FourOfAKind;
		
	}

	return HandValue::None;
}

/*
* 
* 3 cards of a rank and 2 of another
*/
HandValue IsFullHouse(const std::vector<Card>& cards)
{
	if(cards[0].faceValue == cards[1].faceValue //first == second
		&& cards[3].faceValue == cards[4].faceValue //fourth == fifth
		&& cards[0].faceValue != cards[3].faceValue  // first != fourth
		&& (cards[2].faceValue == cards[0].faceValue || cards[2].faceValue == cards[3].faceValue)) //third equals to either first or fourth
		return HandValue::FullHouse;

	return HandValue::None;
}

/*
* 
* All of the same suit
*/
HandValue IsFlush(const std::vector<Card>& cards)
{
	if(std::all_of(begin(cards), end(cards), [first = cards[0]](Card card){ return card.suit == first.suit; }))
		return HandValue::Flush;

	return HandValue::None;
}

/*
* 
* Any 5 sequential cards
*/
HandValue IsStraight(const std::vector<Card>& cards)
{
	
	auto IsSequence = [&cards](int first)
	{
		bool sequence = true;
		
		for(int i=0;i<cards.size()-1;i++)
			sequence = sequence && FaceAdjacency(cards[(first + i) % 5].faceValue, cards[(first + i + 1) % 5].faceValue);		

		return sequence;
	};

	bool sequence = IsSequence(0);

	//Corner case: A T J Q K
	if(cards[0].faceValue == Face::Ace && !sequence)
	{
		sequence = IsSequence(1);
	}
	
	return sequence ? HandValue::Straight : HandValue::None;
}

/*
* 
* Any 3 cards with the same face value
*/
HandValue IsThreeOfAKind(const std::vector<Card>& cards)
{
	for(int i=0;i < cards.size() - 2; i++)
	{
		if(cards[i].faceValue == cards[i+1].faceValue && cards[i].faceValue == cards[i+2].faceValue)
			return HandValue::ThreeOfAKind;
	}
	return HandValue::None;
}

/*
* 
* Any two pairs
*/
HandValue IsTwoPair(const std::vector<Card>& cards)
{
	int pairs = 0, i = 0;

	while(i < cards.size() - 1)
	{
		if(cards[i].faceValue == cards[i+1].faceValue)
		{
			pairs++;
			i = i+2;
		}
		else
			i++;
	}

	return pairs == 2 ? HandValue::TwoPair : HandValue::None;
}

/*
* 
* Any pair
*/
HandValue IsPair(const std::vector<Card>& cards)
{
	for(int i=0;i < cards.size()-1;i++)
		if(cards[i].faceValue == cards[i+1].faceValue)
			return HandValue::OnePair;

	return HandValue::None;
}

/*
* 
* Any pair
*/
HandValue IsHighestCard(const std::vector<Card>& cards)
{
	return HandValue::HighCard;
}